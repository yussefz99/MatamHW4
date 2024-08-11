//
// Created by yusse on 06/08/2024.
//

#include "PotionsMerchant.h"


int PotionsMerchant::Get_OutCome() const {
    return outcome;
}

int PotionsMerchant::make_move(Player &player) {
    std::string charcter = player.get_charecter();
    int player_coins = player.getCoins();
    int player_Maxhp = player.get_Maxhp();
    int player_Hp = player.get_Maxhp();
    outcome=2;
    int counter=0;
    if(charcter == "Responsible"){
        while (player_coins >= 5 && player_Hp < player_Maxhp){
            player_coins -= 5;
            player_Hp += 10;
            counter++;
        }
        player.set_HP(player_Hp);
        player.set_coins(player_coins);
        return counter;
    }
    if(charcter == "RiskTaking"){
        if(player_Hp < 50 && player_coins >= 5){
            player.set_coins(player_coins-5);
            player.set_HP(player_Hp+10);
            return 1;
        }
    }
    return 0;
}

string PotionsMerchant::getDescription() const {
    return "PotionsMerchant";
}


