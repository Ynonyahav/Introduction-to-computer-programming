#include <iostream>

#include "Event.h"
#include "EventFactory.h"
#include "../Utilities.h"

using std::move;
using std::invalid_argument;
using std::exception;
using std::stoi;
using namespace eventfactory;

//****************************************************************************//

unique_ptr<Event> Event::makeEvent(istream& eventsStream) {
    try {
        string eventName;
        eventsStream >> eventName;
        if (eventName.empty()) {
            return nullptr;
        }
        unique_ptr<Event> newEvent = EventFactory::getInstance().createEvent(eventName);
        if (!newEvent) {
            throw invalid_argument("Invalid Event Type: " + eventName);
        }
        newEvent->init(eventsStream);
        return newEvent;
    } catch (const exception& e) {
        throw invalid_argument("Invalid Events File");
    }
}






