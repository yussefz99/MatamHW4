//
// Created by yusse on 08/08/2024.
//
#include "Encounter.h"
#ifndef MATAMHW4_BALROG_H
#define MATAMHW4_BALROG_H

class Balrog : public Encounter{
public:
    static const int Barlog_COMPATPOWER=15;
    static const int Barlog_LOOT=100;
    static  const int Barlog_DAMAGE=9001;
    Balrog();
    void make_move(Player &player) override;
    int Get_CombatPower() override;
    int Get_Loot() override;
    int Get_Damage() override;
    int Get_OutCome() const override;
    string getDescription() const override;
    ~Balrog()override=default;
};

#endif //MATAMHW4_BALROG_H
