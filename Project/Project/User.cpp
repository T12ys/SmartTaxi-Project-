#pragma once
#include "User.hpp"
#include <iostream>

User::User()
    : _name("Unknown"), _surname("Unknown"),_age(18), _rating(5),_rating_count(0), _password(0) {}

User::User(std::string name, std::string surname,unsigned int age ,unsigned int password)
    : _name(name), _surname(surname),_age(age), _rating(5),_rating_count(0), _password(password)
{
    if (name.empty() || surname.empty()) {
        throw std::invalid_argument("Name and surname cannot be empty");
    }

    if (age < 18) {
        throw std::invalid_argument("User must be at least 18 years old");
    }
}
void User::Rating_system(unsigned int rate)
{
    this->update_rating(rate);
}
bool User::checkPassword(unsigned int pwd) const {
    return _password == pwd;
}
