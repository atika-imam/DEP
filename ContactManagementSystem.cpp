#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Contact {
private:
    string name;
    string phoneNumber;

public:
    Contact(string n, string pn) : name(n), phoneNumber(pn) {}

    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }
};

vector<Contact> contactList;

void addContact(string name, string phoneNumber) {
    Contact newContact(name, phoneNumber);
    contactList.push_back(newContact);
}

void viewContacts() {
    for (const auto& contact : contactList) {
        cout << "Name: " << contact.getName() << ", Phone Number: " << contact.getPhoneNumber() << endl;
    }
}

void deleteContact(string name) {
    for (auto it = contactList.begin(); it != contactList.end(); ++it) {
        if (it->getName() == name) {
            contactList.erase(it);
            cout << "Contact deleted successfully." << endl;
            return;
        }
    }
    cout << "Contact not found." << endl;
}

void displayMenu() {
    cout << "Contact Management System" << endl;
    cout << "------------------------" << endl;
    cout << "1. Add Contact" << endl;
    cout << "2. View Contacts" << endl;
    cout << "3. Delete Contact" << endl;
    cout << "4. Exit" << endl;
}

void saveContactsToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& contact : contactList) {
            file << contact.getName() << "," << contact.getPhoneNumber() << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file." << endl;
    }
}

void loadContactsFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string name, phoneNumber;
            getline(iss, name, ',');
            getline(iss, phoneNumber, ',');
            addContact(name, phoneNumber);
        }
        file.close();
    } else {
        cout << "Unable to open file." << endl;
    }
}

int main() {
    int choice;
    string name, phoneNumber;

    loadContactsFromFile("contacts.txt");

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        
        // Ignore the newline character before using getline
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, phoneNumber);
                addContact(name, phoneNumber);
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                cout << "Enter name of contact to delete: ";
                getline(cin, name);
                deleteContact(name);
                break;
            case 4:
                saveContactsToFile("contacts.txt");
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}