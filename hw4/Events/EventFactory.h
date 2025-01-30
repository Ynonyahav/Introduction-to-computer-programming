#pragma once

#include <functional>
#include <unordered_map>
#include <string>

#include "Event.h"

using std::function;
using std::unique_ptr;
using std::unordered_map;
using std::string;

namespace eventfactory {

    // For easier readability, hopefully...
    using EventCreator = function<unique_ptr<Event>()>;
    using PlayMethod = function<string(Player&)>;

    /**
     * Factory class for creating events, and getting the play methods.
     */
    class EventFactory {
        unordered_map<string, EventCreator> m_eventCreators;
        unordered_map<string, PlayMethod> m_playMethods;
        /**
         * Private constructor to prevent instantiation. (Singleton)
         * Registers default event creators.
         */
        EventFactory();
        /**
         * Destructor.
         */
        ~EventFactory() = default; // Optional but advised

    public:
        /**
         * Gets the singleton instance of the EventFactory.
         * @return The singleton instance of the EventFactory.
         */
        static EventFactory& getInstance();
        /**
         * Deleted copy constructor. (Singleton)
         */
        EventFactory(const EventFactory&) = delete;
        /**
         * Deleted copy assignment operator. (Singleton)
         */
        EventFactory& operator=(const EventFactory&) = delete;

        /**
         * Creates an event of the given type.
         * @param type The type of the event to create.
         * @return A unique pointer to the created event.
         *     If the event type is invalid, returns nullptr.
         */
        unique_ptr<Event> createEvent(const string& type) const;
        /**
         * Gets the play method of the given key.
         * @param key The key of the play method to get.
         * @return The play method of the given key.
         */
        PlayMethod getPlayMethod(const string& key) const;

        /**
         * Registers an event creator with the given type. (map key)
         * @param type The type of the event to register.
         * @param eventCreator The event creator to register.
         */
        void registerEvent(const string& type, EventCreator eventCreator);
        /**
         * Registers a play method with the given key. (map key)
         * @param key The key of the play method to register.
         * @param playMethod The play method to register.
         */
        void registerPlayMethod(const string& key, PlayMethod playMethod);
    };
}

