#pragma once

#include <iostream>
#include <queue>
#include <list>

#include "Players/Player.h"
#include "Events/Event.h"

using std::list;
using std::queue;
using std::istream;


/**
 * Represents the game MatamStory
 */
class MatamStory {
    queue<shared_ptr<Player> > m_players;
    queue<unique_ptr<Event> > m_events;
    list<shared_ptr<Player> > m_leaderBoard;

    unsigned int m_turnIndex;
    bool m_isGameOver;

    static constexpr unsigned int INITIAL_TURN_INDEX = 1;
    static constexpr unsigned int MIN_EVENTS = 2;
    static constexpr unsigned int MIN_PLAYERS = 2;
    static constexpr unsigned int MAX_PLAYERS = 6;
    static constexpr unsigned int MAX_LEVEL = 10;

    /**
     * Loads the players from the given input stream
     * @param playersStream - the input stream to load the players from
     * @return - void
     */
    void loadPlayers(istream& playersStream);
    /**
     * Loads the events from the given input stream
     * @param eventsStream - the input stream to load the events from
     * @return - void
     */
    void loadEvents(istream& eventsStream);
    /**
     * Arranges the list of players acording to their level, coins and name.
     * @return - void
     */
    void loadLeaderBoard();

    /**
     * Plays a single turn for a player
     * @param player - the player to play the turn for (correct player)
     * @return - void
     */
    void playTurn(Player& player);
    /**
     * Plays a single round of the game (all players in the game play a one turn)
     * @return - void
     */
    void playRound();
    /**
     * Checks if the game is over
     * @return - true if the game is over, false otherwise
     */
    bool isGameOver() const;

public:

    /**
     * Constructor of MatamStory class
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     * @return - MatamStory object with the given events and players
     */
    MatamStory(istream& eventsStream, istream& playersStream);
    /**
     * Copy constructor of MatamStory class - deleted
     */
    MatamStory(const MatamStory&) = delete;
    /**
     * Assignment operator of MatamStory class - deleted
     */
    MatamStory& operator=(const MatamStory&) = delete;
    /**
     * Destructor of MatamStory class
     */
    ~MatamStory() = default;

    /**
     * Plays the entire game (all rounds until the game is over)
     * @return - void
     */
    void play();
};
