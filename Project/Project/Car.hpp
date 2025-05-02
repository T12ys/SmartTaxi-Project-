#pragma once
#include <iostream>
#include <string>
#include <fstream>

enum CarType { ECONOM, KOMFORT, BIZNES };

class Car {
private:
    std::string _name;
    unsigned int _mileage;
    unsigned int _year;
    CarType _type;
public:
    Car();
    Car(std::string name, unsigned int mileage,unsigned int year,CarType type);
    void showInfo();
    CarType Get_type() const;
    void write_to_file(std::ofstream& out) const;
    void read_from_file(std::ifstream& in);
};
