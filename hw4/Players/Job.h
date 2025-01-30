#pragma once

#include <string>

using std::string;


class Job {

public:
    // Destructor
    virtual ~Job() = default;
    /**
     * @return - the name of the job 
     */
    string getName() const;
    /**
     * @return - the combat quality of the job (melee, distance, evasion)
     */
    string getCombatQuality() const;
    /**
     * @return - the magical quality of the job (common, magical)
     */
    string getMagicalQuality() const;
    /**
     * @return - the initial force of the job
     */
    int getInitialForce() const;
    /**
     * @return - the initial health points of the job
     */
    int getInitialHealthPoints() const;
    /**
     * @return - the initial coins of the job
     */
    int getInitialCoins() const;
    /**
     * @return - the maximum health points of the job
     */
    virtual int getMaxHealthPoints() const;

protected:
    const string m_name;
    string m_combatQuality = "Distance";
    string m_magicalQuality = "Common";
    int m_force;
    int m_healthPoints;
    int m_coins;
    static const  int INITIAL_FORCE = 5;
    static const  int INITIAL_HEALTH = 100;
    static const  int INITIAL_COINS = 10;
    static const  int MAX_HEALTH_POINTS = 100;

    // Constructor
    explicit Job(string name);
    /**
     * Constructor 
     * @param name - the name of the job
     * @param force - the force of the job
     * @param healthPoints - the health points of the job
     * @param coins - the coins of the job
     */
    Job(string name, int force, int healthPoints, int coins);
};

//****************************************************************************//

class Warrior : public Job {
    static const  int WARRIOR_MAX_HEALTH = 150;

public:
    // Constructor
    Warrior();
    /**
     * @return - the maximum health points of the warrior
     */
    int getMaxHealthPoints() const override;
};

//****************************************************************************//

class Archer : public Job {
    static const  int ARCHER_INITIAL_COINS = 20;

public:
    // Constructor
    Archer();
};

//****************************************************************************//

class Magician : public Job {

public:
    // Constructor
    Magician();
};

//****************************************************************************//

class Rogue : public Job {

public:
    // Constructor
    Rogue();
};
