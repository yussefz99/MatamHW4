//
// Created by yusse on 08/08/2024.
//
#include "Encounter.h"
#ifndef MATAMHW4_SNAIL_H
#define MATAMHW4_SNAIL_H


class Snail : public Encounter{
public:
    static const int Snail_COMPATPOWER=5;
    static const int Snail_LOOT=2;
    static  const int Snail_DAMAGE=10;
    Snail();
    void make_move(Player &player) override;
    int Get_CombatPower() override;
    int Get_Loot() override;
    int Get_Damage() override;
    int Get_OutCome() const override;
    string getDescription() const override;
    ~Snail()override=default;
};

#endif //MATAMHW4_SNAIL_H
