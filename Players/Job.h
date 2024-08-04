//
// Created by yusse on 04/08/2024.
//
#include <iostream>
#ifndef MATAMHW4_JOB_H
#define MATAMHW4_JOB_H

class Job{
public:
    Job()=default;
   // virtual bool ch_force(int* new_force)=0;
    virtual int combat_power(int force,int level)=0;
    virtual std::string get_job()=0;
    virtual ~Job()=default;
};

#endif //MATAMHW4_JOB_H
