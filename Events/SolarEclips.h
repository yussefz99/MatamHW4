//
// Created by yusse on 06/08/2024.
//
#include "SpecialEvent.h"
#ifndef MATAMHW4_SOLARECLIPS_H
#define MATAMHW4_SOLARECLIPS_H

class SolarEclips : public SpecialEvent{
    SolarEclips()=default;
    ~SolarEclips()override=default;
    string getDescription() const override;
    int make_move(Player &player) override;
    int Get_OutCome() const override;
};


#endif //MATAMHW4_SOLARECLIPS_H
