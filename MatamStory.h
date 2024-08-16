
#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include <sstream>

#include "Players/Player.h"
#include "Events/Event.h"
#include "Events/Encounter.h"
#include "Events/SpecialEvent.h"

using std::shared_ptr;
using std::vector;
using std::queue;
using std::exception;


class MatamStory{
private:
    unsigned int m_turnIndex;
    shared_ptr<vector<shared_ptr<Player>>> Players_Vec;
    std::queue<shared_ptr<Event>>* Events_queue;
    /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player& player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;

public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);
    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();

    ///add a destractor
    ~MatamStory();

};
