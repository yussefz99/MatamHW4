//
// Created by yusse on 06/08/2024.
//

#include "SolarEclips.h"


int SolarEclips::Get_OutCome() const {
    return outcome;
}

void SolarEclips::make_move(Player &player) {
    if(player.get_job() == "Magician"){
        player.add_force(1);
    } else{
        player.add_force(-1);
    }
    outcome=4;
}

string SolarEclips::getDescription() const {
    return "SolarEclip";
}

