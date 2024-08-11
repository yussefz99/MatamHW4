//
// Created by yusse on 08/08/2024.
//
#include "Event.h"
#include "memory"
#include <string>
#include <vector>
#ifndef MATAMHW4_ENCOUNTER_H
#define MATAMHW4_ENCOUNTER_H

class Encounter : public Event{
public:
    Encounter(const int CombatPower,const int Loot,const int Damage);
    virtual int make_move(Player &player)=0;
    virtual int Get_OutCome()const=0;
    virtual int Get_CombatPower()=0;
    virtual int Get_Loot()=0;
    virtual int Get_Damage()=0;
    virtual string getDescription() const=0;
    virtual ~Encounter()=default;
protected:
    int CombatPower;
    int Loot;
    int Damage;
};

#endif //MATAMHW4_ENCOUNTER_H
