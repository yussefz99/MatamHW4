
#include "MatamStory.h"
#include "Utilities.h"


class EventExeption :public exception{
public:
    const char* what()const noexcept override{
        return "Invalid Events File";
    }
};

class PlayersExeption :public exception{
public:
    const char* what()const noexcept override{
        return "Invalid Players File";
    }
};





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
    vector<shared_ptr<Player>> Leader = Players;
//    for(int i=10;i>-1;i--){
//        for(int j=0;j<PlayersLength;j++){
//            if(Players[j]->getLevel()==i){
//                Leader.push_back(Players[j]);
//            }
//        }
//    }
    sortPlayers(Leader);
    return Leader;
}

//-----------------------------CHECK IF GAMEOVER------------------------------------------------------

bool Player_Wins(const shared_ptr<vector<shared_ptr<Player>>>& Players) ///const& ??????
{
//    int length=Players->size();
//    for(int i=0;i<length;i++){
//        if((*Players)[i]->getLevel()==10){
//            return true;
//        }
//    }
    for(auto& player : *Players){
        if(player->getLevel()==10)return true;
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

//----------------------------------------set up-------------------------------------------------


std::map<string,shared_ptr<Event>> GetEventMap(){
    typename std::map<std::string,shared_ptr<Event>> Eventmap;
    Eventmap["Snail"] = std::make_shared<Snail>();
    Eventmap["Slime"] =  std::make_shared<Slime>();
    Eventmap["Balrog"] =  std::make_shared<Balrog>();
    Eventmap["Pack"] = nullptr;
    Eventmap["SolarEclipse"] =  std::make_shared<SolarEclips>();
    Eventmap["PotionsMerchant"] =std::make_shared<PotionsMerchant>();
    return Eventmap;
}
std::map<string,shared_ptr<Encounter>> GetEncounterMap(){
    typename std::map<std::string,shared_ptr<Encounter>> Encountermap;
    Encountermap["Snail"] = std::make_shared<Snail>();
    Encountermap["Slime"] =  std::make_shared<Slime>();
    Encountermap["Balrog"] =  std::make_shared<Balrog>();
    Encountermap["Pack"] = nullptr;
    return Encountermap;
}

std::map<std::string,shared_ptr<Character>> GetCharcterMap(){
    typename std::map<std::string,shared_ptr<Character>> myMap;
    myMap["RiskTaking"] = std::make_shared<RiskTaking>();
    myMap["Responsible"] = std::make_shared<Responsible>();
    return myMap;
}
std::map<std::string,shared_ptr<Job>> GetJobMap(){
    typename std::map<std::string,shared_ptr<Job>> myMap;
    myMap["Warrior"] =std::make_shared<Warrior>();
    myMap["Sorcerer"] =std::make_shared<Archer>();
    myMap["Magician"] =std::make_shared<Magician>();
    return myMap;
}


bool isNumber(string str){
    int i=0;
    while (str[i]){
        if( str[i]< 48 || str[i]>57)return false;
        i++;
    }
    return true;
}

bool isWord(string str){
    int i=0;
    while (str[i]){
        if(!(str[i]>= 65 && str[i]<= 90) && !(str[i]>= 97 && str[i]<= 122))return false;
        i++;
    }
    return true;
}


void MakePack( std::istringstream lineStream,shared_ptr<vector<shared_ptr<Encounter>>>Members){
    std::string packWord;
    int count=0;
    std::map<string, shared_ptr<Encounter>> EncounterMap=GetEncounterMap();
    shared_ptr<vector<shared_ptr<Encounter>>> PackMembers(new vector<shared_ptr<Encounter>>);
    while (lineStream >> packWord){
        if(count == 1){
            if(!isNumber(packWord)){
                throw EventExeption();
            }
            int number = std::stoi(packWord);
            if(number < 2){
                throw EventExeption();
            }
        }
        if(count > 1){
            if(isWord(packWord)){
                throw EventExeption();
            }
            auto it = EncounterMap.find(packWord);
            if(it != EncounterMap.end()){
                PackMembers->push_back(EncounterMap[packWord]);
            } else{
                throw EventExeption();
            }
        }
        count++;
    }
}

void MakeEventsQueue(string line,std::queue<shared_ptr<Event>> *Cards){

}

void AddPlayers( shared_ptr<vector<shared_ptr<Player>>> Players,std::istringstream& line){
    string word , name, job,charcter;
    std::map<std::string, shared_ptr<Character>> behaviorMap = GetCharcterMap();
    std::map<std::string, shared_ptr<Job>> jobMap = GetJobMap();
    int count=0;
    while (line >> word){
        if(count == 0)name=word;
        if(count==1)job=word;
        if(count==2)charcter=word;
        count++;
    }
    if(!isWord(word)){
        throw PlayersExeption();
    }
    if(name.size() > 15 || name.size() < 3){
        throw PlayersExeption();
    }
    auto it_jop = jobMap.find(job);
    if (it_jop == jobMap.end()) {
        throw PlayersExeption();
    }
    auto it_charcter = behaviorMap.find(charcter);
    if (it_charcter == behaviorMap.end()) {
        throw PlayersExeption();
    }
    shared_ptr<Job> myJob = jobMap[job];
    shared_ptr<Character> myBehavior = behaviorMap[charcter];
    shared_ptr<Player> player1 = std::make_shared<Player>(name, myJob, myBehavior);
    Players->push_back(player1);
}

///-----------------------------------MATAMSTORY----------------------------------------------------//

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/
    string line;
    if(!eventsStream) {
        throw EventExeption();
    }
    auto *Events=new queue<shared_ptr<Event>>;
    while (std::getline(eventsStream,line)){
        std::istringstream lineStream(line); // Create a string stream for each line
        std::string word;
        std::map<string, shared_ptr<Event>> EventMap = GetEventMap();
        while (lineStream >> word) {  // Read each word in the line
            if(word != "Pack"){
                if(!isWord(word)){
                    throw EventExeption();
                }
                auto it = EventMap.find(word);
                if(it != EventMap.end()){
                    Events->push(EventMap[word]);
                } else{
                    throw EventExeption();
                }
            } else{

            }
        }
    }
    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/
    shared_ptr<vector<shared_ptr<Player>>> Players(new vector<shared_ptr<Player>>) ;
    if(!playersStream){
        delete Events;
        throw PlayersExeption();
    }
    while (std::getline(playersStream,line)){
        std::istringstream lineStream(line); // Create a string stream for each line
        try{
            AddPlayers(Players,lineStream);
        }catch (PlayersExeption& e){
            delete Events;
            throw;
        }
    }
    if(Players->size()<2 || Players->size() > 6){
        delete Events;
        throw PlayersExeption();
    }
    
    /*============================================*/

    this->Events_queue=Events;
    this->Players_Vec=Players;
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