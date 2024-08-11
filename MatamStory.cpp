
#include "MatamStory.h"

#include "Utilities.h"


void print_Outcome(Player& player,int result,int outcome){
    if(outcome == 0){
        std::string outcome_massege = getEncounterWonMessage(player,result);
        printTurnOutcome(outcome_massege);
    }
    if(outcome == 1){
        std::string outcome_massege = getEncounterLostMessage(player,result);
        printTurnOutcome(outcome_massege);
    }
    if(outcome == 2){
        std::string outcome_massege = getPotionsPurchaseMessage(player,result);
        printTurnOutcome(outcome_massege);
    }
    if(outcome == 3){
        std::string outcome_massege = getSolarEclipseMessage(player,result);
        printTurnOutcome(outcome_massege);
    }
}

//----------------------------------------------------------------------



//-------------------------------SORT THE LEADBORAD------------------------------------

//bool comparePlayers(const std::shared_ptr<Player>& player1, const std::shared_ptr<Player>& player2){
//    // Compare by level
//    if (player1->getLevel() != player2->getLevel()) {
//        return player1->getLevel() > player2->getLevel();  // Highest level first
//    }
//    // If levels are the same, compare by coins
//    if (player1->getCoins() != player2->getCoins()) {
//        return player1->getCoins() > player2->getCoins();  // Highest coins first
//    }
//    // If levels and coins are the same, compare by name
//    return player1->getName() < player2->getName();  // Alphabetical order by name
//}


void sortPlayers(vector<shared_ptr<Player>>& players) {
    // Using std::sort with custom comparator
    std::sort(players.begin(), players.end(),[](const std::shared_ptr<Player>& a
            , const std::shared_ptr<Player>& b) { return *a < *b ;}); // Use the Player's operator<
}


std::vector<shared_ptr<Player>> Make_Leader(vector<shared_ptr<Player>> Players){
   unsigned int PlayersLength=Players.size();  // unsigend????
    vector<shared_ptr<Player>> Leader;
    for(int i=10;i>-1;i--){
        for(int j=0;j<PlayersLength;j++){
            if(Players[j]->getLevel()==i){
                Leader.push_back(Players[j]);
            }
        }
    }
    sortPlayers(Leader);
    return Leader;
}

//-----------------------------CHECK IF GAMEOVER------------------------------------------------------

bool Player_Wins(const shared_ptr<vector<shared_ptr<Player>>>& Players) ///const& ??????
{
    int length=Players->size();
    for(int i=0;i<length;i++){
        if((*Players)[i]->getLevel()==10){
            return true;
        }
    }
    return false;
}

bool Players_Knocked_out(const shared_ptr<vector<shared_ptr<Player>>>& Players){
    int num=0;
    int length=Players->size();
    for(int i=0;i<length;i++){
        if((*Players)[i]->getHealthPoints() == 0){
            num++;
        }
    }
    length=Players->size();
    return length==num;
}

///-----------------------------------MATAMSTORY----------------------------------------------------//

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/

    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/

    /*============================================*/


    this->m_turnIndex = 1;
}

void MatamStory::playTurn(Player& player) {

    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the event
     * 4. Print the turn outcome with "printTurnOutcome"
    */

    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/

    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/

    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    return false; // Replace this line
    /*===================================================*/
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/

    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/

    /*========================================================================*/
}


MatamStory::~MatamStory() {
    delete Events_queue;
}