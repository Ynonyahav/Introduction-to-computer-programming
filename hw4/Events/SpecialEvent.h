#pragma once

#include "Event.h"


class SpecialEvent : public Event {

public:
    /**
     * @return The name of the special event.
     */
    string getName() const;
    /**
     * @return The description of the special event
     */
    string getDescription() const override;

protected:
    const string m_specialEventName;
    /**
     * Constructor for the special event
     * @param name - the name of the special event
     */
    explicit SpecialEvent(string name);
};

//****************************************************************************//

class SolarEclipse : public SpecialEvent {
    static const  int MAGICAL_FORCE_UP = 1;
    static const  int COMMON_FORCE_DOWN = -1;
    static const  int NO_CHANGE = 0;
    /**
     * Plays the magical version of the event
     * @param player - the player to play the event for
     * @return string - the result of the Play
     */
    static string playMagical(Player& player);
    /**
     * Plays the common version of the event
     * @param player - the player to play the event for
     * @return string - the result of the Play
     */
    static string playCommon(Player& player);

public:
    //Constructor 
    SolarEclipse();
    /**
     * Plays the event
     * @param player - the player to play the event for
     * @return string - the result of the Play
     */
    string play(Player& player) override;
};

//****************************************************************************//

class PotionsMerchant : public SpecialEvent {
    static const  int POTION_COST = 5;
    static const  int POTION_BENEFIT = 10;
    static const  int RISK_TAKING_HEALTH_CONDITION_VALUE = 50;
    static const  int RISK_TAKING_BUY_LIMIT = 1;
    /**
     * Plays the risk taking version of the event
     * @param player - the player to play the event for
     * @return string - the result of the Play
     */
    static string playRiskTaking(Player& player);
    /**
     * Plays the responsible version of the event
     * @param player - the player to play the event for
     * @return string - the result of the Play
     */
    static string playResponsible(Player& player);

public:
    //Constructor
    PotionsMerchant();
    /**
     * Plays the event
     * @param player - the player to play the event for
     * @return string - the result of the Play
     */
    string play(Player& player) override;
};

//****************************************************************************//

class DivineInspiration : public SpecialEvent {

public:
    //Constructor
    DivineInspiration();
    /**
     * Plays the event
     * @param player - the player to play the event for
     * @return string - the result of the Play
     */
    string play(Player& player) override;
};

