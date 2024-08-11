
#pragma once

#include <string>
#include <utility>
#include <memory>
#include "Job.h"
#include "Character.h"
using std::string;

class Player {
public:
    Player(std::string& name, std::shared_ptr<Job> job,std::shared_ptr<Character> behavior);
    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const;

    int get_Maxhp() const;
    string get_job() const;
    string get_charecter()const;
    void set_HP(int hp);
    void set_force(int Newforce);
    void set_coins(int newCoins);
    void add_level();
    void add_coins(int coins);
    void add_force(int toAdd);
    int CombatPower()const;

    bool operator<(const Player& other)const;///operator < for sorted vector

private:
    std::string m_name;
    int m_level;
    int m_force;
    int m_currHP;
    int m_MaxHP;
    int m_coins;
    std::shared_ptr<Job> m_job;
    std::shared_ptr<Character> m_character;
};
