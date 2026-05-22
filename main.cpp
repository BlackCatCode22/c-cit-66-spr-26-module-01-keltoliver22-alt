#include "crow_all.h"
#include "json.hpp"
#include <iostream>
#include <string>
#include <curl/curl.h>

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fetchWeatherData(const std::string& url, bool isNWS = false) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

        struct curl_slist* headers = NULL;
        if (isNWS) {
            headers = curl_slist_append(headers, "User-Agent: FCC-Student-App (student@fresno.edu)");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }

        res = curl_easy_perform(curl);
        
        if(headers) {
            curl_slist_free_all(headers);
        }
        
        if(res != CURLE_OK) {
            std::cerr << "CURL Error: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            return "";
        }
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        std::string fresnoRaw = fetchWeatherData("https://api.weather.gov/gridpoints/HNX/53,100/forecast", true);
        std::string nyRaw = fetchWeatherData("https://api.weather.gov/gridpoints/OKX/33,37/forecast", true);
        std::string londonRaw = fetchWeatherData("https://api.open-meteo.com/v1/forecast?latitude=51.5085&longitude=-0.1257&current=temperature_2m,weather_code&temperature_unit=fahrenheit");

        std::string fresnoTemp = "N/A", fresnoCond = "Data Unavailable";
        std::string nyTemp = "N/A", nyCond = "Data Unavailable";
        std::string londonTemp = "N/A", londonCond = "Data Unavailable";

        if (!fresnoRaw.empty()) {
            try {
                auto data = json::parse(fresnoRaw);
                auto currentPeriod = data["properties"]["periods"][0];
                fresnoTemp = std::to_string(currentPeriod["temperature"].get<int>()) + "°F";
                fresnoCond = currentPeriod["shortForecast"].get<std::string>();
            } catch (...) {}
        }

        if (!nyRaw.empty()) {
            try {
                auto data = json::parse(nyRaw);
                auto currentPeriod = data["properties"]["periods"][0];
                nyTemp = std::to_string(currentPeriod["temperature"].get<int>()) + "°F";
                nyCond = currentPeriod["shortForecast"].get<std::string>();
            } catch (...) {}
        }

        if (!londonRaw.empty()) {
            try {
                auto data = json::parse(londonRaw);
                double temp = data["current"]["temperature_2m"].get<double>();
                londonTemp = std::to_string(static_cast<int>(temp)) + "°F";
                
                int code = data["current"]["weather_code"].get<int>();
                if (code == 0) londonCond = "Clear Sky";
                else if (code <= 3) londonCond = "Partly Cloudy";
                else if (code <= 48) londonCond = "Foggy";
                else if (code <= 65) londonCond = "Rainy";
                else if (code <= 77) londonCond = "Snowy";
                else londonCond = "Stormy";
            } catch (...) {}
        }

        std::string html = R"html(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Global Weather Dashboard</title>
            <style>
                body {
                    font-family: '-apple-system', BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
                    background: linear-gradient(135deg, #0f172a 0%, #1e1e38 100%);
                    color: #f8fafc;
                    margin: 0;
                    padding: 60px 20px;
                    display: flex;
                    flex-direction: column;
                    align-items: center;
                    min-height: 100vh;
                }
                h1 { font-size: 2.5rem; font-weight: 800; color: #38bdf8; margin-bottom: 40px; letter-spacing: -0.05em; }
                .dashboard { display: flex; gap: 24px; flex-wrap: wrap; justify-content: center; max-width: 1100px; width: 100%; }
                .card {
                    background: rgba(30, 41, 59, 0.7);
                    backdrop-filter: blur(12px);
                    border: 1px solid #334155;
                    border-radius: 24px;
                    padding: 32px 24px;
                    width: 260px;
                    text-align: center;
                    box-shadow: 0 10px 25px -5px rgba(0, 0, 0, 0.3);
                    transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
                }
                .card:hover { transform: translateY(-6px); border-color: #38bdf8; box-shadow: 0 20px 30px -10px rgba(56, 189, 248, 0.2); }
                .location { font-size: 1.4rem; color: #94a3b8; font-weight: 700; letter-spacing: -0.02em; }
                .temp { font-size: 3.5rem; font-weight: 900; margin: 16px 0; color: #ffffff; }
                .condition { color: #38bdf8; font-weight: 600; font-size: 1.05rem; }
                .footer { margin-top: auto; padding-top: 50px; font-size: 0.85rem; color: #475569; letter-spacing: 0.05em; text-transform: uppercase; }
            </style>
        </head>
        <body>
            <h1>Vibe-Coded Global Weather Dashboard</h1>
            <div class="dashboard">
                <div class="card">
                    <div class="location">Fresno, CA</div>
                    <div class="temp">)html" + fresnoTemp + R"html(</div>
                    <div class="condition">)html" + fresnoCond + R"html(</div>
                </div>
                <div class="card">
                    <div class="location">New York, NY</div>
                    <div class="temp">)html" + nyTemp + R"html(</div>
                    <div class="condition">)html" + nyCond + R"html(</div>
                </div>
                <div class="card">
                    <div class="location">London, UK</div>
                    <div class="temp">)html" + londonTemp + R"html(</div>
                    <div class="condition">)html" + londonCond + R"html(</div>
                </div>
            </div>
            <div class="footer">Built with Crow C++ & Live Multi-API Architecture</div>
        </body>
        </html>
        )html";

        return crow::response(html);
    });

    app.port(8080).multithreaded().run();
}
