#include "Order.hpp"

Client* Search_for_a_client(Client* clients,int size,unsigned int ID)
{
    for (int i = 0; i < size; ++i) {
        if (clients[i].Get_ID() == ID) {
            return &clients[i];
        }
    }

    return nullptr;
}

Driver* Search_for_a_driver(Driver* drivers,int size,unsigned int ID)
{
    for (int i = 0; i < size; ++i) {
        if (drivers[i].Get_ID() == ID) {
            return &drivers[i];
        }
    }
    return nullptr;
}

//=========================================================================


    Order::Order():_client(),_driver(),_from("From nowhere"),_to("nowhere"),_distance(0),_status(IN_PROGRESS),_price(0) {}
    
    Order::Order(Client* client, Driver* driver, std::string from_loc, std::string to_loc, double distance)
        : _client(client), _driver(driver), _from(from_loc), _to(to_loc), _distance(distance), _status(IN_PROGRESS),_price(calculatePrice(_driver->Get_car_type(), _distance))
    {}
        //Пользователь хочет сделать заказ пишет все данные и ему высвечиваются все водители которые могут взять заказ и он выбирает 1 из них 
    void Order::assignOrder() {
        _status = IN_PROGRESS;
        _driver->Set_EmploymentStatus(true);
    }

    void Order::completeOrder() {
        _status = COMPLETED;
        _driver->Set_EmploymentStatus(false);
        
    }

    void Order::Set_Orderstatus_FINALIZED()
    {
        _status = FINALIZED;
    }
    

    void Order::OrderInfo() {
        std::cout << "From: " << _from << " To: " << _to << "\n";
        std::cout << "Distance: " << _distance << " km\n";
        std::cout << "Client: "; _client->show_info();
        if (_driver) {
            std::cout << "Driver: "; _driver->show_info();
            std::cout << "Price: " << _price <<"$"<<"\n";
            std::cout << "Status: ";
            switch (_status) {
            case IN_PROGRESS: std::cout << "In Progress"; break;
            case COMPLETED: std::cout << "Completed"; break;
            case FINALIZED: std::cout << "Finalized"; break;
            }
            std::cout << "\n";
        }
        else {
            std::cout << "Driver not assigned yet.\n";
        }
    }
    std::string Order::get_driver_name()
    {
        return _driver->Get_name();
    }
    Driver* Order::get_driver()
    {
        return _driver;
    }
    Client* Order::get_client()
    {
        return _client;
    }
    
    std::string Order::get_driver_surname()
    {
        return _driver->Get_surname();
    }
    std::string Order::get_client_name()
    {
        return _client->Get_name();
    }
    std::string Order::get_client_surname()
    {
        return _client->Get_surname();
    }

    OrderStatus Order::get_order_status()
    {
        return _status;
    }
    std::string Order::GetFrom() const {
        return _from;
    }

    std::string Order::GetTo() const {
        return _to;
    }

    void Order::write_to_file(const std::string& file_name) {
        std::ofstream out(file_name, std::ios::binary);
        if (!out) {
            throw std::runtime_error("Cannot open file for reading");
        }

        
        unsigned int clientId = _client->Get_ID();
        unsigned int driverId = _driver->Get_ID();

        out.write(reinterpret_cast<const char*>(&clientId), sizeof(clientId));
        out.write(reinterpret_cast<const char*>(&driverId), sizeof(driverId));

        
        unsigned int from_size = _from.size();  // NOLINT(clang-diagnostic-shorten-64-to-32)
        out.write(reinterpret_cast<const char*>(&from_size), sizeof(unsigned int));
        out.write(_from.data(), from_size);

        unsigned int to_size = _to.size();  // NOLINT(clang-diagnostic-shorten-64-to-32)
        out.write(reinterpret_cast<const char*>(&to_size), sizeof(unsigned int));
        out.write(_to.data(), to_size);

        
        out.write(reinterpret_cast<const char*>(&_distance), sizeof(double));
        out.write(reinterpret_cast<const char*>(&_price), sizeof(double));
        out.write(reinterpret_cast<const char*>(&_status), sizeof(OrderStatus));

        out.close();
    }

    void Order::read_from_file(const std::string& file_name, unsigned int index ,
                    Client* clients, int client_size,
                    Driver* drivers, int driver_size ) {
        std::ifstream in(file_name, std::ios::binary);
        if (!in) {
            throw std::runtime_error("Cannot open file for reading");
        }

        unsigned int tracker = 0;
        unsigned int clientId, driverId;

        while (tracker <= index && in.read(reinterpret_cast<char*>(&clientId), sizeof(unsigned int))) {
            in.read(reinterpret_cast<char*>(&driverId), sizeof(unsigned int));

            unsigned int from_size;
            in.read(reinterpret_cast<char*>(&from_size), sizeof(unsigned int));
            std::string from(from_size, '\0');
            in.read(&from[0], from_size);

            unsigned int to_size;
            in.read(reinterpret_cast<char*>(&to_size), sizeof(unsigned int));
            std::string to(to_size, '\0');
            in.read(&to[0], to_size);

            double distance, price;
            OrderStatus status;
            in.read(reinterpret_cast<char*>(&distance), sizeof(double));
            in.read(reinterpret_cast<char*>(&price), sizeof(double));
            in.read(reinterpret_cast<char*>(&status), sizeof(OrderStatus));

            if (tracker == index) {
                Client* client = Search_for_a_client(clients, client_size, clientId);
                Driver* driver = Search_for_a_driver(drivers, driver_size, driverId);
                if (client != nullptr && driver != nullptr) {
                    this->SetClientAndDriver(client, driver);
                } else {
                   throw  std::runtime_error("Client or driver not found.\n");
                }

                _from = from;
                _to = to;
                _distance = distance;
                _price = price;
                _status = status;

                in.close();
                return;
            }

            tracker++;
        }

        in.close();
        throw std::runtime_error("Index out of range");
    }

