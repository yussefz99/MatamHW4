//
// Created by yusse on 04/08/2024.
//
#include "Player.h"

#include <utility>

Player::Player(std::string& name,std::shared_ptr<Job> job,std::shared_ptr<Character> character):m_name(name),m_level(1)
        ,m_force(5),m_currHP(100),m_MaxHP(100),m_coins(10),m_job(std::move(job)),m_character(std::move(character)){ //moveee??
    if(m_job->get_job() == "Warrior"){
        m_MaxHP=150;
        m_currHP=150;
    }
    if(m_job->get_job() == "Archer")m_coins=20;
}

string Player::getName() const {
    return m_name;
}

string Player::getDescription() const {
    return getName() + ", " + m_job->get_job() + " with " + m_character->get_Character()
    + " character (level " + std::to_string(getLevel()) +", force " + std::to_string(getForce()) + ")";
}

int Player::getCoins() const {
    return m_coins;
}

int Player::getForce() const {
    return m_force;
}

int Player::getLevel() const {
    return m_level;
}

int Player::getHealthPoints() const {
    return m_currHP;
}

string Player::get_job() const {
    return m_job->get_job();
}

string Player::get_charecter() const {
    return m_character->get_Character();
}

int Player::get_Maxhp() const {
    return m_MaxHP;
}

void Player::set_HP(int hp) {
    if(hp > m_MaxHP){
        this->m_currHP=m_MaxHP;
    } else{
        this->m_currHP=hp;
    }
   if(hp < 0)m_currHP=0;
}

void Player::set_force(int Newforce) {
    this->m_force=Newforce;
}

void Player::set_coins(int newCoins) {
    m_coins=newCoins;
}

int Player::CombatPower() const {
    return m_job->combat_power(m_force,m_level);
}

void Player::add_coins(int coins) {
    m_coins+=coins;
}
void Player::add_level() {
    if(this->m_level < 10){
        m_level++;
    }
}

void Player::add_force(int toAdd) {
    m_force+=toAdd;
    if(m_force < 0)m_force=0;
}

bool Player::operator<(const Player &other) const {
    if (m_level != other.m_level) {
        return m_level < other.getLevel();  // Highest level first
    }
    // If levels are the same, compare by coins
    if (m_coins != other.m_coins) {
        return m_coins < other.m_coins;  // Highest coins first
    }
    // If levels and coins are the same, compare by name
    return m_name > other.m_name;  // Alphabetical order by name
}
