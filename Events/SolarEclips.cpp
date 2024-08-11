//
// Created by yusse on 06/08/2024.
//

#include "SolarEclips.h"


int SolarEclips::Get_OutCome() const {
    return outcome;
}

int SolarEclips::make_move(Player &player) {
    outcome=3;
    if(player.get_job() == "Magician"){
        player.add_force(1);
        return 1;
    } else{
        player.add_force(-1);
        return -1;
    }
}

string SolarEclips::getDescription() const {
    return "SolarEclip";
}

