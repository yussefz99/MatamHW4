//
// Created by yusse on 06/08/2024.
//
#include "Event.h"
#ifndef MATAMHW4_SPECIALEVENT_H
#define MATAMHW4_SPECIALEVENT_H

class SpecialEvent : public Event{
public:
    SpecialEvent()=default;
    virtual int make_move(Player &player)=0;
    virtual int Get_OutCome() const =0;
    virtual string getDescription() const=0;
    virtual ~SpecialEvent()=default; //override?
};

class SolarEclips : public SpecialEvent{
public:
    SolarEclips()=default;
    ~SolarEclips()override=default;
    string getDescription() const override{
        return "SolarEclipse";
    }
    int make_move(Player &player) override{
        outcome=3;
        if(player.get_job() == "Magician"){
            player.add_force(1);
            return 1;
        } else{
            player.add_force(-1);
            return -1;
        }
    }
    int Get_OutCome() const override{
        return outcome;
    }
};


class PotionsMerchant : public SpecialEvent{
public:
    PotionsMerchant()=default;
    ~PotionsMerchant()override=default;
    string getDescription() const override{
        return "PotionsMerchant";
    }
    int make_move(Player &player) override{
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
    int Get_OutCome() const override{
        return outcome;
    }
};



#endif //MATAMHW4_SPECIALEVENT_H
