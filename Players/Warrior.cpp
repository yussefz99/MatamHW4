//
// Created by yusse on 04/08/2024.
//
#include "Warrior.h"

int Warrior::combat_power(int force, int level) {
    return (force*2)+level;
}

std::string Warrior::get_job() {
    return "Warrior";
}



