#include <string>
#include <future>

#include "Player.h"
#include "PlayerFactory.h"

using std::move;
using std::invalid_argument;
using std::exception;
using std::string;
using std::to_string;
using namespace playerfactory;


//****************************************************************************//

Player::Player(const string& name, const string& job, const string& character)
        : m_level(MIN_LEVEL) {
        try {
                if (name.size() < MIN_NAME_LEN ||
                    name.size() > MAX_NAME_LEN) {
                        throw invalid_argument("Invalid Player Name: " + name);
                }
                m_name = name;
                m_job = PlayerFactory::getInstance().createJob(job);
                m_character = PlayerFactory::getInstance().createCharacter(character);
                if (!m_job || !m_character) {
                        throw invalid_argument("Invalid Job / Character Type: " + job + ", " + character);
                }
                m_force = m_job->getInitialForce();
                m_healthPoints = m_job->getInitialHealthPoints();
                m_coins = m_job->getInitialCoins();
        } catch (const exception& e) {
                throw invalid_argument("Invalid Players File");
        }
}

//****************************************************************************//

bool operator<(const Player& lhs, const Player& rhs) {
        if (lhs.m_level < rhs.m_level) {
                return true;
        }
        if (lhs.m_level == rhs.m_level) {
                if (lhs.getCoins() < rhs.getCoins()) {
                        return true;
                }
                if (lhs.getCoins() == rhs.getCoins()) {
                        if (lhs.m_name > rhs.m_name) {
                                return true;
                        }
                }
        }
        return false;
}

//****************************************************************************//

string Player::getName() const {
        return m_name;
}

//****************************************************************************//

string Player::getDescription() const {
        return getName() + ", " + m_job->getName() + " with "
               + m_character->getName() + " character "
               + "(level " + to_string(getLevel())
               + ", force " + to_string(getForce()) + ")";
}

//****************************************************************************//

Job& Player::getJob() const {
        return *m_job;
}
//****************************************************************************//

Character& Player::getCharacter() const {
        return *m_character;
}

//****************************************************************************//

int Player::getForce() const {
        return m_force;
}

//****************************************************************************//
int Player::getHealthPoints() const {
        return m_healthPoints;
}

//****************************************************************************//

int Player::getCoins() const {
        return m_coins;
}

//****************************************************************************//

int Player::getLevel() const {
        return m_level;
}

//****************************************************************************//

bool Player::isActive() const {
        return m_healthPoints;
}

//****************************************************************************//

void Player::setJob(const string& type) {
        unique_ptr<Job> job = PlayerFactory::getInstance().createJob(type);
        if (!job) {
                throw invalid_argument("Invalid Job Type: " + type);
        }
        m_job = move(job);
}

//****************************************************************************//

void Player::setCharacter(const string& type) {
        unique_ptr<Character> character = PlayerFactory::getInstance().createCharacter(type);
        if (!character) {
                throw invalid_argument("Invalid Character Type: " + type);
        }
        m_character = move(character);
}

//****************************************************************************//

void Player::setForce(int change) {
        int result = m_force + change;
        if (result < GENERAL_MIN_PLAYER_VALUES) {
                m_force = GENERAL_MIN_PLAYER_VALUES;
        } else {
                m_force = result;
        }
}

//****************************************************************************//

void Player::setHealthPoints(int change) {
        int result = m_healthPoints + change;
        if (result < GENERAL_MIN_PLAYER_VALUES) {
                m_healthPoints = GENERAL_MIN_PLAYER_VALUES;
        } else if (result > m_job->getMaxHealthPoints()) {
                m_healthPoints = m_job->getMaxHealthPoints();
        } else {
                m_healthPoints = result;
        }
}

//****************************************************************************//

void Player::setCoins(int change) {
        int result = m_coins + change;
        if (result < GENERAL_MIN_PLAYER_VALUES) {
                m_coins = GENERAL_MIN_PLAYER_VALUES;
        } else {
                m_coins = result;
        }
}

//****************************************************************************//

void Player::setLevel(int change) {
        int result = m_level + change;
        if (change < MIN_LEVEL) {
                m_level = MIN_LEVEL;
        } else if (result > MAX_LEVEL) {
                m_level = MAX_LEVEL;
        } else {
                m_level = result;
        }
}


