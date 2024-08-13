//
// Created by yusse on 04/08/2024.
//
#include <iostream>
#ifndef MATAMHW4_CHARACTER_H
#define MATAMHW4_CHARACTER_H

class Character{
public:
    Character()=default;
    virtual std::string get_Character()=0;
    virtual ~Character()=default;
};

///--------------------RESPONSIBLE CLASS------------------------

class Responsible : public Character{
public:
    Responsible()=default;
    std::string get_Character() override{
        return "Responsible";
    }
    ~Responsible()override=default;
};

///----------------RISKTACKING CLASS-----------------------

class RiskTaking:public Character{
public:
    RiskTaking()=default;
    std::string get_Character() override{
        return "RiskTaking";
    }
    ~RiskTaking()override=default;
};


#endif //MATAMHW4_CHARACTER_H
