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

///----------------ARCHER CLASS------------------------

class Archer : public Job{
public:
    Archer()=default;
    int combat_power(int force, int level) override{
        return force+level;

    }
    std::string get_job() override{
        return "Archer";

    }
    ~Archer()override=default;
};

///------------------MAGICIAN CLASS-----------------------------

class Magician:public Job{
public:
    int combat_power(int force, int level) override{
        return force+level;

    }
    std::string get_job() override{
        return "Magician";
    }
    ~Magician()override=default;
    Magician()=default;
};

///---------------------WARRIOR CLASS--------------------------

class Warrior :public Job{
public:
    Warrior()=default;
    int combat_power(int force, int level) override{
        return (force*2)+level;
    }
    std::string get_job() override{
        return "Warrior";
    }
    ~Warrior()override=default;
};
#endif //MATAMHW4_JOB_H
