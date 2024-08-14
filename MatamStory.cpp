
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


void sortPlayers(vector<shared_ptr<Player>>& players) {
    // Using std::sort with custom comparator
    std::sort(players.begin(), players.end(),[](const std::shared_ptr<Player>& a
            , const std::shared_ptr<Player>& b) { return *a < *b ;}); // Use the Player's operator<
}


std::vector<shared_ptr<Player>> MakeBoard(vector<shared_ptr<Player>> Players){
    vector<shared_ptr<Player>> Leader = Players;
    sortPlayers(Leader);
    std::reverse(Leader.begin(),Leader.end());
    return Leader;
}

//-----------------------------CHECK IF GAMEOVER------------------------------------------------------

bool IsWinner(const shared_ptr<vector<shared_ptr<Player>>>& Players) ///const& ??????
{
    for(auto& player : *Players){
        if(player->getLevel()==10)return true;
    }
    return false;
}

bool AllOUT(const shared_ptr<vector<shared_ptr<Player>>>& Players){
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

//----------------------------------------setUp the constactor-------------------------------------------------


/// Maps for code simlifiction

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
    myMap["Archer"] =std::make_shared<Archer>();
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


void MakePack(vector<string> words,shared_ptr<vector<shared_ptr<Encounter>>>Members
              , std::map<string,shared_ptr<Event>> EventsMap,int index,int membersNum){
    if(membersNum < 2)throw EventExeption();
    int len = words.size();
    while (membersNum != 0 && index < len){
        if(words[index] == "Pack"){
            if(!isNumber(words[index+1]))throw EventExeption();
            if(std::stoi(words[index+1]) < 2)throw EventExeption();
            //makepck(words,Members,EventsMap,index+2,std::stoi(words[index+1]));
            index+=2;
            membersNum--;
        } else{
            std::map<string, shared_ptr<Encounter>> EncounterMap=GetEncounterMap();
            auto it = EncounterMap.find(words[index]);
            if (it != EncounterMap.end()) {
                Members->push_back(EncounterMap[words[index]]);
            } else {
                throw EventExeption();
            }
            membersNum--;
            index++;
        }
    }
}

void AddEvent(std::istringstream& line,std::queue<shared_ptr<Event>> *Events){
    shared_ptr<vector<shared_ptr<Encounter>>> PackMembers(new vector<shared_ptr<Encounter>>) ;
    std::map<string, shared_ptr<Event>> EventsMap = GetEventMap();
    string word;
    vector<string> words;
    while (line >> word){
        words.push_back(word);
    }
    if(words.size()==1){
        if(!isWord(words[0]))throw EventExeption();
        auto it = EventsMap.find(words[0]);
        if(it == EventsMap.end())throw EventExeption();
        Events->push(EventsMap[words[0]]);
    } else if(words[0] == "Pack"){
        if(!isNumber(words[1]))throw EventExeption();
        int num = std::stoi(words[1]);
        MakePack(words,PackMembers,EventsMap,0,num+1); // try and catch????? +111111???
        shared_ptr<Pack> myPack=std::make_shared<Pack>(*PackMembers,num);
        Events->push(myPack);//Gang constructor
        PackMembers->clear();
    }
    else{
        throw EventExeption();
    }
}

void AddPlayers( shared_ptr<vector<shared_ptr<Player>>> Players,std::istringstream& line){
    string word , name, job,charcter;
    std::map<std::string, shared_ptr<Character>> CharcterMap = GetCharcterMap();
    std::map<std::string, shared_ptr<Job>> jobMap = GetJobMap();
    int count=0;
    while (line >> word){
        if(count == 0)name=word;
        if(count==1)job=word;
        if(count==2)charcter=word;
        count++;
    }
    if(!isWord(name)){
        throw PlayersExeption();
    }
    if(name.size() > 15 || name.size() < 3){
        throw PlayersExeption();
    }
    auto it_jop = jobMap.find(job);
    if (it_jop == jobMap.end()) {
        throw PlayersExeption();
    }
    auto it_charcter = CharcterMap.find(charcter);
    if (it_charcter == CharcterMap.end()) {
        throw PlayersExeption();
    }
    shared_ptr<Job> myJob = jobMap[job];
    shared_ptr<Character> myCHarcter = CharcterMap[charcter];
    shared_ptr<Player> player1 = std::make_shared<Player>(name, myJob, myCHarcter);
    Players->push_back(player1);
}

///-----------------------------------MATAMSTORY----------------------------------------------------//


MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/

    string lineEvent, linePlayer;
    if(!eventsStream) {
        throw EventExeption();
    }
    typename std::queue<shared_ptr<Event>> *Events=new queue<shared_ptr<Event>>;
    while (std::getline(eventsStream,lineEvent)){
        std::istringstream lineStreamEvent(lineEvent); // Create a string stream for each line
        try {
            AddEvent(lineStreamEvent,Events);
        }catch (...){
            delete Events;
            throw EventExeption();
        }
    }
    if(Events->size() < 2 ) {
        delete Events;
        throw EventExeption();
    }

    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/
    shared_ptr<vector<shared_ptr<Player>>> Players(new vector<shared_ptr<Player>>) ;
    if(!playersStream){
        delete Events;
        throw PlayersExeption();
    }
    while (std::getline(playersStream,linePlayer)){
        std::istringstream lineStream(linePlayer); // Create a string stream for each line
        try{
            AddPlayers(Players,lineStream);
        }catch (...){
            delete Events;
            throw PlayersExeption();
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
    Event* curr_Event = Events_queue->front().get();
    printTurnDetails(m_turnIndex,player,*curr_Event);
    int res=curr_Event->make_move(player);
    Events_queue->push(Events_queue->front());
    Events_queue->pop();
    int outcome=curr_Event->Get_OutCome();
    print_Outcome(player,res,outcome);
    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/
    for(auto& player : *Players_Vec){
        if(player->getHealthPoints() != 0){
            playTurn(*player);
        }
    }
    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();
    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
    std::vector<shared_ptr<Player>> Leader_Board=MakeBoard(*Players_Vec);
    int len =Players_Vec->size();
    for(int i=0 ; i<len;i++){
        printLeaderBoardEntry(i+1,*(Leader_Board[i]));
    }
    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    if(IsWinner(Players_Vec) || AllOUT(Players_Vec))return true;
    return false; // Replace this line
    /*===================================================*/
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/
    int len =Players_Vec->size();
    for(int i=0;i<len;i++) {
        printStartPlayerEntry(i+1, *((*Players_Vec)[i]));
    }
    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/

    if (AllOUT(Players_Vec))printNoWinners();
    if (IsWinner(Players_Vec)){
        std::vector<shared_ptr<Player>> Leader_Board = MakeBoard(*Players_Vec);
        printWinner(*(Leader_Board[0]));
    }
    /*========================================================================*/
}


MatamStory::~MatamStory() {
    delete Events_queue;
}