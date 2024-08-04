//
// Created by yusse on 04/08/2024.
//
#include "Job.h"
#ifndef MATAMHW4_MAGICIAN_H
#define MATAMHW4_MAGICIAN_H
class Magician:public Job{
    Magician()=default;
    int combat_power(int force, int level) override;
    std::string get_job() override;
    ~Magician()override=default;
};

#endif //MATAMHW4_MAGICIAN_H
