#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

class customer_arrival;
class Customer_busy;
class idle_teller;

customer_arrival* frontt = NULL;
customer_arrival* rear = NULL;
Customer_busy* Start = NULL;
idle_teller* idle_front = NULL;
idle_teller* idle_rear = NULL;

class idle_teller {
public:
    int info;
    idle_teller* next;

    idle_teller* create() {
        idle_teller* newteller = new idle_teller;
        newteller->next = NULL;
        return newteller;
    }

    void teller_idle(int number) {
        idle_teller* temp1 = create();
        temp1->info = number;
        if (idle_front == NULL) {
            idle_front = temp1;
            idle_rear = temp1;
        } else {
            idle_rear->next = temp1;
            idle_rear = temp1;
        }
    }

    int teller_count() {
        int count = 0;
        idle_teller* temp = idle_front;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void teller_busy() {
        if (idle_front == NULL) {
            cout << "NO IDLE TELLERS\n";
        } else {
            idle_teller* temp1 = idle_front;
            idle_front = idle_front->next;
            cout << "Teller " << temp1->info << " is on service.\n" << endl;
            delete temp1;
        }
    }
};

class Customer_busy {
public:
    int customer_number;
    int teller_number;
    Customer_busy* next;

    Customer_busy* create(int customer, int teller) {
        Customer_busy* newBusy = new Customer_busy;
        newBusy->customer_number = customer;
        newBusy->teller_number = teller;
        newBusy->next = NULL;
        return newBusy;
    }

    void add_customer(int customer, int teller) {
        Customer_busy* temp1 = create(customer, teller);
        if (Start == NULL) {
            Start = temp1;
        } else {
            Customer_busy* temp2 = Start;
            while (temp2->next != NULL) {
                temp2 = temp2->next;
            }
            temp2->next = temp1;
        }
    }

    void display_busy_customers() {
        Customer_busy* temp = Start;
        while (temp != NULL) {
            cout << "Customer " << temp->customer_number << " is being served by Teller " << temp->teller_number << endl;
            temp = temp->next;
        }
    }
};

class customer_arrival {
public:
    int info;
    customer_arrival* next;

    customer_arrival* create() {
        customer_arrival* newcustomer = new customer_arrival;
        newcustomer->next = NULL;
        return newcustomer;
    }

    void customer_add(int number) {
        customer_arrival* temp1 = create();
        temp1->info = number;
        if (frontt == NULL) {
            frontt = temp1;
            rear = temp1;
        } else {
            rear->next = temp1;
            rear = temp1;
        }
    }

    void customer_delete() {
        if (frontt == NULL) {
            cout << "The Queue is empty, add new customers.\n" << endl;
        } else {
            customer_arrival* temp1 = frontt;
            frontt = frontt->next;
            delete temp1;
        }
    }

    void display_all_customers() {
        customer_arrival* temp = frontt;
        while (temp != NULL) {
            cout << temp->info << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    int customer_count() {
        int count = 0;
        customer_arrival* temp = frontt;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }
};

class linked_accounts {
public:
    int customerID;
    int serviceTime;
    string relationType;
    vector<linked_accounts*> relatives;

    linked_accounts(int id, int time, string relation = "")
        : customerID(id), serviceTime(time), relationType(relation) {}

    void addRelative(linked_accounts* relative) {
        relatives.push_back(relative);
    }

    void displayRelatives(int depth = 0) {
        for (int i = 0; i < depth; ++i) cout << "--";
        cout << "Customer " << customerID << " (Service time: " << serviceTime << " mins) "
             << (relationType.empty() ? "" : "[" + relationType + "]") << endl;
        for (auto& child : relatives) {
            child->displayRelatives(depth + 1);
        }
    }
};

class Banksystem {
    customer_arrival customers;
    idle_teller tellers;
    vector<linked_accounts*> activeCustomers; // Tracks current customers

public:
    Banksystem(int numTellers) {
        srand(time(0));
        for (int i = 1; i <= numTellers; ++i) {
            tellers.teller_idle(i);
        }
    }

    void addCustomer(int customerID) {
        customers.customer_add(customerID);
        cout << "Customer " << customerID << " added to the queue.\n" << endl;
    }

    void processCustomers(int numToProcess) {
        int availableTellers = tellers.teller_count();
        int customersToProcess = min(numToProcess, availableTellers);

        for (int i = 0; i < customersToProcess; ++i) {
            if (frontt == NULL) {
                cout << "No more customers in queue.\n" << endl;
                return;
            }
            int serviceTime = rand() % 20 + 1;
            customer_arrival* currentCustomer = frontt;
            idle_teller* currentTeller = idle_front;

            cout << "Customer " << currentCustomer->info << " is being served by Teller " << currentTeller->info
                 << " for " << serviceTime << " minutes.\n" << endl;

            linked_accounts* newCustomerNode = new linked_accounts(currentCustomer->info, serviceTime);

            if (!activeCustomers.empty()) {
                newCustomerNode->addRelative(activeCustomers.back());
            }

            activeCustomers.push_back(newCustomerNode);
            customers.customer_delete();
            tellers.teller_busy();
        }
    }

    void addRelative(int customerID, int relativeID, int serviceTime, string relation) {
        for (auto& customer : activeCustomers) {
            if (customer->customerID == customerID) {
                linked_accounts* newRelative = new linked_accounts(relativeID, serviceTime, relation);
                customer->addRelative(newRelative);
                cout << "Added " << relation << " with ID " << relativeID << " to Customer " << customerID << ".\n" << endl;
                return;
            }
        }
        cout << "Customer ID " << customerID << " not found in active customers.\n" << endl;
    }

    void displayCustomerRelatives(int customerID) {
        for (auto& customer : activeCustomers) {
            if (customer->customerID == customerID) {
                cout << "Displaying relatives for Customer " << customerID << ":\n" << " " << endl;
                customer->displayRelatives();
                return;
            }
        }
        cout << "Customer ID " << customerID << " not found in active customers.\n" << endl;
    }
};

int main() {
    int n, id_cust, x;
    cout << "Enter number of tellers: ";
    cin >> n;
    Banksystem bankSystem(n);

    int c;
    int f = 0;
    while (f == 0) {
        cout << "Enter 1 to Add Customers to the queue\n"
             << "2 to Process customers\n"
             << "3 to add relatives to the customers\n"
             << "4 to view the people linked with the customers\n"
             << "5 to exit" << endl;
        cin >> c;

        if (c == 1) {
            cout << "Enter no. of customers to add: ";
            cin >> x;
            for (int i = 0; i < x; i++) {
                cout << "Enter the id of customer: ";
                cin >> id_cust;
                bankSystem.addCustomer(id_cust);
            }
        } else if (c == 2) {
            bankSystem.processCustomers(x);
        } else if (c == 3) {
            cout << "Enter a customer id to show its previous linked accounts: ";
            cin >> id_cust;
            bankSystem.addRelative(id_cust, 201, 10, "Parent");
            bankSystem.addRelative(id_cust, 202, 5, "Sibling");
        } else if (c == 4) {
            cout << "\nCustomer and Relative Tree for Customer you have entered:\n";
            bankSystem.displayCustomerRelatives(id_cust);
        } else if (c == 5) {
            f = 1;
            cout << " Exiting the Bank Queue\n***Thanks for Visiting!!***\nWe will see you Later\n" << endl;
        } else {
            cout << "Invalid input" << endl;
        }
    }
    return 0;
}
