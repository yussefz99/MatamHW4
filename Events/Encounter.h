//
// Created by yusse on 08/08/2024.
//
#include "Event.h"
#include "memory"
#include <string>
#include <vector>
#ifndef MATAMHW4_ENCOUNTER_H
#define MATAMHW4_ENCOUNTER_H

class Encounter : public Event{
public:
    Encounter(const int CombatPower,const int Loot,const int Damage):CombatPower(CombatPower)
            ,Loot(Loot),Damage(Damage){}
    virtual int make_move(Player &player)=0;
    virtual int Get_OutCome()const=0;
    virtual int Get_CombatPower()=0;
    virtual int Get_Loot()=0;
    virtual int Get_Damage()=0;
    virtual string getDescription() const=0;
    virtual ~Encounter()=default;
protected:
    int CombatPower;
    int Loot;
    int Damage;
};

///----------------BALROG CLASS----------------------------

class Balrog : public Encounter{
public:
    static const int Barlog_COMPATPOWER=15;
    static const int Barlog_LOOT=100;
    static  const int Barlog_DAMAGE=9001;
    Balrog(): Encounter(Barlog_COMPATPOWER,Barlog_LOOT,Barlog_DAMAGE) {}
    int make_move(Player &player) override{
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
    int Get_CombatPower() override{
        return CombatPower;
    }
    int Get_Loot() override{
        return Barlog_LOOT;
    }
    int Get_Damage() override{
        return Barlog_DAMAGE;
    }
    int Get_OutCome() const override{
        return outcome;
    }
    string getDescription() const override{
        return "Balrog (power "+ std::to_string(CombatPower) + ", loot 100, damage 9001)";
    }
    ~Balrog()override=default;
};

///--------------------------------SNAIL CLASS-------------------------

class Snail : public Encounter{
public:
    static const int Snail_COMPATPOWER=5;
    static const int Snail_LOOT=2;
    static  const int Snail_DAMAGE=10;
    Snail():Encounter(Snail_COMPATPOWER,Snail_LOOT,Snail_DAMAGE){}
    int make_move(Player &player) override{
        if(player.CombatPower() > Snail_COMPATPOWER){
            player.add_level();
            player.add_coins(Snail_LOOT);
            if(player.get_job() == "Warrior"){
                int hp = player.getHealthPoints();
                player.set_HP(hp-10);
            }
            outcome=0;
            return Snail_LOOT;
        } else{
            int hp = player.getHealthPoints();
            player.set_HP(hp-Snail_DAMAGE);
            outcome=1;
            return Snail_DAMAGE;
        }
    }
    int Get_CombatPower() override{
        return Snail_COMPATPOWER;
    }
    int Get_Loot() override{
        return Snail_LOOT;
    }
    int Get_Damage() override{
        return Snail_DAMAGE;
    }
    int Get_OutCome() const override{
        return outcome;
    }
    string getDescription() const override{
        return  "Snail (power 5, loot 2, damage 10)";
    }
    ~Snail()override=default;
};

///------------------SLIME CLASS----------------------------

class Slime : public Encounter{
public:
    static const int Slime_COMPATPOWER=12;
    static const int Slime_LOOT=5;
    static  const int Slime_DAMAGE=25;
    Slime():Encounter(Slime_COMPATPOWER,Slime_LOOT,Slime_DAMAGE){}
    int make_move(Player &player) override{
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
    int Get_CombatPower() override{
        return Slime_COMPATPOWER;

    }
    int Get_Loot() override{
        return Slime_LOOT;
    }
    int Get_Damage() override{
        return Slime_DAMAGE;
    }
    int Get_OutCome() const override{
        return outcome;
    }
    string getDescription() const override{
        return "Slime (power 12, loot 5, damage 25)";
    }
    ~Slime()override=default;
};

///-------------------------PACK CLASS-------------------------

class Pack : public Encounter{
private:
    int pack_num;
public:
    Pack(const std::vector<std::shared_ptr<Encounter>>& Pack_Members,int num):
            Encounter(0,0,0),pack_num(num){
        int Pack_CombatPower=0;
        int Pack_Loot=0;
        int Pack_Damage=0;
        for(auto & Pack_Member : Pack_Members){
            Pack_CombatPower+=Pack_Member->Get_CombatPower();
            Pack_Loot+=Pack_Member->Get_Loot();
            Pack_Damage+=Pack_Member->Get_Damage();
        }
        CombatPower = Pack_CombatPower;
        Loot = Pack_Loot;
        Damage = Pack_Damage;
    }
    int make_move(Player &player) override{
        if(player.CombatPower() > CombatPower){
            player.add_level();
            player.add_coins(Loot);
            if(player.get_job() == "Warrior"){
                int hp = player.getHealthPoints();
                player.set_HP(hp-10);
            }
            outcome=0;
            return Loot;
        } else{
            int hp = player.getHealthPoints();
            player.set_HP(hp-Damage);
            outcome=1;
            return Damage;
        }
    }
    int Get_CombatPower() override{
        return CombatPower;
    }
    int Get_Loot() override{
        return Loot;
    }
    int Get_Damage() override{
        return Damage;
    }
    int Get_OutCome() const override{
        return outcome;
    }
    string getDescription() const override{
        return  "Pack of "+std::to_string(pack_num)+" members (power "+std::to_string(CombatPower)+
                ", loot "+std::to_string(Loot)+", damage "+std::to_string(Damage)+")";
    }
    ~Pack()override=default;
};

#endif //MATAMHW4_ENCOUNTER_H
