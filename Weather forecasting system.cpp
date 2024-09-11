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
            // Handle memory problem
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

int main() {
    // Weather Forecasting System
    std::string apiKey = "31ade4b4739564885a532497ebf98459"; // Replace with your actual API key
    std::string baseUrl = "https://api.openweathermap.org/data/2.5/weather";
    WeatherForecastingSystem weatherSystem(apiKey, baseUrl);
    std::string weatherData = weatherSystem.fetchWeatherData("New York");
    weatherSystem.displayWeatherData(weatherData);

    return 0;
}