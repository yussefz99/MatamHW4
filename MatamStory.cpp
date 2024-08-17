
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
            , const std::shared_ptr<Player>& b) { return *a < *b ;}); // Use the Player operator<
}


std::vector<shared_ptr<Player>> MakeBoard(vector<shared_ptr<Player>> Players){
    vector<shared_ptr<Player>> Leader = Players;
    sortPlayers(Leader);
    std::reverse(Leader.begin(),Leader.end());
    return Leader;
}

//-----------------------------CHECK IF GAMEOVER------------------------------------------------------

bool IsWinner(const shared_ptr<vector<shared_ptr<Player>>>& Players)
{
    for(auto& player : *Players){
        if(player->getLevel()==10)return true;
    }
    return false;
}

bool AllOUT(const shared_ptr<vector<shared_ptr<Player>>>& Players){
    int num=0;
    for(auto& player : *Players){
        if(player->getHealthPoints() <= 0)num++;
    }
    int len = Players->size();
    return num == len;
}

//----------------------------------------setUp the constactor-------------------------------------------------

//----------------------

std::shared_ptr<Event> getEvant(const string& str){
    if(str == "Snail")return  std::make_shared<Snail>();
    if(str == "Slime")return  std::make_shared<Slime>();
    if(str == "Balrog")return  std::make_shared<Balrog>();
    if(str == "Pack")return  std::make_shared<Pack>();
    if(str == "SolarEclipse")return  std::make_shared<SolarEclips>();
    if(str == "PotionsMerchant")return  std::make_shared<PotionsMerchant>();
    return nullptr;
}

std::shared_ptr<Encounter> getEncounter(const string& str){
    if(str == "Snail")return  std::make_shared<Snail>();
    if(str == "Slime")return  std::make_shared<Slime>();
    if(str == "Balrog")return  std::make_shared<Balrog>();
    if(str == "Pack")return  std::make_shared<Pack>();
    return nullptr;
}

std::shared_ptr<Job> getJob(const std::string& str){
    if(str == "Warrior")return std::make_shared<Warrior>();
    if(str == "Archer")return std::make_shared<Archer>();
    if(str == "Magician")return std::make_shared<Magician>();
    return nullptr;
}

std::shared_ptr<Character> getCharcter(const std::string& str){
    if(str == "RiskTaking")return std::make_shared<RiskTaking>();
    if(str == "Responsible")return std::make_shared<Responsible>();
    return nullptr;
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


bool MakePack(vector<string> words,shared_ptr<vector<shared_ptr<Encounter>>>Members
              ,int wordsNum,int* index,int MemebersNum){

    if (MemebersNum < 2){
        throw EventExeption();
    }
    string current;
    bool flag=true;
    while(MemebersNum && *index < wordsNum){
        if(*index+1 >= wordsNum)throw EventExeption();
        *index=*index+1;
        current= words[*index];
        if(current == "Pack"){
            *index=*index+1;
            current= words[*index];
            if(!isNumber(current))throw EventExeption();
            flag=MakePack(words,Members,wordsNum,index,std::stoi(current));
            MemebersNum--;
            continue;
        }
        shared_ptr<Encounter> ptr= getEncounter(current);
        if(ptr == nullptr)throw EventExeption();
        Members->push_back(ptr);
        MemebersNum--;
    }
    if(MemebersNum != 0 || !flag)return false;
    return true;
}

void AddEvent(vector<string> words,std::queue<shared_ptr<Event>> *Events){
   string word;
    int index = 0;
    string current;
    int length=words.size();
    shared_ptr<vector<shared_ptr<Encounter>>> PackMembers(new vector<shared_ptr<Encounter>>) ;
    while (index < length) {
        current=words[index];
        if (isNumber(current)) {
            throw EventExeption();
        }
        shared_ptr<Event> ptr_Event= getEvant(current);
        if(ptr_Event == nullptr)throw EventExeption();
        Events->push(ptr_Event);
        index++;
        if (current == "Pack") {
            current = words[index];
            if (!isNumber(current)) {
                throw EventExeption();
            }
            try{
                MakePack(words,PackMembers,length,&index,std::stoi(current));
            }catch (EventExeption &e) {
                throw EventExeption();
            }
            shared_ptr<Event> myPack=std::make_shared<Pack>(*PackMembers,std::stoi(current));
            Events->back()=myPack;
            PackMembers->clear();
            index++;
        }
    }
}

void AddPlayers( shared_ptr<vector<shared_ptr<Player>>> Players,vector<string> words){
    string word , name, job,charcter;
    int index=0;
    int len = words.size();
    while (index < len){
        if(index+1 >= len)throw PlayersExeption();
        if(index+2 >= len)throw PlayersExeption();
        name = words[index];
        if(!isWord(name))throw PlayersExeption();
        if(name.size() > 15 || name.size() < 3)throw PlayersExeption();
        job = words[index+1];
        charcter = words[index+2];
        shared_ptr<Job> myJob = getJob(job);//jobMap[job];
        shared_ptr<Character> myCHarcter = getCharcter(charcter);//CharcterMap[charcter];
        if(myJob == nullptr || myCHarcter == nullptr)throw PlayersExeption();
        shared_ptr<Player> player1 = std::make_shared<Player>(name, myJob, myCHarcter);
        Players->push_back(player1);
        index+=3;
    }
}

///-----------------------------------MATAMSTORY----------------------------------------------------//




MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/
    vector<string> events_words;
    string event_word;
    string lineEvent, linePlayer;
    if(!eventsStream) {
        throw EventExeption();
    }
    auto *Events=new queue<shared_ptr<Event>>;
    while (std::getline(eventsStream,lineEvent)){
        std::istringstream lineStreamEvent(lineEvent); // Create a string stream for each line
        while (lineStreamEvent >> event_word){
            events_words.push_back(event_word);
        }
    }
    try {
        AddEvent(events_words,Events);
    }catch (...){
        delete Events;
        throw EventExeption();
    }
    if(Events->size() < 2 ) {
        delete Events;
        throw EventExeption();
    }

    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/
    vector<string> players_words;
    string player_word;
    shared_ptr<vector<shared_ptr<Player>>> Players(new vector<shared_ptr<Player>>) ;
    if(!playersStream){
        delete Events;
        throw PlayersExeption();
    }
    while (std::getline(playersStream,linePlayer)){
        std::istringstream lineStream(linePlayer); // Create a string stream for each line
        while (lineStream >> player_word){
            players_words.push_back(player_word);
        }
    }
    try{
        AddPlayers(Players,players_words);
    }catch (...){
        delete Events;
        throw PlayersExeption();
    }
    if(Players->size()<2 || Players->size() > 6){
        delete Events;
        throw PlayersExeption();
    }

    /*==========================================*/

    this->m_turnIndex = 1;
    this->Events_queue=Events;
    this->Players_Vec=Players;
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

    if (IsWinner(Players_Vec)){
        std::vector<shared_ptr<Player>> Leader_Board = MakeBoard(*Players_Vec);
        printWinner(*(Leader_Board[0]));
    } else if(AllOUT(Players_Vec))printNoWinners();
    /*========================================================================*/
}



MatamStory::~MatamStory() {
    delete Events_queue;
}