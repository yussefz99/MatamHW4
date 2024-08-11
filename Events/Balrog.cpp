//
// Created by yusse on 08/08/2024.
//

#include "Balrog.h"

Balrog::Balrog(): Encounter(Barlog_COMPATPOWER,Barlog_LOOT,Barlog_DAMAGE) {}

int Balrog::make_move(Player &player) {
    if(player.CombatPower() > CombatPower){
        player.add_level();
        player.add_coins(Barlog_LOOT);
        if(player.get_job() == "Warrior"){
            int hp = player.getHealthPoints();
            player.set_HP(hp-10);
        }
        outcome=0;
        CombatPower+=2;
        return Barlog_LOOT;
    } else{
        int hp = player.getHealthPoints();
        player.set_HP(hp-Barlog_DAMAGE);
        outcome=1;
        CombatPower+=2;
        return Barlog_DAMAGE;
    }
}

int Balrog::Get_CombatPower() {
    return CombatPower;
}

int Balrog::Get_Loot() {
    return Barlog_LOOT;
}

int Balrog::Get_Damage() {
    return Barlog_DAMAGE;
}

int Balrog::Get_OutCome() const {
    return outcome;
}

string Balrog::getDescription() const {
    return "Dragon (power "+ std::to_string(CombatPower) + ", loot 100, damage 9001)";
}


