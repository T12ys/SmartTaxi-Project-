#include "Driver.hpp"

    

Driver::Driver():_status(Free),driver_ID(0) {}
Driver::Driver(std::string name,
    std::string surname,
    unsigned int age,
    unsigned int password,
    std::string carName,
    unsigned int mileage,
    unsigned int year,
    CarType type): User(name, surname,age, password),_status(Free), driver_ID(generateId()), _car(carName, mileage,year, type)
{}


void Driver::show_info() {
    std::cout << "Driver Name: " << _name << " Surname: " << _surname <<" Age: " << _age 
              << " Rating: " << _rating << " ID: " << driver_ID << "\n";
    _car.showInfo();
}

CarType Driver::Get_car_type() const {
    return _car.Get_type(); 
}

unsigned int Driver::Get_ID() const
{
    return driver_ID;
}

std::string Driver::Get_name() const
{
    return _name;
}

std::string Driver::Get_surname() const
{
    return _surname;
}

void Driver::Set_EmploymentStatus(bool isBusy)
{
    if (isBusy) _status = Busy;
    else  _status = Free;
}
 EmploymentStatus Driver::Get_EmploymentStatus() const
{
    return _status;
}

unsigned int Driver::GetAverageRating() const {
        if (_rating_count == 0) return 0; 
        return _rating; 
    }

void Driver::write_to_file(const std::string& file_name) const {
    std::ofstream out(file_name, std::ios::binary | std::ios::app);

    if (!out) {
        throw std::runtime_error("Cannot open file for writing");
    }

    unsigned int name_size = _name.size();  // NOLINT(clang-diagnostic-shorten-64-to-32) ┏(-_-)┛┗(-_-)┓┗(-_-)┛┏(-_-)┓
    out.write(reinterpret_cast<const char*>(&name_size), sizeof(unsigned int));
    out.write(_name.data(), name_size);

    unsigned int surname_size = _surname.size();  // NOLINT(clang-diagnostic-shorten-64-to-32) ( ＾▽＾)っ✂╰⋃╯
    out.write(reinterpret_cast<const char*>(&surname_size), sizeof(unsigned int));
    out.write(_surname.data(), surname_size);

    out.write(reinterpret_cast<const char*>(&_age), sizeof(unsigned int));
    out.write(reinterpret_cast<const char*>(&_rating), sizeof(unsigned int));
    out.write(reinterpret_cast<const char*>(&_rating_count), sizeof(unsigned int));
    out.write(reinterpret_cast<const char*>(&_password), sizeof(unsigned int));
    out.write(reinterpret_cast<const char*>(&_status), sizeof(EmploymentStatus));
    out.write(reinterpret_cast<const char*>(&driver_ID), sizeof(unsigned int));

    _car.write_to_file(out);

    out.close();
}

void Driver::read_from_file(const std::string& file_name,unsigned int index)
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
            throw std::runtime_error("Error reading age data");
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

        in.read(reinterpret_cast<char*>(&_status), sizeof(EmploymentStatus));
        if (!in)
        {
            throw std::runtime_error("Error reading status");
        }

        in.read(reinterpret_cast<char*>(&driver_ID), sizeof(unsigned int));
        if (!in) {
            throw std::runtime_error("Error reading ID");
        }

        _car.read_from_file(in);
        if (tracker == index){
            break;
        }
        tracker++;
    }
    
    if (tracker != index) {
        throw std::runtime_error("Index out of range");
    
    }
}


