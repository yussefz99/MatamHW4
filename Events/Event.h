
#pragma once

#include "../Players/Player.h"

class Event {  //intilaze outcome
public:
    Event()=default;
    virtual int Get_OutCome();
    virtual void make_move(Player &player)=0;
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const=0;
    virtual ~Event()=default;

protected:
    int outcome;
};
