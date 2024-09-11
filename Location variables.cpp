#include <iostream>
#include <string>
using namespace std;

class WeatherVariable {
private:
    static const int MAX_VARIABLES = 100;
    struct Variable {
        string name;
        double value;
    };
    Variable variables[MAX_VARIABLES];
    int variableCount;

public:
    WeatherVariable() : variableCount(0) {}

    void defineVariable(const string& name, double value) {
        for (int i = 0; i < variableCount; ++i) {
            if (variables[i].name == name) {
                variables[i].value = value; // Update existing variable
                return;
            }
        }
        if (variableCount < MAX_VARIABLES) {
            variables[variableCount].name = name;
            variables[variableCount].value = value;
            variableCount++;
        } else {
            cout << "Cannot add more variables. Maximum limit reached." << endl;
        }
    }

    void listVariables() const {
        for (int i = 0; i < variableCount; ++i) {
            cout << variables[i].name << ": " << variables[i].value << endl;
        }
    }
};

int main() {
    WeatherVariable weather;

    // Define some weather variables
    weather.defineVariable("temperature", 45.5);
    weather.defineVariable("humidity", 60.0);
    weather.defineVariable("windSpeed", 12.3);

    // List all variables
    cout << "Weather Variables:" << endl;
    weather.listVariables();

    return 0;
}