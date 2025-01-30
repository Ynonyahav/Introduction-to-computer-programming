#include "Job.h"

#include <utility>

using std::move;

//****************************************************************************//

Job::Job(string name)
    : m_name(move(name)), m_force(INITIAL_FORCE), m_healthPoints(INITIAL_HEALTH), m_coins(INITIAL_COINS) {}

//****************************************************************************//

Job::Job(string name, int force, int healthPoints, int coins)
    : m_name(move(name)), m_force(force), m_healthPoints(healthPoints), m_coins(coins) {}

//****************************************************************************//

Warrior::Warrior() : Job("Warrior", INITIAL_FORCE, WARRIOR_MAX_HEALTH, INITIAL_COINS) {
    m_combatQuality = "Melee";
}

//****************************************************************************//

Archer::Archer() : Job("Archer", INITIAL_FORCE, INITIAL_HEALTH, ARCHER_INITIAL_COINS) {}

//****************************************************************************//

Magician::Magician() : Job("Magician") {
    m_magicalQuality = "Magical";
}

//****************************************************************************//

Rogue::Rogue() : Job("Rogue") {
    m_combatQuality = "Evasion";
}

//****************************************************************************//

string Job::getName() const {
    return m_name;
}

//****************************************************************************//

string Job::getCombatQuality() const {
    return m_combatQuality;
}

//****************************************************************************//

string Job::getMagicalQuality() const {
    return m_magicalQuality;
}

//****************************************************************************//

int Job::getInitialForce() const {
    return m_force;
}

//****************************************************************************//

int Job::getInitialHealthPoints() const {
    return m_healthPoints;
}

//****************************************************************************//

int Job::getInitialCoins() const {
    return m_coins;
}

//****************************************************************************//

int Job::getMaxHealthPoints() const {
    return MAX_HEALTH_POINTS;
}

//****************************************************************************//

int Warrior::getMaxHealthPoints() const {
    return WARRIOR_MAX_HEALTH;
}







