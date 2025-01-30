
#pragma once

#include <iostream>

using std::string;

enum DevilFruit {
    SECRET_FRUIT,
    PARAMECIA,
    ZOAN,
    LOGIA
};

class Pirate {

    string name;
    int bounty;
    DevilFruit ownedDevilFruit;

public:

    Pirate();
    Pirate(const string& name, int bounty, DevilFruit devilFruit);
    ~Pirate() = default;

    void setName(const string& name);
    string getName() const;

    void setBounty(int bounty);
    int getBounty() const;

    void setDevilFruit(DevilFruit devilFruit);
    string getDevilFruit() const;

    friend std::ostream &operator<<(std::ostream &os, const Pirate &pirate);
};
