#include <iostream>
#include <string>
using namespace std;

class Location {
public:
    string name;
    double latitude;
    double longitude;
};

class LocationManager {
private:
    static const int MAX_LOCATIONS = 100;
    Location locations[MAX_LOCATIONS];
    int locationCount;

public:
    LocationManager() : locationCount(0) {}

    void addLocation(const string& name, double latitude, double longitude) {
        if (locationCount < MAX_LOCATIONS) {
            locations[locationCount].name = name;
            locations[locationCount].latitude = latitude;
            locations[locationCount].longitude = longitude;
            locationCount++;
        } else {
            cout << "Cannot add more locations. Maximum limit reached." << endl;
        }
    }

    void removeLocation(const string& name) {
        bool found = false;
        for (int i = 0; i < locationCount; ++i) {
            if (locations[i].name == name) {
            	
                for (int j = i; j < locationCount - 1; ++j) {
                    locations[j] = locations[j + 1];
                }
                locationCount--;
                found = true;
                cout << "Location \"" << name << "\" removed successfully." << endl;
                break;
            }
        }
        if (!found) {
            cout << "Location \"" << name << "\" not found." << endl;
        }
    }

    void listLocations() const {
        for (int i = 0; i < locationCount; ++i) {
            cout << "Name: " << locations[i].name << ", Latitude: " << locations[i].latitude << ", Longitude: " << locations[i].longitude << endl;
        }
    }
};

int main() {
    LocationManager manager;
    int choice;
    string name;
    double latitude, longitude;

    do {
        cout << "1. Add Location\n2. Remove Location\n3. List Locations\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter latitude: ";
                cin >> latitude;
                cout << "Enter longitude: ";
                cin >> longitude;
                manager.addLocation(name, latitude, longitude);
                break;
            case 2:
                cout << "Enter name of location to remove: ";
                cin >> name;
                manager.removeLocation(name);
                break;
            case 3:
                manager.listLocations();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}