//
// Created by yusse on 08/08/2024.
//
#include "Encounter.h"
#ifndef MATAMHW4_SLIME_H
#define MATAMHW4_SLIME_H

class Slime : public Encounter{
public:
    static const int Slime_COMPATPOWER=12;
    static const int Slime_LOOT=5;
    static  const int Slime_DAMAGE=25;
    Slime();
    int make_move(Player &player) override;
    int Get_CombatPower() override;
    int Get_Loot() override;
    int Get_Damage() override;
    int Get_OutCome() const override;
    string getDescription() const override;
    ~Slime()override=default;
};

#endif //MATAMHW4_SLIME_H
