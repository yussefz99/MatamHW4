//
// Created by yusse on 04/08/2024.
//
#include <iostream>
#ifndef MATAMHW4_CHARACTER_H
#define MATAMHW4_CHARACTER_H

class Character{
public:
    Character()=default;
   // virtual int buy_hp(int* coins,int* hp)=0;
    virtual std::string get_Character()=0;
    virtual ~Character()=default;
};

#endif //MATAMHW4_CHARACTER_H
