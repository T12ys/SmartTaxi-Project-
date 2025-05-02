#include "Car.hpp"


    Car::Car(): _name("Unknown"), _mileage(0), _year(0), _type(ECONOM) {}
    Car::Car(std::string name, unsigned int mileage,unsigned int year,CarType type)
        : _name(name), _mileage(mileage), _year(year), _type(type)
    {
        if (name.empty()) {
            throw std::invalid_argument("Car name cannot be empty");
        }

        if (mileage > 1'000'000) {
            throw std::invalid_argument("Mileage is unrealistically high");
        }

        if (year != 0 && (year < 1900 || year > 2025)) {
            throw std::invalid_argument("Invalid car year");
        } 
    }

    void Car::showInfo() {
        std::cout << "Car Name: " << _name << "\n";
        std::cout << "Car Mileage: " << _mileage << " km\n";
        std::cout << "Car Type: ";
        switch (_type) {
        case ECONOM: std::cout << "Economy"; break;
        case KOMFORT: std::cout << "Comfort"; break;
        case BIZNES: std::cout << "Business"; break;
        }
        std::cout << "\n";
        std::cout << "Year of the car: " << _year << "\n";
    }

    CarType Car::Get_type() const {
        return _type;
    }
    
    void Car::write_to_file(std::ofstream& out) const {
        if (!out) { throw std::runtime_error("Cannot open file for writing"); }
        unsigned int name_len = _name.size();  // NOLINT(clang-diagnostic-shorten-64-to-32) ..................-_-
        out.write((const char*)&name_len, sizeof(unsigned int));// Внутри скобки написанно const char* потому что в обявлении метода у меня есть ключевое слово const из-за этого пермеменные внутри метода ведут себя как const а запись просто char* будет пытатся превратить указатель на константу в обычный неконстантный указатель на char что не верно. 
        out.write(_name.data(), name_len);
        out.write((const char*)&_mileage, sizeof(unsigned int));
        out.write((const char*)&_year, sizeof(unsigned int));
        out.write((const char*)&_type, sizeof(CarType));
    }

    void Car::read_from_file(std::ifstream& in) {
        unsigned int name_len;
        in.read((char*)&name_len, sizeof(unsigned int));
        _name.resize(name_len);
        in.read(&_name[0], name_len);
        if (!in) {throw std::runtime_error("Error reading car name");}
        in.read((char*)&_mileage, sizeof(unsigned int));
        if (!in) {throw std::runtime_error("Error reading mileage ");}
        in.read((char*)&_year, sizeof(unsigned int));
        if (!in) {throw std::runtime_error("Error reading year");}
        in.read((char*)&_type, sizeof(CarType));
        if (!in) {throw std::runtime_error("Error reading type of car");}
    }
