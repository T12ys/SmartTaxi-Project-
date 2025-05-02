#pragma once
#include "Client.hpp"
#include "Driver.hpp"

Client* Search_for_a_client(Client* clients,int size,unsigned int ID);

Driver* Search_for_a_driver(Driver* drivers,int size,unsigned int ID);

//=========================================================================
enum OrderStatus {IN_PROGRESS, COMPLETED,FINALIZED};
class Order final{
private:
    Client* _client;
    Driver* _driver;
    std::string _from;
    std::string _to;
    double _distance; 
    double _price;
    OrderStatus _status;

    double calculatePrice(CarType type, double distance) {
        double rate = 0;
        switch (type) {
        case ECONOM:  rate = 1.0; break;
        case KOMFORT: rate = 1.5; break;
        case BIZNES:  rate = 2.5; break;
        }
        return rate * distance;
    }
    void SetClientAndDriver(Client* client, Driver* driver) {
        _client = client;  
        _driver = driver;  
    }

public:
    Order();
    Order(Client* client, Driver* driver, std::string from_loc, std::string to_loc, double distance);
    void assignOrder();
    void completeOrder();
    void Set_Orderstatus_FINALIZED();
    void OrderInfo();
    std::string get_driver_name();
    Driver* get_driver();
    Client* get_client();
    std::string get_driver_surname();
    std::string get_client_name();
    std::string get_client_surname();
    OrderStatus get_order_status();
    std::string GetFrom() const;  
    std::string GetTo() const; 
    void write_to_file(const std::string& file_name);
    void read_from_file(const std::string& file_name, unsigned int index = 0,
                    Client* clients = nullptr, int client_size = 0,
                    Driver* drivers = nullptr, int driver_size = 0);
    
    
};
