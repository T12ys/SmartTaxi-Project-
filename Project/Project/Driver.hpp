#pragma once

#include "Car.hpp"

enum EmploymentStatus { Busy, Free };
#include "User.hpp"
class Driver final: public User
{
private:
    EmploymentStatus _status;
    unsigned int driver_ID;  
    Car _car;

    unsigned int generateId() {
        unsigned int lastID = 100000;

        
        std::ifstream inFile("last_id_driver.bin", std::ios::binary);
        if (inFile) {
            inFile.read(reinterpret_cast<char*>(&lastID), sizeof(lastID));
            inFile.close();
        }

        lastID++;  

        
        std::ofstream outFile("last_id_driver.bin", std::ios::binary);
        if (outFile) {
            outFile.write(reinterpret_cast<const char*>(&lastID), sizeof(lastID));
            outFile.close();
        }

        return lastID;
    }

public:
    Driver();
    Driver(std::string name,
        std::string surname,
        unsigned int age,
        unsigned int password,
        std::string carName,
        unsigned int mileage,
        unsigned int year,
        CarType type);
    
    void show_info() override;
    CarType Get_car_type() const;
    unsigned int Get_ID() const;
    std::string Get_name() const;
    std::string Get_surname() const;
    void Set_EmploymentStatus(bool isBusy);
    EmploymentStatus Get_EmploymentStatus() const;
    unsigned int GetAverageRating() const;
    void write_to_file(const std::string& file_name) const;
    void read_from_file(const std::string& file_name,unsigned int index = 0);
};
