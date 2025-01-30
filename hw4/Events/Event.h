#pragma once

#include <memory>
#include <vector>
#include <string>

#include "../Players/Player.h"

using std::unique_ptr;
using std::vector;
using std::istream;
using std::to_string;

/**
 * Base class for all events in the game.
 */
class Event {

public:
    /**
     * Destructor.
     */
    virtual ~Event() = default;
    /**
     * Factory method to create an event from the input stream
     * @param eventsStream The input stream to read from.
     * @return A unique pointer to the created event.
     *     If the event type is invalid, returns nullptr.
     */
    static unique_ptr<Event> makeEvent(istream& eventsStream);
    /**
     * Initializes the event from the input stream.
     * its for specializations of specific needs to specific events.
     * (the default implementation does nothing)
     * @param eventsStream The input stream to read from.
     */
    virtual void init(istream&) {}
    /**
     * Pure virtual method to get the description of the event.
     * @return The string representation of the event.
     */
    virtual string getDescription() const = 0;
    /**
     * Pure virtual method to play the event.
     * @param player The player to play the event on.
     * @return The string representation of the event result.
     */
    virtual string play(Player& player) = 0;
};


