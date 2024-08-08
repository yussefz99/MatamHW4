//
// Created by yusse on 06/08/2024.
//
#include "Event.h"
#ifndef MATAMHW4_SPECIALEVENT_H
#define MATAMHW4_SPECIALEVENT_H

class SpecialEvent : public Event{
public:
    SpecialEvent()=default;
    virtual void make_move(Player &player)=0;
    virtual int Get_OutCome() const =0;
    virtual string getDescription() const=0;
    virtual ~SpecialEvent()=default; //override?
};

#endif //MATAMHW4_SPECIALEVENT_H
