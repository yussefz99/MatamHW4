//
// Created by yusse on 08/08/2024.
//

#include "Snail.h"

Snail::Snail(): Encounter(Snail_COMPATPOWER,Snail_LOOT,Snail_DAMAGE){}

void Snail::make_move(Player &player) {
    if(player.CombatPower() > Snail_COMPATPOWER){
        player.add_level();
        player.add_coins(Snail_LOOT);
        if(player.get_job() == "Warrior"){
            int hp = player.getHealthPoints();
            player.set_HP(hp-10);
        }
        outcome=0;
    } else{
        int hp = player.getHealthPoints();
        player.set_HP(hp-Snail_DAMAGE);
        outcome=1;
    }
}

int Snail::Get_CombatPower() {
    return Snail_COMPATPOWER;
}

int Snail::Get_Loot() {
    return Snail_LOOT;
}

int Snail::Get_Damage() {
    return Snail_DAMAGE;
}

string Snail::getDescription() const {
    return  "Snail (power 5, loot 2, damage 10)";
}

int Snail::Get_OutCome() const {
    return outcome;
}