
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


string GetStr(string line,int* index){
    string current;
    int i=*index;
    int length=line.size();
    if(*index >= length){
        return "";
    }
    while(( line[*index] != ' ' && line[*index]!='\n') && *index < length ){
        (*index)++;
    }
    current=line.substr(i,(*index)-i);
    if(current.back() == 13){
        current.pop_back();
    }
    return current;
}

int NewIndex(int index,string line){
    int length=line.size();
    while(index<length && (line[index] == ' ' || line[index] == '\n')){
        index++;
    }
    return index;
}


bool MakePack(string line,int MemebersNum,shared_ptr<vector<shared_ptr<Encounter>>>Members,int* index
              , std::map<string,shared_ptr<Event>> CardsMap) {

    if (MemebersNum < 2){
        throw EventExeption();
    }
    string current;
    bool flag=true;
    while(MemebersNum && line[*index]){
        *index= NewIndex(*index,line);
        current= GetStr(line,index);
        if(current == "Pack"){
            *index= NewIndex(*index,line);
            current= GetStr(line,index);
            if(!isNumber(current)){
                throw EventExeption();
            }
            flag=MakePack(line,std::stoi(current),Members, index, CardsMap);
            MemebersNum--;
            continue;
        }
        std::map<string, shared_ptr<Encounter>> EncounterMap=GetEncounterMap();
        auto it = EncounterMap.find(current);
        if (it != EncounterMap.end()) {
            Members->push_back(EncounterMap[current]);
        } else {
            throw EventExeption();
        }
        MemebersNum--;
    }
    if(MemebersNum != 0 || !flag){
        return false;
    }
    return true;
}


void fillQueue(string line,std::queue<shared_ptr<Event>> *Cards){
    int index = 0;
    string current;
    int length=line.size();
    std::map<string, shared_ptr<Event>> CardsMap = GetEventMap();
    shared_ptr<vector<shared_ptr<Encounter>>> GangMembers(new vector<shared_ptr<Encounter>>) ;
    while (index < length) {
        current="";
        index = NewIndex(index, line);
        current += GetStr(line, &index);
        if(current == ""){
            break;
        }
        if (isNumber(current) == true) {
            throw EventExeption();
        }
        auto it = CardsMap.find(current);
        if (it != CardsMap.end()) {
            Cards->push(CardsMap[current]);
        } else {
            throw EventExeption();
        }
        if (current == "Pack") {
            index = NewIndex(index, line);
            current = GetStr(line, &index);
            if (!isNumber(current)) {
                throw EventExeption();
            }
            try{
                MakePack(line,std::stoi(current),GangMembers,&index,CardsMap);
            }catch (std::out_of_range& e) {
                throw EventExeption();
            }
            shared_ptr<Pack> myGang=std::make_shared<Pack>(*GangMembers,std::stoi(current));
            Cards->back()=myGang;//Gang constructor
            GangMembers->clear();
        }
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

//    string line;
//    if(!eventsStream) {
//        throw EventExeption();
//    }
//    auto *Events=new queue<shared_ptr<Event>>;
//    std::map<string, shared_ptr<Event>> EventMap = GetEventMap();
//    while (std::getline(eventsStream,line)) {
//        std::istringstream lineStream(line); // Create a string stream for each line
//        std::string word;
//        vector<string> words;
//        while (lineStream >> word) {  // Read each word in the line
//            words.push_back(word);
//        }
//        if(words[0] == "Pack"){
//            shared_ptr<vector<shared_ptr<Encounter>>> PackMembers(new vector<shared_ptr<Encounter>>);
//            MakePack(words,PackMembers);
//            shared_ptr<Pack> myPack=std::make_shared<Pack>(*PackMembers,std::stoi(words[1]));
//            Events->back()=myPack;//Gang constructor
//            PackMembers->clear(); // ?????
//        } else{
//            auto it = EventMap.find(words[0]);
//            if(it == EventMap.end()){
//                throw EventExeption();
//            }
//            shared_ptr<Event> event = EventMap[words[0]];
//        }
//    }



MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/

    string line, singleLine="";
    if(!eventsStream) {
        throw EventExeption();
    }

    typename std::queue<shared_ptr<Event>> *Events=new queue<shared_ptr<Event>>;
    while (std::getline(eventsStream,line)){
        singleLine += line;
        if(singleLine.back() == '\n'){
            singleLine.pop_back();
        }
        singleLine+=" ";
    }

    try{
        fillQueue(singleLine,Events);
    }catch (EventExeption& e){
        delete Events;
        throw;
    }
    if(Events->size() < 2 ){
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