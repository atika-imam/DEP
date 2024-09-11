#include <iostream>
#include <string>
#include <curl/curl.h>
using namespace std;

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
        if(curl) {
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
};


class HistoricalWeatherSystem {
public:
    string apiKey;
    string baseUrl;
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

    string fetchHistoricalWeatherData(const string& location, const string& date) {
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl = curl_easy_init();
        if(curl) {
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
};

int main() {
    WeatherForecastingSystem weatherSystem;
    weatherSystem.apiKey = "Your_API_Key"; 
    weatherSystem.baseUrl = "https://open-meteo.com/en/docs";
    
    HistoricalWeatherSystem historicalWeatherSystem;
    historicalWeatherSystem.apiKey = "YOUR_API_KEY"; 
    historicalWeatherSystem.baseUrl = "https://openweathermap.org/current";
    historicalWeatherSystem.historicalBaseUrl = "https://open-meteo.com/en/docs/historical-weather-api";

    // Fetch and display current weather data
    string weatherData = weatherSystem.fetchWeatherData("London");
    weatherSystem.displayWeatherData(weatherData);

    // Fetch and display historical weather data
    string historicalData = historicalWeatherSystem.fetchHistoricalWeatherData("London", "2023-08-01"); 
    historicalWeatherSystem.displayHistoricalWeatherData(historicalData);

    return 0;
}