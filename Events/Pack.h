//
// Created by yusse on 08/08/2024.
//
#include "Encounter.h"
#ifndef MATAMHW4_PACK_H
#define MATAMHW4_PACK_H

class Pack : public Encounter{
private:
    int pack_num;
public:
    Pack(std::vector<std::shared_ptr<Encounter>> Pack_Members,int num);
    int make_move(Player &player) override;
    int Get_CombatPower() override;
    int Get_Loot() override;
    int Get_Damage() override;
    int Get_OutCome() const override;
    string getDescription() const override;
    ~Pack()override=default;

};

#endif //MATAMHW4_PACK_H
