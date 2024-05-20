#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
using namespace std;

class Order;
class MenuItem {
public:
    string name;
    double price;

    MenuItem(const string& name, double price) : name(name), price(price) {

    }
    ~MenuItem() {
    }

    void display() const {
        cout << name << ": $" << price << endl;
    }


    bool operator==(const MenuItem& other) const {
        return name == other.name;
    }

    friend ostream& operator<<(ostream& os, const MenuItem& item);
};

ostream& operator<<(ostream& os, const MenuItem& item) {
    os << item.name << ": $" << item.price;
    return os;
}


class Menu {
private:
    vector<MenuItem> menuItems;

public:
    Menu() {}
    ~Menu() {
    }

    void addItem(const MenuItem& item) {
        menuItems.push_back(item);
    }

    void displayMenu() const {
        for (const auto& item : menuItems) {
            item.display();
        }
    }

    const vector<MenuItem>& getItems() const {
        return menuItems;
    }

    friend void chooseOrder(Menu& menu, Order& order);
};


class Order {
private:
    vector<MenuItem> orderItems;
    static int orderCount;

public:
    Order() {
        ++orderCount;
    }

    ~Order() {

    }

    void addItem(const MenuItem& item) {
        orderItems.push_back(item);
    }

    double calculateTotal() const {
        double total = 0.0;
        for (const auto& item : orderItems) {
            total += item.price;
        }
        return total;
    }

    void displayOrder() const {
        for (const auto& item : orderItems) {
            item.display();
        }
    }

    static int getOrderCount() {
        return orderCount;
    }

    friend void chooseOrder(Menu& menu, Order& order);
};

int Order::orderCount = 0;

void chooseOrder(Menu& menu, Order& order) {
    string itemName;
    string more;

    do {
        cout << "Enter the name of the item you want to add to your order: ";
        getline(cin, itemName);

        bool found = false;
        for (const auto& item : menu.getItems()) {
            if (item.name == itemName) {
                order.addItem(item);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Item not found in the menu. Please try again." << endl;
        } else {
            cout << "Item added to order." << endl;
        }

        cout << "Do you want to add another item? (yes/no): ";
        getline(cin, more);

    } while (more.size() > 0 && (more[0] == 'yes' || more[0] == 'Yes'));
}

//****************************************************************************************************************************
class Payment {
private:
    double amount;

public:
    Payment(double amount) : amount(amount) {}
    ~Payment() {
    }

    void processPayment() const {
        cout << "Processing payment of $" << amount << endl;
    }

    void generateReceipt() const {
        cout << "Receipt: Payment of $" << amount << " received." << endl;
    }
};
//********************************************************************************************************************************
class Staff {
protected:
    string name;
    string role;

public:
    Staff(const string& name, const string& role) : name(name), role(role) {}
    virtual ~Staff() {

    }

    string getName() const {
        return name;
    }

    string getRole() const {
        return role;
    }

    virtual void displayRole() const {
        cout << "Role: " << role << endl;
    }
};
//********************************************************************************************************************************
class Chef : public Staff {
public:
    Chef(const string& name) : Staff(name, "Chef") {}

    void displayRole() const override { // Virtual function override
        cout << "Chef: " << getName() << endl;
    }
};

//************************************************************************************************************************************
class Waiter : public Staff {
public:
    Waiter(const string& name) : Staff(name, "Waiter") {}

    void displayRole() const override { // Virtual function override
        cout << "Waiter: " << getName() << endl;
    }
};

//***************************************************************************************************************************************
template<typename T>
void displayItems(const vector<T>& items) {
    for (const auto& item : items) {
        cout << item << endl;
    }
}

// Chatbot Class
class Chatbot {
public:
    void startChat() const {
        string input;
        cout << "Welcome to the Help Chatbot! Type 'help' to see available commands or 'exit' to quit." << endl;
        do {

            getline(cin, input);
            if (input == "help") {
                displayHelp();
            } else if (input == "menu") {
                displayMenuHelp();
            } else if (input != "exit") {
                cout << "Unknown command. Type 'help' to see available commands." << endl;
            }
        } while (input != "exit");
    }

private:
    void displayHelp() const {
        cout << "Available commands:" << endl;
        cout << "  help - Show this help message" << endl;
        cout << "  menu - Get help with the menu" << endl;
        cout << "  exit - Exit the chatbot" << endl;
    }

    void displayMenuHelp() const {
        cout << "Menu Help: You can order items by typing their name during the ordering process." << endl;
    }
};

int main() {
    Menu menu;
    menu.addItem(MenuItem("Burger", 50));
    menu.addItem(MenuItem("Fries", 15));
    menu.addItem(MenuItem("Salad", 5));
    menu.addItem(MenuItem("Soup", 10));
    menu.addItem(MenuItem("Pasta", 7));
    menu.addItem(MenuItem("drink", 2));
    menu.addItem(MenuItem("Chicken soup", 40));


    cout << "Menu:" << endl;
    menu.displayMenu();


    Order order;


    chooseOrder(menu, order);


    cout << "\nOrder:" << endl;
    order.displayOrder();


    cout << "\nTotal: $" << order.calculateTotal() << endl;


    Payment payment(order.calculateTotal());
    payment.processPayment();
    payment.generateReceipt();


    Chef chef("David");
    Waiter waiter("John");
    cout << "\nStaff Roles:" << endl;
    chef.displayRole();
    waiter.displayRole();


    cout << "\nTotal Orders: " << Order::getOrderCount() << endl;

//***********************************************************************************************************************
    Chatbot chatbot;
    chatbot.startChat();

    return 0;
}
