#include <iostream>

#include "Monster.h"
#include "EventFactory.h"
#include "../Utilities.h"

using std::move;
using std::invalid_argument;
using std::exception;
using std::stoi;
using namespace eventfactory;

//****************************************************************************//

// Helper function to get and validate pack size:
int getAndVerifyPackSize(const string& packSize, int minSize) {
    try {
        for (const char i: packSize) {
            if (i > '9' || i < '0') {
                throw invalid_argument("Non-integer Pack Size: " + packSize);;
            }
        }
        int size = stoi(packSize);
        if (size < minSize) {
            throw invalid_argument("Low Pack Size: " + packSize);;
        }
        return size;
    } catch (const exception& e) {
        throw invalid_argument("Invalid Pack Size: " + packSize);
    }
}

//****************************************************************************//

void Pack::init(istream& eventStream) {
    string packSize;
    eventStream >> packSize;
    m_packSize = getAndVerifyPackSize(packSize, MIN_PACK_MEMBERS);
    for (int i = 0; i < m_packSize; i++) {
        string next;
        eventStream >> next;
        unique_ptr<Event> newEvent = EventFactory::getInstance().createEvent(next);
        if (!newEvent) {
            throw invalid_argument("Invalid Event Type: " + next);
        }
        newEvent->init(eventStream);
        auto* monster = dynamic_cast<Monster*>(newEvent.get());
        if (monster) {
            m_totalMonsters++;
            m_combatPower += monster->getCombatPower();
            m_loot += monster->getLoot();
            m_damage += monster->getDamage();
            const auto* packMonster = dynamic_cast<Pack*>(monster);
            if (packMonster) {
                m_totalMonsters += packMonster->getTotalMonsters() - 1;
                m_totalBalrogs += packMonster->getTotalBalrogs();
            }
            const auto* balrog = dynamic_cast<Balrog*>(monster);
            if (balrog) {
                m_totalBalrogs++;
            }
        }
        m_monsters.emplace_back(move(newEvent));
    }
}

//****************************************************************************//

Monster::Monster(string name, int combatPower, int loot, int damage)
    : m_monsterName(move(name)), m_combatPower(combatPower), m_loot(loot), m_damage(damage) {
    EventFactory::getInstance().registerPlayMethod(m_monsterName + "_" + "Melee",
        [this](Player& player) { return meleePlay(player); });
    EventFactory::getInstance().registerPlayMethod(m_monsterName + "_" + "Distance",
        [this](Player& player) { return distancePlay(player); });
    EventFactory::getInstance().registerPlayMethod(m_monsterName + "_" + "Evasion",
        [this](Player& player) { return evasionPlay(player); });
}

//****************************************************************************//

string Monster::getName() const {
    return m_monsterName;
}

//****************************************************************************//

int Monster::getCombatPower() const {
    return m_combatPower;
}

//****************************************************************************//

void Monster::setCombatPower(int change) {
    m_combatPower += change;
}

//****************************************************************************//

int Monster::getLoot() const {
    return m_loot;
}

//****************************************************************************//

void Monster::setLoot(int change) {
    m_loot += change;
}

//****************************************************************************//

int Monster::getDamage() const {
    return m_damage;
}

//****************************************************************************//

void Monster::setDamage(int change) {
    m_damage += change;
}

//****************************************************************************//

string Monster::getDetails() const {
    return " (power " + to_string(getCombatPower()) +
           ", loot " + to_string(getLoot()) + ", damage " +
           to_string(getDamage()) + ")";
}

//****************************************************************************//

string Monster::getDescription() const {
    return getName() + getDetails();
}

//****************************************************************************//

int Monster::meleeCombatPower(const Player& player) {
    return MELEE_FORCE_MULTIPLY * player.getForce() + player.getLevel();
}

//****************************************************************************//

int Monster::generalCombatPower(const Player& player) {
    return player.getForce() + player.getLevel();
}

//****************************************************************************//

string Monster::play(Player& player) {
    const string key = m_monsterName + "_" + player.getJob().getCombatQuality();
    auto playMethod = EventFactory::getInstance().getPlayMethod(key);
    if (playMethod) {
        return playMethod(player);
    }
    return "No valid play method found.";
}

//****************************************************************************//

int Monster::generalMonsterPlay(Player& player, int combatPower) const {
    if (combatPower > m_combatPower) {
        player.setLevel(LEVEL_UP);
        player.setCoins(m_loot);
        return VICTORY;
    }
    player.setHealthPoints(-m_damage);
    return DEFEAT;
}

//****************************************************************************//

string Monster::meleePlay(Player& player) const {
    int result = generalMonsterPlay(player, meleeCombatPower(player));
    if (result == VICTORY) {
        player.setHealthPoints(MELEE_HEALTH_DOWN);
        return getEncounterWonMessage(player, m_loot);
    }
    return getEncounterLostMessage(player, m_damage);
}

//****************************************************************************//

string Monster::distancePlay(Player& player) const {
    int result = generalMonsterPlay(player, generalCombatPower(player));
    if (result == VICTORY) {
        return getEncounterWonMessage(player, m_loot);
    }
    return getEncounterLostMessage(player, m_damage);
}

//****************************************************************************//

string Monster::evasionPlay(Player& player) const {
    if (m_combatPower >= ROUGH_FORCE_DIFFERANCE_CONDITION_VALUE * player.getForce()) {
        return player.getName() + " dodged the encunter!";
    }
    return distancePlay(player);
}

//****************************************************************************//

Snail::Snail() : Monster("Snail", SNAIL_POWER, SNAIL_LOOT, SNAIL_DAMAGE) {}

//****************************************************************************//

Slime::Slime() : Monster("Slime", SLIME_POWER, SLIME_LOOT, SLIME_DAMAGE) {}

//****************************************************************************//

Balrog::Balrog() : Monster("Balrog", BALROG_POWER, BALROG_LOOT, BALROG_DAMAGE) {}

//****************************************************************************//

int Balrog::getBalrogEncounterPowerUp() {
    return BALROG_ENCOUNTER_POWER_UP;
}

//****************************************************************************//

string Balrog::play(Player& player) {
    string result = Monster::play(player);
    setCombatPower(BALROG_ENCOUNTER_POWER_UP);
    return result;
}

//****************************************************************************//

Pack::Pack() : Monster("Pack", 0, 0, 0),
               m_packSize(0), m_totalMonsters(0), m_totalBalrogs(0) {}

//****************************************************************************//

string Pack::getDescription() const {
    return getName() + " of " + to_string(m_packSize) + " members" + getDetails();
}

//****************************************************************************//

int Pack::getPackSize() const {
    return m_packSize;
}

//****************************************************************************//

int Pack::getTotalMonsters() const {
    return m_totalMonsters;
}

//****************************************************************************//

int Pack::getTotalBalrogs() const {
    return m_totalBalrogs;
}

//****************************************************************************//

string Pack::play(Player& player) {
    string result = Monster::play(player);
    setCombatPower(Balrog::getBalrogEncounterPowerUp() * m_totalBalrogs);
    return result;
}
