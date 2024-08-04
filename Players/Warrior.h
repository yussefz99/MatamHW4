//
// Created by yusse on 04/08/2024.
//
#include "Job.h"
#ifndef MATAMHW4_WARRIOR_H
#define MATAMHW4_WARRIOR_H

class Warrior :public Job{
public:
    Warrior()=default;
    int combat_power(int force, int level) override;
    std::string get_job() override;
    ~Warrior()override=default;
};

#endif //MATAMHW4_WARRIOR_H
