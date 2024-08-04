//
// Created by yusse on 04/08/2024.
//
#include "Archer.h"


int Archer::combat_power(int force, int level) {
    return force+level;
}

std::string Archer::get_job() {
    return "Archer";
}
