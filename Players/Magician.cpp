//
// Created by yusse on 04/08/2024.
//
#include "Magician.h"

int Magician::combat_power(int force, int level) {
    return force+level;
}

std::string Magician::get_job() {
    return "Magician";
}
