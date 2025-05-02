#include "Client.hpp"

#include <iostream>
    
    

    Client::Client():User(),client_ID(0){}

    Client::Client(std::string name, std::string surname ,unsigned int age, unsigned int password)
            :User(name,surname ,age,password),
            client_ID(generateID())
    {}
    //--------------------------------------------------------------------------------
    //ПЕРЕДЕЛАТЬ КОНСТРУКТОРЫ КОПИРОВАНИЯ И ПЕРЕМЕШЕНИЯ ОНИ СКОРЕЕ ВСЕГО НЕ ВЕРНО РАБОТАЮТ
    
    //--------------------------------------------------------------------------------
    void Client::show_info()  {
        std::cout << "Name: " << _name << "\n"<<"Surname: " << _surname <<"\n"<<"Age: "<< _age <<"\n"<<"Rating: " << _rating << "\n"<<"ID: " << client_ID  << "\n";
    }

    unsigned int Client::Get_ID() const
    {
        return client_ID;
    }

    std::string Client::Get_name() const
    {
        return _name;
    }
    std::string Client::Get_surname() const
    {
        return _surname;
    }
    
    


    //Запись и считывание из файла
    void Client::write_to_file(const std::string& file_name) const {
        std::ofstream out(file_name, std::ios::binary | std::ios::app);

        if (!out) {
            throw std::runtime_error("Cannot open file for writing");
        }

        unsigned int name_size = _name.size();  // NOLINT(clang-diagnostic-shorten-64-to-32) В моем классе точно не будет имя больше чем из 4,294,967,295 символов 
        out.write(reinterpret_cast<const char*>(&name_size), sizeof(unsigned int));
        out.write(_name.data(), name_size);

        unsigned int surname_size = _surname.size();  // NOLINT(clang-diagnostic-shorten-64-to-32) Фамилии тоже -_-
        out.write(reinterpret_cast<const char*>(&surname_size), sizeof(unsigned int));
        out.write(_surname.data(), surname_size);

        out.write(reinterpret_cast<const char*>(&_age), sizeof(unsigned int));
        out.write(reinterpret_cast<const char*>(&_rating), sizeof(unsigned int));
        out.write(reinterpret_cast<const char*>(&_rating_count), sizeof(unsigned int));
        out.write(reinterpret_cast<const char*>(&_password), sizeof(unsigned int));
        out.write(reinterpret_cast<const char*>(&client_ID), sizeof(unsigned int));

        out.close();
    }
    
    void Client::read_from_file(const std::string& file_name,unsigned int index = 0)
    {
        std::ifstream in(file_name, std::ios::binary);
        if (!in) {
            throw std::runtime_error("Cannot open file for reading");
        }

        unsigned int tracker = 0;
        unsigned int name_size;
        while (in.read(reinterpret_cast<char*>(&name_size), sizeof(unsigned int)))
        {
            _name.resize(name_size);
            in.read(&_name[0], name_size);

            unsigned int surname_size;
            in.read(reinterpret_cast<char*>(&surname_size), sizeof(unsigned int));
            if (!in)
            {
                throw std::runtime_error("Error reading surname size");
            }
            _surname.resize(surname_size);
            in.read(&_surname[0], surname_size);
            if (!in) {
                throw std::runtime_error("Error reading surname data");
            }

            in.read(reinterpret_cast<char*>(&_age), sizeof(unsigned int));
            if (!in) {
                throw std::runtime_error("Error reading age");
            }

            in.read(reinterpret_cast<char*>(&_rating), sizeof(unsigned int));
            if (!in) {
                throw std::runtime_error("Error reading rating");
            }

            in.read(reinterpret_cast<char*>(&_rating_count), sizeof(unsigned int));
            if (!in) {
                throw std::runtime_error("Error reading rating count");
            }

            in.read(reinterpret_cast<char*>(&_password), sizeof(unsigned int));
            if (!in) {
                throw std::runtime_error("Error reading password");
            }

            in.read(reinterpret_cast<char*>(&client_ID), sizeof(unsigned int));
            if (!in) {
                throw std::runtime_error("Error reading ID");
            }

            if (tracker == index){
                break;
            }
            tracker++;
        }
        
        if (tracker != index) {
            throw std::runtime_error("Index out of range");
        
        }
    }



