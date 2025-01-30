#pragma once

#include "Event.h"


class Monster : public Event {
    static const  int LEVEL_UP = 1;
    static const  int VICTORY = 1;
    static const  int DEFEAT = 0;
    static const  int MELEE_FORCE_MULTIPLY = 2;
    static const  int MELEE_HEALTH_DOWN = -10;
    static const  int ROUGH_FORCE_DIFFERANCE_CONDITION_VALUE = 2;

    /**
     * Calculates the combat power of the player in melee combat
     * @param player - the player to calculate the combat power for
     * @return - the combat power of the player in melee combat
     */
    static int meleeCombatPower(const Player& player);
    /**
     * Calculates the general combat power of the player
     * @param player - the player to calculate the combat power for
     * @return - the general combat power of the player
     */
    static int generalCombatPower(const Player& player);
    /**
     * Plays the monster encounter
     * @param player - the player to play the encounter for
     * @param combatPower - the combat power of the player
     * @return - the result of the encounter (VICTORY or DEFEAT)
     */
    int generalMonsterPlay(Player& player, int combatPower) const;
    /**
     * Plays the monster encounter in melee combat
     * @param player - the player to play the encounter for
     * @return string - getEncounterWonMessage or getEncounterLostMessage
     */
    string meleePlay(Player& player) const;
    /**
     * Plays the monster encounter in distance combat
     * @param player - the player to play the encounter for
     * @return string - getEncounterWonMessage or getEncounterLostMessage
     */
    string distancePlay(Player& player) const;
    /**
     * Plays the monster encounter in evasion combat
     * @param player - the player to play the encounter for
     * @return string - getEncounterWonMessage or getEncounterLostMessage or EncounterDodgedMessage
     */
    string evasionPlay(Player& player) const;

public:

    /**
     * @return The name of the monster.
     */
    string getName() const;
    /**
     * @return The description of the monster
     */
    string getDescription() const override;
    /**
     * @return The combat power of the monster
     */
    int getCombatPower() const;
    /**
     * @return The loot from the monster
     */
    int getLoot() const;
    /**
     * @return The damage of the monster
     */
    int getDamage() const;

    /**
     * Sets the combat power of the monster
     * @param change - the change to be made
     */
    virtual void setCombatPower(int change);
    /**
     * Sets the loot from the monster
     * @param change - the change to be made
     */
    virtual void setLoot(int change);
    /**
     * Sets the damage from the monster
     * @param change - the change to be made
     */
    virtual void setDamage(int change);

protected:
    const string m_monsterName;
    int m_combatPower;
    int m_loot;
    int m_damage;

    /**
     * Constructor for the monster
     * @param name - the name of the monster
     * @param combatPower - the combat power of the monster
     * @param loot - the loot from the monster
     * @param damage - the damage of the monster
     */
    Monster(string name, int combatPower, int loot, int damage);
    /**
     * @return string - the details of the monster
     */
    string getDetails() const;
    /**
     * Plays the monster encounter
     * @param player - the player to play the encounter for
     * @return string - result of the encounter
     */
    string play(Player& player) override;
};

//****************************************************************************//

class Snail : public Monster {
    static const  int SNAIL_POWER = 5;
    static const  int SNAIL_LOOT = 2;
    static const  int SNAIL_DAMAGE = 10;

public:
    // Constructor
    Snail();
};

//****************************************************************************//

class Slime : public Monster {
    static const  int SLIME_POWER = 12;
    static const  int SLIME_LOOT = 5;
    static const  int SLIME_DAMAGE = 25;

public:
    // Constructor
    Slime();
};

//****************************************************************************//

class Balrog : public Monster {
    static const  int BALROG_POWER = 15;
    static const  int BALROG_LOOT = 100;
    static const  int BALROG_DAMAGE = 9001;
    static const  int BALROG_ENCOUNTER_POWER_UP = 2;

public:
    // Constructor
    Balrog();
    /**
     * @return int - the power up of the balrog after encounter
     */
    static int getBalrogEncounterPowerUp();
    /**
     * Plays the balrog encounter
     * @param player - the player to play the encounter for
     * @return string - result of the encounter
     */
    string play(Player& player) override;
};

//****************************************************************************//

class Pack : public Monster {
    vector<unique_ptr<Event> > m_monsters;
    int m_packSize;
    int m_totalMonsters;
    int m_totalBalrogs;
    static const  int MIN_PACK_MEMBERS = 2;

public:
    // Constructor
    Pack();
    /**
     * Initializes the pack from the input stream
     * @param eventStream - the input stream to read from
     */
    void init(istream& eventStream) override;
    /**
     * @return string - the description of the pack
     */
    string getDescription() const override;
    /**
     * @return int - the size of the pack (number of monsters)
     */
    int getPackSize() const;
    /**
     * @return int - the total number of monsters in the pack (including sub packs)
     */
    int getTotalMonsters() const;
    /**
     * @return int - the total number of balrogs in the pack (including sub packs)
     */
    int getTotalBalrogs() const;
    /**
     * Plays the pack encounter
     * @param player - the player to play the encounter for
     * @return string - result of the encounter
     */
    string play(Player& player) override;
};



