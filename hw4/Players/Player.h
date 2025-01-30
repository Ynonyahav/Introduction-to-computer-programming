#pragma once

#include <string>
#include <memory>

#include "Job.h"
#include "Character.h"

using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::istream;


class Player {
    string m_name;
    unique_ptr<Job> m_job;
    unique_ptr<Character> m_character;
    int m_force;
    int m_healthPoints;
    int m_coins;
    int m_level;
    static const  int MIN_NAME_LEN = 3;
    static const  int MAX_NAME_LEN = 15;
    static const  int MIN_LEVEL = 1;
    static const  int MAX_LEVEL = 10;
    static const  int GENERAL_MIN_PLAYER_VALUES = 0;

public:
    /**
     * Constructor
     *
     * @param name - the name of the player
     * @param job - the job of the player
     * @param character - the character of the player
     */
    Player(const string& name, const string& job, const string& character);
    /**
     * Destructor
     */
    ~Player() = default;
    /**
     * Operator < Overloading
     * @param lhs - the left player
     * @param rhs - the right player
     * @return - true if the left player is smaller than the right player, false otherwise
     *         (by level, coins and name)
     */
    friend bool operator<(const Player& lhs, const Player& rhs);

    /**
     * Gets the name of the player
     * @return - name of the player
     */
    string getName() const;
    /**
     * Gets the description of the player
     * @return - description of the player
     */
    string getDescription() const;
    /**
     * Gets the Job of the player
     * @return - the job by reference of the player
     */
    Job& getJob() const;
    /**
     * Gets the Character of the player
     * @return - the character by reference of the player
     */
    Character& getCharacter() const;
    /**
     * Gets the force of the player
     * @return - the force of the player
     */
    int getForce() const;
    /**
     * Gets the health points of the player
     * @return - the health points of the player
     */
    int getHealthPoints() const;
    /**
     * Gets the coins of the player
     * @return - the coins of the player
     */
    int getCoins() const;
    /**
     * Gets the level of the player
     * @return - the level of the player
     */
    int getLevel() const;
    /**
     * Gets the status of the player
     * @return - true if the player is active, false otherwise
     */
    bool isActive() const;

    /**
     * Sets the job of the player
     * @param type - the type of the job
     */
    void setJob(const string& type);
    /**
     * Sets the character of the player
     * @param type - the type of the character
     */
    void setCharacter(const string& type);
    /**
     * Sets the force of the player
     * @param change - the change to be added
     */
    void setForce(int change);
    /**
     * Sets the health points of the player
     * @param change - the change to be added
     */
    void setHealthPoints(int change);
    /**
     * Sets the coins of the player
     * @param change - the change to be added
     */
    void setCoins(int change);
    /**
     * Sets the level of the player
     * @param change - the change to be added
     */
    void setLevel(int change);
};

