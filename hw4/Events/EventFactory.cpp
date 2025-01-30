#include "EventFactory.h"
#include "Monster.h"
#include "SpecialEvent.h"

using namespace eventfactory;
using std::make_unique;
using std::move;


//****************************************************************************//

EventFactory::EventFactory() {
    // Register Default Event Creators:
    m_eventCreators["Snail"] = [] { return make_unique<Snail>(); };
    m_eventCreators["Slime"] = [] { return make_unique<Slime>(); };
    m_eventCreators["Balrog"] = [] { return make_unique<Balrog>(); };
    m_eventCreators["Pack"] = [] { return make_unique<Pack>(); };
    m_eventCreators["SolarEclipse"] = [] { return make_unique<SolarEclipse>(); };
    m_eventCreators["PotionsMerchant"] = [] { return make_unique<PotionsMerchant>(); };
    m_eventCreators["DivineInspiration"] = [] { return make_unique<DivineInspiration>(); };
}

//****************************************************************************//

EventFactory& EventFactory::getInstance() {
    static EventFactory eventFactory;
    return eventFactory;
}

//****************************************************************************//

unique_ptr<Event> EventFactory::createEvent(const string& type) const {
    const auto it = m_eventCreators.find(type);
    if (it != m_eventCreators.end()) {
        return it->second();
    }
    return nullptr;
    //throw std::invalid_argument("Invalid Event Type: " + type);
}

//****************************************************************************//

PlayMethod EventFactory::getPlayMethod(const string& key) const {
    auto it = m_playMethods.find(key);
    if (it != m_playMethods.end()) {
        return it->second;
    }
    return nullptr;
    //throw std::runtime_error("Invalid Play Method: " + key);
}

//****************************************************************************//

void EventFactory::registerEvent(const string& type, EventCreator eventCreator) {
    if (m_eventCreators.find(type) == m_eventCreators.end()) {
        m_eventCreators[type] = move(eventCreator);
    }
}

//****************************************************************************//

void EventFactory::registerPlayMethod(const string& key, PlayMethod playMethod) {
    if (m_playMethods.find(key) == m_playMethods.end()) {
        m_playMethods[key] = move(playMethod);
    }
}

