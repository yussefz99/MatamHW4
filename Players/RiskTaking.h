//
// Created by yusse on 04/08/2024.
//
#include "Character.h"

#ifndef MATAMHW4_RISKTAKING_H
#define MATAMHW4_RISKTAKING_H

class RiskTaking:public Character{
public:
    RiskTaking()=default;
    std::string get_Character() override;
    ~RiskTaking()override=default;
};

#endif //MATAMHW4_RISKTAKING_H
