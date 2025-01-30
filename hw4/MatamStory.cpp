#include <memory>
#include <sstream>

#include "MatamStory.h"
#include "Utilities.h"

using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::istringstream;
using std::invalid_argument;
using std::exception;

//****************************************************************************//

MatamStory::MatamStory(istream& eventsStream, istream& playersStream)
    : m_turnIndex(INITIAL_TURN_INDEX), m_isGameOver(false) {
    loadEvents(eventsStream);
    loadPlayers(playersStream);
}

//****************************************************************************//

void MatamStory::loadEvents(istream& eventsStream) {
    try {
        while (!eventsStream.eof()) {
            auto event = Event::makeEvent(eventsStream);
            if (!event) {
                break;
            }
            m_events.push(move(event));
        }
        if (m_events.size() < MIN_EVENTS) {
            throw invalid_argument("Empty Event File");
        }
    } catch (const exception& e) {
        throw invalid_argument("Invalid Events File");
    }
}

//*****************************************************************************//

void MatamStory::loadPlayers(istream& playersStream) {
    try {
        while (!playersStream.eof()) {
            string name, job, character;
            playersStream >> name >> job >> character;
            if (name.empty()) {
                break;
            }
            if (job.empty() || character.empty()) {
                throw invalid_argument("Invalid Player Format");
            }
            auto player = make_shared<Player>(name, job, character);
            m_players.push(player);
            m_leaderBoard.emplace_back(player);
            if (m_players.size() > MAX_PLAYERS) {
                break;
            }
        }
        if (m_players.size() < MIN_PLAYERS || m_players.size() > MAX_PLAYERS) {
            throw invalid_argument("Invalid Number Of Players");
        }
    } catch (const exception& e) {
        throw invalid_argument("Invalid Players File");
    }
}

//****************************************************************************//

// Preferred not to define < operator for Player POINTERS, instead: this lambda...
void MatamStory::loadLeaderBoard() {
    m_leaderBoard.sort([](const shared_ptr<Player>& lhs, const shared_ptr<Player>& rhs) {
        return *lhs < *rhs;
    });
}

//****************************************************************************//

void MatamStory::playTurn(Player& player) {
    unique_ptr<Event> currentEvent = move(m_events.front());
    m_events.pop();
    printTurnDetails(m_turnIndex, player, *currentEvent);
    const string outcomeMessege = currentEvent->play(player);
    printTurnOutcome(outcomeMessege);
    m_events.push(move(currentEvent));
    m_turnIndex++;
}

//****************************************************************************//

void MatamStory::playRound() {
    unsigned int activePlayers = m_players.size();
    printRoundStart();
    for (long long unsigned int i = 0; i < m_players.size(); i++) {
        shared_ptr<Player> currentPlayer = m_players.front();
        m_players.pop();
        m_players.push(currentPlayer);
        if (currentPlayer->isActive()) {
            playTurn(*currentPlayer);
        }
        if (!currentPlayer->isActive()) {
            activePlayers--;
        }
        if (currentPlayer->getLevel() == MAX_LEVEL || !activePlayers) {
            m_isGameOver = true;
            //break;
        }
    }
    printRoundEnd();
    loadLeaderBoard();
    printLeaderBoardMessage();
    int rank = 1;
    for (auto it = m_leaderBoard.rbegin(); it != m_leaderBoard.rend(); ++it) {
        printLeaderBoardEntry(rank++, **it);
    }
    printBarrier();
}

//****************************************************************************//

bool MatamStory::isGameOver() const {
    return m_isGameOver;
}

//****************************************************************************//

void MatamStory::play() {
    printStartMessage();
    for (long long unsigned int i = 0; i < m_players.size(); i++) {
        shared_ptr<Player> currentPlayer = m_players.front();
        printStartPlayerEntry(i + 1, *m_players.front());
        m_players.pop();
        m_players.push(currentPlayer);
    }
    printBarrier();
    while (!isGameOver()) {
        playRound();
    }
    printGameOver();
    const auto& it = m_leaderBoard.rbegin();
    if ((*it)->getLevel() == MAX_LEVEL) {
        printWinner(**it);
    } else {
        printNoWinners();
    }
}




