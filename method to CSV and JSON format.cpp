#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>  // for file operations like input, output etc
#include <nlohmann/json.hpp> 

using namespace std;
using json = nlohmann::json; // For JSON handling

class WeatherForecastingSystem {
private:
    string apiKey;
    string baseUrl;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* s) {
        size_t newLength = size * nmemb;
        size_t oldLength = s->size();
        try {
            s->resize(oldLength + newLength);
        } catch (bad_alloc &e) {
            return 0;
        }
        copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength);
        return size * nmemb;
    }

public:
    WeatherForecastingSystem(const string& apiKey, const string& baseUrl)
        : apiKey(apiKey), baseUrl(baseUrl) {}

    string fetchWeatherData(const string& location) {
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            string url = baseUrl + "?q=" + location + "&appid=" + apiKey;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    }

    void displayWeatherData(const string& data) {
        cout << "Weather Data: " << data << endl;
    }

    void exportWeatherDataToCSV(const string& data, const string& filename) {
        // Simple CSV export: You may need to parse the JSON data to properly structure the CSV
        ofstream file(filename);
        if (file.is_open()) {
            file << "weather_data\n";
            file << data << "\n";
            file.close();
        }
    }

    void exportWeatherDataToJSON(const string& data, const string& filename) {
        // Assuming data is a valid JSON string
        ofstream file(filename);
        if (file.is_open()) {
            file << data;
            file.close();
        }
    }
};

class HistoricalWeatherSystem {
private:
    string apiKey;
    string historicalBaseUrl;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* s) {
        size_t newLength = size * nmemb;
        size_t oldLength = s->size();
        try {
            s->resize(oldLength + newLength);
        } catch (bad_alloc &e) {
            return 0;
        }
        copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength);
        return size * nmemb;
    }

public:
    HistoricalWeatherSystem(const string& key, const string& url)
        : apiKey(key), historicalBaseUrl(url) {}

    string fetchHistoricalWeatherData(const string& location, const string& date) {
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            string url = historicalBaseUrl + "?q=" + location + "&date=" + date + "&appid=" + apiKey;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    }

    void displayHistoricalWeatherData(const string& data) {
        cout << "Historical Weather Data: " << data << endl;
    }

    void exportHistoricalWeatherDataToCSV(const string& data, const string& filename) {
        // Simple CSV export: You may need to parse the JSON data to properly structure the CSV
        ofstream file(filename);
        if (file.is_open()) {
            file << "historical_weather_data\n";
            file << data << "\n";
            file.close();
        }
    }

    void exportHistoricalWeatherDataToJSON(const string& data, const string& filename) {
        // Assuming data is a valid JSON string
        ofstream file(filename);
        if (file.is_open()) {
            file << data;
            file.close();
        }
    }
};

int main() {
    string currentWeatherApiKey = "YOUR_CURRENT_API_KEY"; // Replace with your actual API key
    string currentWeatherBaseUrl = "https://api.open-meteo.com/v1/forecast";
    
    string historicalWeatherApiKey = "YOUR_HISTORICAL_API_KEY"; // Replace with your actual API key
    string historicalWeatherBaseUrl = "https://api.weatherbit.io/v2.0/history/daily";

    WeatherForecastingSystem weatherSystem(currentWeatherApiKey, currentWeatherBaseUrl);
    HistoricalWeatherSystem historicalWeatherSystem(historicalWeatherApiKey, historicalWeatherBaseUrl);

    // Fetch and display current weather data
    string weatherData = weatherSystem.fetchWeatherData("London");
    weatherSystem.displayWeatherData(weatherData);

    // Export current weather data to CSV and JSON
    weatherSystem.exportWeatherDataToCSV(weatherData, "current_weather.csv");
    weatherSystem.exportWeatherDataToJSON(weatherData, "current_weather.json");

    // Fetch and display historical weather data
    string historicalData = historicalWeatherSystem.fetchHistoricalWeatherData("London", "2023-08-01");
    historicalWeatherSystem.displayHistoricalWeatherData(historicalData);

    // Export historical weather data to CSV and JSON
    historicalWeatherSystem.exportHistoricalWeatherDataToCSV(historicalData, "historical_weather.csv");
    historicalWeatherSystem.exportHistoricalWeatherDataToJSON(historicalData, "historical_weather.json");

    return 0;
}