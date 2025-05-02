#pragma once
#include <fstream>
#include "User.hpp"

class Client final : public User
{
private:
    unsigned int client_ID;
    unsigned int generateID() {
        unsigned int lastID = 100000;

        
        std::ifstream inFile("last_id_client.bin", std::ios::binary);
        if (inFile) {
            inFile.read(reinterpret_cast<char*>(&lastID), sizeof(lastID));
            inFile.close();
        }

        lastID++;  

        
        std::ofstream outFile("last_id_client.bin", std::ios::binary);
        if (outFile) {
            outFile.write(reinterpret_cast<const char*>(&lastID), sizeof(lastID));
            outFile.close();
        }

        return lastID;
    }
    public:
    Client();
    Client(std::string name, std::string surname ,unsigned int age, unsigned int password);
    void show_info()override;
    unsigned int Get_ID() const;
    std::string Get_name() const;
    std::string Get_surname() const;
    void write_to_file(const std::string& file_name) const ;
    void read_from_file(const std::string& file_name,unsigned int index);
    
};
