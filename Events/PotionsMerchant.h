//
// Created by yusse on 06/08/2024.
//
#include "SpecialEvent.h"
#ifndef MATAMHW4_POTIONSMERCHANT_H
#define MATAMHW4_POTIONSMERCHANT_H

class PotionsMerchant : public SpecialEvent{
    PotionsMerchant()=default;
    ~PotionsMerchant()override=default;
    string getDescription() const override;
    int make_move(Player &player) override;
    int Get_OutCome() const override;
};

#endif //MATAMHW4_POTIONSMERCHANT_H
