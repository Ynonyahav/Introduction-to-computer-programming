
#include "Pirate.h"


Pirate::Pirate() : bounty(0), ownedDevilFruit(SECRET_FRUIT) {}


Pirate::Pirate(const string& name,
    const int bounty,
    const DevilFruit devilFruit):
    name(name), bounty(bounty), ownedDevilFruit(devilFruit) {}


void Pirate::setName(const string& name) {
    this->name = name;
}


std::string Pirate::getName() const {
    return name;
}


void Pirate::setBounty(const int bounty) {
    this->bounty = bounty;
}


int Pirate::getBounty() const {
    return bounty;
}

void Pirate::setDevilFruit(const DevilFruit devilFruit) {
    this->ownedDevilFruit = devilFruit;
}


std::string Pirate::getDevilFruit() const {
    if (ownedDevilFruit == PARAMECIA)
        return "Paramecia";
    if (ownedDevilFruit == ZOAN)
        return "Zoan";
    return "Secret Fruit";
}


std::ostream &operator<<(std::ostream &os, const Pirate &pirate) {
    os << "Pirate " << pirate.name << ":"<< std::endl;
    os << "Head Bounty: " << pirate.bounty << std::endl;
    os << "Owned Devil-Fruit: " << pirate.getDevilFruit();
    return os;
}

