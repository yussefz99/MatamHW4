//
// Created by yusse on 08/08/2024.
//

#include "Slime.h"

Slime::Slime(): Encounter(Slime_COMPATPOWER,Slime_LOOT,Slime_DAMAGE){}


int Slime::make_move(Player &player) {
    if(player.CombatPower() > Slime_COMPATPOWER){
        player.add_level();
        player.add_coins(Slime_LOOT);
        if(player.get_job() == "Warrior"){
            int hp = player.getHealthPoints();
            player.set_HP(hp-10);
        }
        outcome=0;
        return Slime_LOOT;
    } else{
        int hp = player.getHealthPoints();
        player.set_HP(hp-Slime_DAMAGE);
        outcome=1;
        return Slime_DAMAGE;
    }
}

int Slime::Get_OutCome() const {
    return outcome;
}

int Slime::Get_Damage() {
    return Slime_DAMAGE;
}

int Slime::Get_Loot() {
    return Slime_LOOT;
}

int Slime::Get_CombatPower() {
    return Slime_COMPATPOWER;
}

string Slime::getDescription() const {
    return "Slime (power 12, loot 5, damage 25)";
}


