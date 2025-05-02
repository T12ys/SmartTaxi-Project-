#pragma once
#include <string>

class User
{
protected:
    std::string _name;
    std::string _surname;
    unsigned int _age;
    unsigned int _rating;
    unsigned int _rating_count;
    unsigned int _password;

    void update_rating(unsigned int new_rating) {
        _rating = (_rating * _rating_count + new_rating) / (_rating_count + 1);
        _rating_count++;
    }
    public:
    User();
    User(std::string name, std::string surname,unsigned int age ,unsigned int password);
    void Rating_system(unsigned int rate);
    bool checkPassword(unsigned int pwd) const;
    virtual void show_info() = 0;
};