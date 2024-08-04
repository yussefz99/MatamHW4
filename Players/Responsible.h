//
// Created by yusse on 04/08/2024.
//
#include "Character.h"
#ifndef MATAMHW4_RESPONSIBLE_H
#define MATAMHW4_RESPONSIBLE_H

class Responsible : public Character{
    Responsible()=default;
    std::string get_Character() override;
    ~Responsible()override=default;
};

#endif //MATAMHW4_RESPONSIBLE_H
