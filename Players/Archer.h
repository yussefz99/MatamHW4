//
// Created by yusse on 04/08/2024.
//
#include "Job.h"
#ifndef MATAMHW4_ARCHER_H
#define MATAMHW4_ARCHER_H

class Archer : public Job{
public:
    Archer()=default;
    int combat_power(int force, int level) override;
    std::string get_job() override;
    ~Archer()override=default;
};

#endif //MATAMHW4_ARCHER_H
