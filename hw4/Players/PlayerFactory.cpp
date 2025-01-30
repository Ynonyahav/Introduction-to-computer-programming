#include "PlayerFactory.h"

using namespace playerfactory;
using std::make_unique;
using std::move;


//****************************************************************************//

PlayerFactory::PlayerFactory() {
    // Register Default Job Creators:
    m_jobCreators["Warrior"] = [] { return make_unique<Warrior>(); };
    m_jobCreators["Archer"] = [] { return make_unique<Archer>(); };
    m_jobCreators["Magician"] = [] { return make_unique<Magician>(); };
    m_jobCreators["Rogue"] = [] { return make_unique<Rogue>(); };

    // Register Default Character Creators:
    m_characterCreators["Responsible"] = [] { return make_unique<Responsible>(); };
    m_characterCreators["RiskTaking"] = [] { return make_unique<RiskTaking>(); };
}

//****************************************************************************//

PlayerFactory& PlayerFactory::getInstance() {
    static PlayerFactory creatorsFactory;
    return creatorsFactory;
}

//****************************************************************************//

unique_ptr<Job> PlayerFactory::createJob(const string& type) const {
    const auto it = m_jobCreators.find(type);
    if (it != m_jobCreators.end()) {
        return it->second();
    }
    return nullptr;
    //throw std::invalid_argument("Invalid Job Type: " + type);
}

//****************************************************************************//

unique_ptr<Character> PlayerFactory::createCharacter(const string& type) const {
    const auto it = m_characterCreators.find(type);
    if (it != m_characterCreators.end()) {
        return it->second();
    }
    return nullptr;
    //throw std::invalid_argument("Invalid Character Type: " + type);
}

//****************************************************************************//

void PlayerFactory::registerJob(const string& type, JobCreator jobCreator) {
    if (m_jobCreators.find(type) == m_jobCreators.end()) {
        m_jobCreators[type] = move(jobCreator);
    }
}

//****************************************************************************//

void PlayerFactory::registerCharacter(const string& type, CharacterCreator characterCreator) {
    if (m_characterCreators.find(type) == m_characterCreators.end()) {
        m_characterCreators[type] = move(characterCreator);
    }
}


