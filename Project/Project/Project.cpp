#include "Client.hpp"
#include "Car.hpp"
#include "Driver.hpp"
#include "Order.hpp"


unsigned int Clients_count( const std::string& file_name)
{
    std::ifstream in(file_name, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Cannot open client file for reading");
    }

    unsigned int count = 0;

    while (in.peek() != EOF) {
        unsigned int name_size;
        if (!in.read(reinterpret_cast<char*>(&name_size), sizeof(unsigned int))) break;
        in.seekg(name_size, std::ios::cur);

        unsigned int surname_size;
        in.read(reinterpret_cast<char*>(&surname_size), sizeof(unsigned int));
        in.seekg(surname_size, std::ios::cur);

        in.seekg(sizeof(unsigned int) * 5, std::ios::cur);
        count++;
    }

    in.clear();
    in.seekg(0, std::ios::beg);

    return count;
}

void loadAllClients(Client* clients,const std::string& file_name ,unsigned int count) {
    
    for (unsigned int i = 0; i < count; ++i) {
        clients[i].read_from_file(file_name, i);
    }
}

unsigned int Drivers_count( const std::string& file_name)
{
    std::ifstream in(file_name, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Cannot open driver file for reading");
    }

    unsigned int count = 0;
    while (in.peek() != EOF) {
        unsigned int name_size;
        if (!in.read(reinterpret_cast<char*>(&name_size), sizeof(unsigned int))) break;
        in.seekg(name_size, std::ios::cur);

        unsigned int surname_size;
        in.read(reinterpret_cast<char*>(&surname_size), sizeof(unsigned int));
        in.seekg(surname_size, std::ios::cur);

        in.seekg(sizeof(unsigned int) * 4, std::ios::cur);
        in.seekg(sizeof(EmploymentStatus) , std::ios::cur);
        in.seekg(sizeof(unsigned int) , std::ios::cur);
        
        unsigned int car_name_len;
        in.read(reinterpret_cast<char*>(&car_name_len), sizeof(unsigned int));
        in.seekg(car_name_len, std::ios::cur);

        in.seekg(sizeof(unsigned int) * 3, std::ios::cur);

        count++;
    }

    in.clear();
    in.seekg(0, std::ios::beg);

    return count;

}

void loadAllDrivers(Driver* drivers, const std::string& file_name, unsigned int count) {
    
    
    for (unsigned int i = 0; i < count; ++i) {
        drivers[i].read_from_file(file_name, i);
    }
}

unsigned int Order_count(const std::string& file_name) {
    std::ifstream in(file_name, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Cannot open file for reading");
    }

    unsigned int count = 0;

    while (in.peek() != EOF) {
        unsigned int clientId, driverId;

        
        if (!in.read(reinterpret_cast<char*>(&clientId), sizeof(unsigned int))) break;
        if (!in.read(reinterpret_cast<char*>(&driverId), sizeof(unsigned int))) break;

        
        unsigned int from_size;
        if (!in.read(reinterpret_cast<char*>(&from_size), sizeof(unsigned int))) break;
        in.seekg(from_size, std::ios::cur); 

        
        unsigned int to_size;
        if (!in.read(reinterpret_cast<char*>(&to_size), sizeof(unsigned int))) break;
        in.seekg(to_size, std::ios::cur); 

        
        in.seekg(sizeof(double) * 2, std::ios::cur); 

        
        in.seekg(sizeof(OrderStatus), std::ios::cur); 

        count++;
    }

    in.close();
    return count;
}

void loadAllOrders(Order* orders, Client* clients, int client_count,
                   Driver* drivers, int driver_count,
                   const std::string& file_name, unsigned int count) {
    for (unsigned int i = 0; i < count; ++i) {
        orders[i].read_from_file(file_name, i, clients, client_count, drivers, driver_count);
    }
}


void saveAllClients( Client* clients, const std::string& file_name,unsigned int count) {
    std::ofstream out(file_name, std::ios::binary | std::ios::trunc); 
    if (!out) {
        throw std::runtime_error("Cannot open client file for writing");
    }
    out.close(); 

    for (unsigned int i = 0; i < count; ++i) {
        clients[i].write_to_file(file_name);
    }
}


void saveAllDrivers( Driver* drivers,const std::string& file_name, unsigned int count) {
    std::ofstream out(file_name, std::ios::binary | std::ios::trunc); 
    if (!out) {
        throw std::runtime_error("Cannot open driver file for writing");
    }
    out.close(); 

    for (unsigned int i = 0; i < count; ++i) {
        drivers[i].write_to_file(file_name);
    }
}

void saveAllOrders( Order* orders,const std::string& file_name, unsigned int count) {
    std::ofstream out(file_name, std::ios::binary | std::ios::trunc); 
    if (!out) {
        throw std::runtime_error("Cannot open driver file for writing");
    }
    out.close(); 

    for (unsigned int i = 0; i < count; ++i) {
        orders[i].write_to_file(file_name);
    }
}
//=========================================================================

int Search_for_a_client(Client* clients,int size,std::string name, std::string surname)
{
    for (int i = 0; i < size; ++i) {
        if (clients[i].Get_name() == name && clients[i].Get_surname() == surname) {
            return i;
        }
    }
    return -1;
}
//-------------------------------------------------------------------------

int Search_for_a_driver(Driver* drivers, int size, const std::string& name, const std::string& surname)
{
    
        for (int i = 0; i < size; ++i) {
            if (drivers[i].Get_name() == name && drivers[i].Get_surname() == surname) {
                return i;
            }
        }
    

    return -1;
}
//--------------------------------------------------------------------------

int Search_for_order_by_driver(Order* orders, int size, std::string driver_name, std::string driver_surname)
{
    
    for (int i = 0; i < size; i++)
    {
        
        if (orders[i].get_driver_name() == driver_name && orders[i].get_driver_surname() == driver_surname)
        {
            return i;
        }
    }
    return -1;
}
int Search_for_order_by_client(Order* orders, int size, std::string client_name, std::string client_surname)
{
    
    for (int i = 0; i < size; i++)
    {
        
        if (orders[i].get_client_name() == client_name && orders[i].get_client_surname() == client_surname && orders[i].get_order_status() != FINALIZED)
        {
            return i;
        }
    }
    return -1;
}


//=========================================================================
bool containsDigit(const std::string& str) {
    for (char ch : str) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            return true;
        }
    }
    return false;
}

bool containsSpecialChar(const std::string& str) {
    for (char ch : str) {
        if (!std::isalnum(static_cast<unsigned char>(ch))) {
            return true;
        }
    }
    return false;
}
//=========================================================================
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}
//=========================================================================
unsigned int GetTotalFinalizedOrders(Order* orders, unsigned int order_count) {
    unsigned int finalizedOrdersCount = 0;

    for (unsigned int i = 0; i < order_count; ++i) {
        if (orders[i].get_order_status() == FINALIZED) {
            ++finalizedOrdersCount;  
        }
    }

    return finalizedOrdersCount;
}
//=========================================================================
void adminMenu(const std::string& drivers_file, const std::string& orders_file, const std::string& clients_file)
{
    if (!fileExists(drivers_file) || !fileExists(orders_file))
    {
        std::cerr << "No data available to display statistics.\n";
        return;
    }

    unsigned int driver_count = Drivers_count(drivers_file);
    Driver* drivers = new Driver[driver_count];
    loadAllDrivers(drivers, drivers_file, driver_count);

    unsigned int order_count = Order_count(orders_file);
    Order* orders = new Order[order_count];

    unsigned int client_count = 0;
    Client* clients = nullptr;
    if (fileExists(clients_file)) {
        client_count = Clients_count(clients_file);
        clients = new Client[client_count];
        loadAllClients(clients, clients_file, client_count);
    }

    loadAllOrders(orders, clients, client_count, drivers, driver_count, orders_file, order_count);

    std::cout << "\n--- Admin Menu ---\n";

    
    std::cout << "\nDriver Statistics:\n";
    for (unsigned int i = 0; i < driver_count; ++i)
    {
        std::cout << drivers[i].Get_name() << " " << drivers[i].Get_surname() << ":\n";
        unsigned int finalizedOrders = GetTotalFinalizedOrders(orders, order_count);
        std::cout << "Total finalized orders: " << finalizedOrders << "\n"; 
        std::cout << "Average rating: " << drivers[i].GetAverageRating() << "\n\n";
    }

    
    unsigned int route_count = 0;
    std::string* routes = new std::string[order_count];

    
    for (unsigned int i = 0; i < order_count; ++i)
    {
        routes[route_count++] = orders[i].GetFrom() + " -> " + orders[i].GetTo();
    }

    
    std::string most_popular, least_popular;
    int max_count = 0, min_count = INT_MAX;

    for (unsigned int i = 0; i < route_count; ++i)
    {
        int count = 0;
        for (unsigned int j = 0; j < route_count; ++j)
        {
            if (routes[i] == routes[j]) {
                count++;
            }
        }

        if (count > max_count)
        {
            max_count = count;
            most_popular = routes[i];
        }

        if (count < min_count)
        {
            min_count = count;
            least_popular = routes[i];
        }
    }

    std::cout << "Most popular route: " << most_popular << " (" << max_count << " times)\n";
    std::cout << "Least popular route: " << least_popular << " (" << min_count << " times)\n\n";
    

    delete[] drivers;
    delete[] orders;
    if (clients) delete[] clients;
    delete[] routes;
}


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

int main()
{
    
    const std::string clients_file = "clients.bin";
    const std::string drivers_file = "drivers.bin";
    const std::string orders_file = "orders.bin"  ;
    
    std::cout << "Hello, this is our taxi system.\n"
             "What do you want to do?\n"
             "1) Register\n"
             "2) Login\n"
             "3) Admin Panel\n";

    size_t Register_or_Login = 0;

    while (true) {
        std::cout << "Enter your choice (1-3): ";
        std::cin >> Register_or_Login;

        if (Register_or_Login < 1 || Register_or_Login > 3) {
            std::cerr << "Invalid value! Please enter 1, 2, or 3.\n";
        } else {
            break;
        }
    }

    size_t Driver_or_Client = 0;

    if (Register_or_Login == 1) 
    {
        std::cout << "Register as:\n"
                     "1) Driver\n"
                     "2) Client\n";

        while (true) {
            std::cout << "Enter your choice (1 or 2): ";
            std::cin >> Driver_or_Client;

            if (Driver_or_Client != 1 && Driver_or_Client != 2) {
                std::cerr << "Invalid value! Please enter 1 or 2.\n";
            } else {
                break;
            }
        }
    }
    else if (Register_or_Login == 2) 
    {
        std::cout << "Login as:\n"
                     "1) Driver\n"
                     "2) Client\n";

        while (true) {
            std::cout << "Enter your choice (1 or 2): ";
            std::cin >> Driver_or_Client;

            if (Driver_or_Client != 1 && Driver_or_Client != 2) {
                std::cerr << "Invalid value! Please enter 1 or 2.\n";
            } else {
                break;
            }
        }
    }
    else if (Register_or_Login == 3) 
    {
        std::string admin_password;
        std::cout << "Enter admin password: ";
        std::cin >> admin_password;

        if (admin_password == "admin123") {
            std::cout << "Access granted to admin panel.\n";
            adminMenu(drivers_file,orders_file,clients_file);
            
        } else {
            std::cerr << "Access denied. Incorrect password.\n";
            return 0; 
        }
    }

//======================================================================================
//======================================================================================

    
    
    if (Register_or_Login == 1 && Driver_or_Client == 1)
{
    std::string name, surname, carname;

    do {
        std::cout << "Enter your name: ";
        std::cin >> name;
        if (containsSpecialChar(name) || containsDigit(name))
            std::cout << "The name cannot contain numbers or special characters\n";
    } while (containsSpecialChar(name) || containsDigit(name));

    do {
        std::cout << "Enter your surname: ";
        std::cin >> surname;
        if (containsSpecialChar(surname) || containsDigit(surname))
            std::cout << "The surname cannot contain numbers or special characters\n";
    } while (containsSpecialChar(surname) || containsDigit(surname));

    unsigned int age;
    while (true)
    {
        std::cout << "Enter your age: ";
        std::cin >> age;
        if (age >= 18) break;
        std::cerr << "Error: Registration is allowed only for people 18 years and older.\n";
    }

    unsigned int password;
    while (true)
    {
        std::cout << "Create a password: ";
        std::cin >> password;
        if (password >= 100000 && password <= 99999999) break;
        std::cerr << "Error: Your password must be 6, 7 or 8 digits long and must not start with 0\n";
    }

    do {
        std::cout << "Enter your car name: ";
        std::cin >> carname;
        if (containsSpecialChar(carname) || containsDigit(carname))
            std::cout << "The car name cannot contain numbers or special characters\n";
    } while (containsSpecialChar(carname) || containsDigit(carname));

    std::cout << "Enter your car mileage: ";
    unsigned int mileage;
    std::cin >> mileage;

    unsigned int year;
    while (true)
    {
        std::cout << "Enter your car year: ";
        std::cin >> year;
        if (year >= 1980 && year <= 2025) break;
        std::cerr << "Error: Your car can't be from before 1980 or from the future.\n";
    }

    CarType type;
    int choice;
    while (true)
    {
        std::cout << "Please select your car type:\n";
        std::cout << "1. Economy\n";
        std::cout << "2. Comfort\n";
        std::cout << "3. Business\n";
        std::cout << "Your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            type = ECONOM;
            break;
        }
        else if (choice == 2) {
            type = KOMFORT;
            break;
        }
        else if (choice == 3) {
            type = BIZNES;
            break;
        }
        else {
            std::cerr << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }

    Driver driver(name, surname, age, password, carname, mileage, year, type);
    driver.write_to_file(drivers_file);

    std::cout << "\nNo active orders.\n"
              << "Please wait for new ride requests...\n"
              << "We'll notify you as soon as a ride is available.\n";

    int log_out;
    while (true)
    {
        std::cout << "Enter 1 if you want to log out: ";
        std::cin >> log_out;
        if (log_out == 1) break;
        std::cerr << "Invalid choice. Please select 1\n";
    }

    return 0;
}

    


    if (Register_or_Login == 1 && Driver_or_Client == 2)
{
    std::string name, surname;

    do {
        std::cout << "Enter your name: ";
        std::cin >> name;
        if (containsSpecialChar(name) || containsDigit(name))
            std::cout << "The name cannot contain numbers or special characters\n";
    } while (containsSpecialChar(name) || containsDigit(name));

    do {
        std::cout << "Enter your surname: ";
        std::cin >> surname;
        if (containsSpecialChar(surname) || containsDigit(surname))
            std::cout << "The surname cannot contain numbers or special characters\n";
    } while (containsSpecialChar(surname) || containsDigit(surname));

    unsigned int age;
    while (true)
    {
        std::cout << "Enter your age: ";
        std::cin >> age;
        if (age >= 18) break;
        std::cerr << "Error: Registration is allowed only for people 18 years and older.\n";
    }

    unsigned int password;
    while (true)
    {
        std::cout << "Create a password: ";
        std::cin >> password;
        if (password >= 100000 && password <= 99999999) break;
        std::cerr << "Error: Your password must be 6, 7, or 8 digits and must not start with 0.\n";
    }

    Client client(name, surname, age, password);
    client.write_to_file(clients_file);

    std::cout << "\nYour information:\n";
    client.show_info();

    int Order_or_Logout;
    while (true)
    {
        std::cout << "\nWhat would you like to do next?\n"
                     "1. Make an order\n"
                     "2. Log out\n";
        
        std::cout << "Enter your choice (1 or 2): ";
        std::cin >> Order_or_Logout;
        if (Order_or_Logout == 1 || Order_or_Logout == 2) break;
        std::cerr << "Invalid input! Please enter 1 or 2.\n";
    }

    if (Order_or_Logout == 2) return 0;

    if (!fileExists(drivers_file))
    {
        std::cerr << "There are no drivers in the system.\n";
        return 0;
    }

    unsigned int driver_count = Drivers_count(drivers_file);
    Driver* drivers = new Driver[driver_count];
    loadAllDrivers(drivers, drivers_file, driver_count);

    unsigned int* free_driver_indexes = new unsigned int[driver_count];
    int free_count = 0;

    std::cout << "\nChoose a driver for your trip:\n";
    for (unsigned int i = 0; i < driver_count; ++i)
    {
        if (drivers[i].Get_EmploymentStatus() == Free)
        {
            free_driver_indexes[free_count] = i;
            std::cout << "Driver number " << free_count + 1 << ":\n";
            drivers[i].show_info();
            ++free_count;
        }
    }

    if (free_count == 0)
    {
        std::cerr << "No available drivers at the moment. Please try again later.\n";
        delete[] drivers;
        delete[] free_driver_indexes;
        return 0;
    }

    int driver_selection;
    while (true)
    {
        std::cout << "Select a driver (1 - " << free_count << "): ";
        std::cin >> driver_selection;
        if (driver_selection > 0 && driver_selection <= free_count) break;
        std::cerr << "Invalid selection! Please enter the correct value.\n";
    }

    unsigned int selected_index = free_driver_indexes[driver_selection - 1];
    std::cout << "You selected:\n";
    drivers[selected_index].show_info();

    delete[] free_driver_indexes;

    std::string from, to;

    do {
        std::cout << "Enter your pickup location: ";
        std::cin >> from;
        if (containsSpecialChar(from) || containsDigit(from))
            std::cout << "The pickup location cannot contain numbers or special characters\n";
    } while (containsSpecialChar(from) || containsDigit(from));

    do {
        std::cout << "Enter your destination: ";
        std::cin >> to;
        if (containsSpecialChar(to) || containsDigit(to))
            std::cout << "The destination cannot contain numbers or special characters\n";
    } while (containsSpecialChar(to) || containsDigit(to));

    std::cout << "\nPlease enter the distance between the pickup and drop-off points: ";
    double distance;
    std::cin >> distance;

    Order order(&client, &drivers[selected_index], from, to, distance);
    order.assignOrder();

    std::cout << "\nOrder information:\n";
    order.OrderInfo();

    order.write_to_file(orders_file);
    drivers[selected_index].Set_EmploymentStatus(true);
    saveAllDrivers(drivers, drivers_file, driver_count);

    delete[] drivers;
}




    if (Register_or_Login == 2 && Driver_or_Client == 1)
{
    std::cout << "Login_Driver\n";

    if (!fileExists(drivers_file))
    {
        std::cerr << "There are no drivers in the system.\n"
                     "Please register first and then log in.\n";
        return 0;
    }

    unsigned int driver_count = Drivers_count(drivers_file);
    Driver* drivers = new Driver[driver_count];
    loadAllDrivers(drivers, drivers_file, driver_count);

    std::cout << "Login to account\n";

    int driver_number;
    while (true)
    {
        std::string name, surname;

        do {
            std::cout << "Enter your name: ";
            std::cin >> name;
            if (containsSpecialChar(name) || containsDigit(name))
                std::cerr << "The name cannot contain numbers or special characters\n";
        } while (containsSpecialChar(name) || containsDigit(name));

        do {
            std::cout << "Enter your surname: ";
            std::cin >> surname;
            if (containsSpecialChar(surname) || containsDigit(surname))
                std::cerr << "The surname cannot contain numbers or special characters\n";
        } while (containsSpecialChar(surname) || containsDigit(surname));

        driver_number = Search_for_a_driver(drivers, driver_count, name, surname);
        if (driver_number == -1)
        {
            std::cerr << "User not found. Try again.\n";
        }
        else break;
    }

    while (true)
    {
        std::cout << "Enter your password: ";
        unsigned int password;
        std::cin >> password;
        if (drivers[driver_number].checkPassword(password))
        {
            std::cout << "Login successful\n";
            break;
        }
        std::cerr << "Incorrect password. Try again.\n";
    }

    if (drivers[driver_number].Get_EmploymentStatus() == Busy)
    {
        if (!fileExists(orders_file) || !fileExists(clients_file))
        {
            std::cerr << "Order or client file missing. Cannot continue.\n";
            delete[] drivers;
            return 0;
        }

        unsigned int client_count = Clients_count(clients_file);
        Client* clients = new Client[client_count];
        loadAllClients(clients, clients_file, client_count);

        unsigned int order_count = Order_count(orders_file);
        Order* orders = new Order[order_count];
        loadAllOrders(orders, clients, client_count, drivers, driver_count, orders_file, order_count);

        int order_number = Search_for_order_by_driver(
            orders, order_count,
            drivers[driver_number].Get_name(),
            drivers[driver_number].Get_surname()
        );

        if (order_number == -1)
        {
            std::cerr << "No matching order found.\n";
        }
        else
        {
            std::cout << "You have an order:\n";
            orders[order_number].OrderInfo();

            std::cout << "Look at the road, you have an order.\n";

            int complete_the_order;
            while (true)
            {
                std::cout << "To complete your order, press 1: ";
                std::cin >> complete_the_order;
                if (complete_the_order == 1)
                {
                    orders[order_number].completeOrder();
                    break;
                }
            }

            int rate;
            while (true)
            {
                std::cout << "Please rate the client from 1 to 5: ";
                std::cin >> rate;
                if (rate >= 1 && rate <= 5)
                {
                    orders[order_number].get_client()->Rating_system(rate);
                    break;
                }
                std::cerr << "Invalid rating. Try again.\n";
            }

            saveAllDrivers(drivers, drivers_file, driver_count);
            saveAllClients(clients, clients_file, client_count);
            saveAllOrders(orders, orders_file, order_count);
        }

        delete[] clients;
        delete[] orders;
    }
    else
    {
        std::cerr << "You don't have an order. Wait...\n";
    }

    delete[] drivers;
}

    if (Register_or_Login == 2 && Driver_or_Client == 2)
    {
        std::cout << "Login_Client\n";

        if (!fileExists(clients_file))
    {
        std::cerr << "There are no clients in the system.\n"
                     "Please register first and then log in.\n";
        return 0;
    }

    unsigned int client_count = Clients_count(clients_file);
    Client* clients = new Client[client_count];
    loadAllClients(clients, clients_file, client_count);

    std::cout << "Login to account\n";

    int client_number;
    while (true)
    {
        std::string name, surname;
        
        do {
            std::cout << "Enter your name: ";
            std::cin >> name;
            if (containsSpecialChar(name) || containsDigit(name))
                std::cerr << "The name cannot contain numbers or special characters\n";
        } while (containsSpecialChar(name) || containsDigit(name));
        
        
        do {
            std::cout << "Enter your surname: ";
            std::cin >> surname;
            if (containsSpecialChar(surname) || containsDigit(surname))
                std::cerr << "The surname cannot contain numbers or special characters\n";
        } while (containsSpecialChar(surname) || containsDigit(surname));

        client_number = Search_for_a_client(clients, client_count, name, surname);
        if (client_number == -1)
        {
            std::cerr << "User not found. Please try again.\n";
        }
        else break;
    }

    
    while (true)
    {
        std::cout << "Enter your password: ";
        unsigned int password;
        std::cin >> password;
        if (clients[client_number].checkPassword(password))
        {
            std::cout << "Login successful\n";
            break;
        }
        std::cerr << "Incorrect password. Try again.\n";
    }

    std::cout << "Your information:\n";
    clients[client_number].show_info();

    
    if (fileExists(orders_file) && fileExists(drivers_file))
    {
        unsigned int driver_count = Drivers_count(drivers_file);
        Driver* drivers = new Driver[driver_count];
        loadAllDrivers(drivers, drivers_file, driver_count);

        unsigned int order_count = Order_count(orders_file);
        Order* orders = new Order[order_count];
        loadAllOrders(orders, clients, client_count, drivers, driver_count, orders_file, order_count);

        int order_number = Search_for_order_by_client(orders, order_count,clients[client_number].Get_name(), clients[client_number].Get_surname());

        if (order_number != -1)
        {
            std::cout << "Here is your order:\n";
            orders[order_number].OrderInfo();

            if (orders[order_number].get_order_status() == COMPLETED)
            {
                std::cout << "Order completed.\n";
                int rate;
                while (true)
                {
                    std::cout << "Please rate the driver from 1 to 5: ";
                    std::cin >> rate;
                    if (rate >= 1 && rate <= 5)
                    {
                        orders[order_number].get_driver()->Rating_system(rate);
                        orders[order_number].Set_Orderstatus_FINALIZED();
                        break;
                    }
                    std::cerr << "Invalid rating. Try again.\n";
                }
                saveAllDrivers(drivers, drivers_file, driver_count);
                saveAllOrders(orders, orders_file, order_count);
            }
        }

        
        int choice;
        std::cout << "\nWhat would you like to do next?\n"
                     "1. Log out\n"
                     "2. Make an order\n";
        
        while (true)
        {
            std::cout << "Enter your choice (1 or 2): ";
            std::cin >> choice;
            if (choice == 1 || choice == 2) break;
            std::cerr << "Invalid choice. Please enter 1 or 2.\n";
        }

        if (choice == 2)
        {
            if (order_number != -1 && orders[order_number].get_order_status() != FINALIZED)
            {
                std::cerr << "You already have an active order. Complete it first.\n";
            }
            else
            {
                
                std::cout << "Choose a driver for your trip:\n";
                int free_count = 0;
                for (unsigned int i = 0; i < driver_count; ++i)
                {
                    if (drivers[i].Get_EmploymentStatus() == Free)
                    {
                        free_count++;
                        std::cout << "Driver #" << free_count << ":\n";
                        drivers[i].show_info();
                    }
                }

                if (free_count == 0)
                {
                    std::cerr << "No free drivers available.\n";
                }
                else
                {
                    int selection;
                    while (true)
                    {
                        std::cout << "Select driver number (1 - " << free_count << "): ";
                        std::cin >> selection;
                        if (selection >= 1 && selection <= free_count) break;
                        std::cerr << "Invalid selection.\n";
                    }

                    free_count = 0;
                    unsigned int selected_index;
                    for (unsigned int i = 0; i < driver_count; ++i)
                    {
                        if (drivers[i].Get_EmploymentStatus() == Free)
                        {
                            free_count++;
                            if (free_count == selection)
                            {
                                selected_index = i;
                                break;
                            }
                        }
                    }

                    std::string from, to;
                    do {
                        std::cout << "Enter pickup location: ";
                        std::cin >> from;
                    } while (containsSpecialChar(from) || containsDigit(from));

                    do {
                        std::cout << "Enter destination: ";
                        std::cin >> to;
                    } while (containsSpecialChar(to) || containsDigit(to));

                    double distance;
                    std::cout << "Enter distance (km): ";
                    std::cin >> distance;

                    Order new_order(&clients[client_number], &drivers[selected_index], from, to, distance);
                    new_order.assignOrder();
                    new_order.OrderInfo();
                    new_order.write_to_file(orders_file);

                    drivers[selected_index].Set_EmploymentStatus(true);

                    saveAllDrivers(drivers, drivers_file, driver_count);
                    saveAllClients(clients, clients_file, client_count);
                }
            }
        }

        delete[] drivers;
        delete[] orders;
    }

    saveAllClients(clients, clients_file, client_count);
    delete[] clients;
}

}

