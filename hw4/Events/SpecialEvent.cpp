#include <iostream>

#include "SpecialEvent.h"
#include "EventFactory.h"
#include "../Utilities.h"

using std::move;
using std::invalid_argument;
using std::exception;
using std::stoi;
using namespace eventfactory;


//****************************************************************************//

SpecialEvent::SpecialEvent(string name) : m_specialEventName(move(name)) {}

//****************************************************************************//

string SpecialEvent::getName() const {
    return m_specialEventName;
}

//****************************************************************************//

string SpecialEvent::getDescription() const {
    return m_specialEventName;
}

//****************************************************************************//

SolarEclipse::SolarEclipse() : SpecialEvent("SolarEclipse") {
    EventFactory::getInstance().registerPlayMethod("SolarEclipse_Magical",
        &SolarEclipse::playMagical);
    EventFactory::getInstance().registerPlayMethod("SolarEclipse_Common",
        &SolarEclipse::playCommon);
}

//****************************************************************************//

string SolarEclipse::play(Player& player) {
    const string key = "SolarEclipse_" + player.getJob().getMagicalQuality();
    auto playMethod = EventFactory::getInstance().getPlayMethod(key);
    if (playMethod) {
        return playMethod(player);
    }
    return "No valid play method found.";
}

//****************************************************************************//

string SolarEclipse::playMagical(Player& player) {
    player.setForce(MAGICAL_FORCE_UP);
    return getSolarEclipseMessage(player, MAGICAL_FORCE_UP);
}

//****************************************************************************//

string SolarEclipse::playCommon(Player& player) {
    if (player.getForce()) {
        player.setForce(COMMON_FORCE_DOWN);
        return getSolarEclipseMessage(player, COMMON_FORCE_DOWN);
    }
    return getSolarEclipseMessage(player, NO_CHANGE);
}

//****************************************************************************//

PotionsMerchant::PotionsMerchant() : SpecialEvent("PotionsMerchant") {
    EventFactory::getInstance().registerPlayMethod("PotionsMerchant_RiskTaking",
        &PotionsMerchant::playRiskTaking);
    EventFactory::getInstance().registerPlayMethod("PotionsMerchant_Responsible",
        &PotionsMerchant::playResponsible);
}

//****************************************************************************//

string PotionsMerchant::play(Player& player) {
    const string key = "PotionsMerchant_" + player.getCharacter().getName();
    auto playMethod = EventFactory::getInstance().getPlayMethod(key);
    if (playMethod) {
        return playMethod(player);
    }
    return "No valid play method found.";
}

//****************************************************************************//

string PotionsMerchant::playResponsible(Player& player) {
    int amount = 0;
    while (player.getCoins() >= POTION_COST &&
           player.getHealthPoints() < player.getJob().getMaxHealthPoints()) {
        player.setCoins(-POTION_COST);
        player.setHealthPoints(POTION_BENEFIT);
        amount++;
    }
    return getPotionsPurchaseMessage(player, amount);
}

//****************************************************************************//

string PotionsMerchant::playRiskTaking(Player& player) {
    int amount = 0;
    if (player.getCoins() >= POTION_COST) {
        if (player.getHealthPoints() < RISK_TAKING_HEALTH_CONDITION_VALUE) {
            player.setCoins(-POTION_COST);
            player.setHealthPoints(POTION_BENEFIT);
            amount = RISK_TAKING_BUY_LIMIT;
        }
    }
    return getPotionsPurchaseMessage(player, amount);
}

//****************************************************************************//

DivineInspiration::DivineInspiration() : SpecialEvent("DivineInspiration") {}

//****************************************************************************//

string DivineInspiration::play(Player& player) {
    // For exemple: change to Warrior. needs to define a method for instanciate random option.
    // Ofcourse, it is possiable that the new random job needs to be differante from the old one
    player.setJob("Warrior");
    return player.getName() + " had a Devine Inspiration and changed his job to Warrior";
}
