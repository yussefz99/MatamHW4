//
// Created by yusse on 04/08/2024.
//
#include "Player.h"

Player::Player(std::string& name,std::shared_ptr<Job> job,std::shared_ptr<Character> character):m_name(name),m_level(1),m_force(5),
m_currHP(100),m_MaxHP(100),m_coins(10),m_job(job),m_character(character){
    if(m_job->get_job() == "Warrior")m_MaxHP=150;
    if(m_job->get_job() == "Archer")m_coins=20;
}


