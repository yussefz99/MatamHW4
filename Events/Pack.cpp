//
// Created by yusse on 08/08/2024.
//

#include "Pack.h"

Pack::Pack(std::vector<std::shared_ptr<Encounter>> Pack_Members, int num):
Encounter(0,0,0),pack_num(num){
        int Pack_CombatPower=0;
        int Pack_Loot=0;
        int Pack_Damage=0;
        for(auto & Pack_Member : Pack_Members){
            Pack_CombatPower+=Pack_Member->Get_CombatPower();
            Pack_CombatPower+=Pack_Member->Get_Loot();
            Pack_CombatPower+=Pack_Member->Get_Damage();
        }
        CombatPower = Pack_CombatPower;
        Loot = Pack_Loot;
        Damage = Pack_Damage;
}

void Pack::make_move(Player &player) {
    if(player.CombatPower() > CombatPower){
        player.add_level();
        player.add_coins(Loot);
        if(player.get_job() == "Warrior"){
            int hp = player.getHealthPoints();
            player.set_HP(hp-10);
        }
        outcome=0;
    } else{
        int hp = player.getHealthPoints();
        player.set_HP(hp-Damage);
        outcome=1;
    }
}

int Pack::Get_CombatPower() {
    return CombatPower;
}

int Pack::Get_OutCome() const {
    return outcome;
}

int Pack::Get_Damage() {
    return Damage;
}

int Pack::Get_Loot() {
    return Loot;
}

string Pack::getDescription() const {
    return  "Pack of "+std::to_string(pack_num)+" members (power "+std::to_string(CombatPower)+
                  ", loot "+std::to_string(Loot)+", damage "+std::to_string(Damage)+")";
}


