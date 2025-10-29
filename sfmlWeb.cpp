#include <iostream>
#include <string>
#include <curl/curl.h>

static size_t WriteCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    std::string* response = static_cast<std::string*>(userdata);
    response->append(ptr, size * nmemb);
    return size * nmemb;
}

void sendScore(const std::string& name, int score, int level) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize curl\n";
        return;
    }

    // Escape the name for URL encoding
    char* escaped_name = curl_easy_escape(curl, name.c_str(), name.length());
    if (!escaped_name) {
        std::cerr << "Failed to escape name\n";
        curl_easy_cleanup(curl);
        return;
    }

    // Prepare POST data
    std::string post_fields = "name=" + std::string(escaped_name) + "&score=" + std::to_string(score) + "&level=" + std::to_string(level);
    curl_free(escaped_name);
    std::cout << score << std::endl;

    std::string response;

    // Set cURL options
    curl_easy_setopt(curl, CURLOPT_URL, "https://alas.matf.bg.ac.rs/~mr22033/send-score.php");
    curl_easy_setopt(curl, CURLOPT_POST, 1L); // Explicit POST method
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // HTTPS security settings
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

    // Execute request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL failed: " << curl_easy_strerror(res) << '\n';
    }
    else {
        std::cout << "Server response: " << response << '\n';
    }

    curl_easy_cleanup(curl);
}