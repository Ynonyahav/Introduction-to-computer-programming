#pragma once

#include <string>

using std::string;

// Abstract class
class Character {

public:
    // Destructor
    virtual ~Character() = default;
    // Pure virtual method to get the name of the character.
    virtual string getName() const = 0;
};

//****************************************************************************//

class Responsible : public Character {
    string m_name = "Responsible";

public:
    // Constructor
    Responsible() = default;
    /**
     * @Return - the name of the character
     */
    string getName() const override {
        return m_name;
    }
};

//****************************************************************************//

class RiskTaking : public Character {
    string m_name = "RiskTaking";

public:
    // Constructor
    RiskTaking() = default;
    /**
     * @Return - the name of the character
     */
    string getName() const override {
        return m_name;
    }
};

//****************************************************************************//





