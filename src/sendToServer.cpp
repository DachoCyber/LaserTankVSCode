#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include <iostream>

void sendMoveCount(const std::string& playerName, int moves) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL\n";
        return;
    }

    // Force HTTP/2 to avoid HTTP/3 (QUIC) dependencies
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);

    // Prepare JSON payload
    std::string json = R"({"player":")" + playerName + R"(","moves":)" + std::to_string(moves) + "}";

    // Set headers
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Accept: application/json");

    // Set options
    curl_easy_setopt(curl, CURLOPT_URL, "https://alas.matf.bg.ac.rs/~mr22033/update_moves.php");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json.length());

    // Perform the request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }

    // Cleanup
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}