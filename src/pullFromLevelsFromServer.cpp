    #include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

// Write callback for curl
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Parse CSV string into matrix
std::vector<std::vector<int>> parseCSV(const std::string& csvData) {
    std::vector<std::vector<int>> matrix;
    std::istringstream ss(csvData);
    std::string line;

    while (std::getline(ss, line)) {
        std::istringstream rowStream(line);
        std::string cell;
        std::vector<int> row;

        while (std::getline(rowStream, cell, ',')) {
            if (!cell.empty())
                row.push_back(std::stoi(cell));
        }
        if (!row.empty())
            matrix.push_back(row);
    }
    return matrix;
}

// Download URL into string
std::string downloadURL(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response;
    if (!curl) return "";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "CURL error: " << curl_easy_strerror(res) << "\n";
        return "";
    }
    return response;
}
/*
int main() {
    std::string baseUrl = "https://alas.matf.bg.ac.rs/~mr22033/";

    // 1) Get directory listing
    std::string listing = downloadURL(baseUrl);

    // 2) Extract all "levelNN/" links using regex
    std::regex re("href=\"(level[0-9]+)/\"");
    std::smatch match;
    std::vector<std::string> levelFolders;

    std::string::const_iterator searchStart(listing.cbegin());
    while (std::regex_search(searchStart, listing.cend(), match, re)) {
        levelFolders.push_back(match[1]);
        searchStart = match.suffix().first;
    }

    // 3) For each folder, download matrix.csv
    std::vector<std::vector<std::vector<int>>> allMatrices;

    for (const auto& folder : levelFolders) {
        std::string url = baseUrl + folder + "/matrix.csv";
        std::string csvData = downloadURL(url);

        if (!csvData.empty()) {
            auto matrix = parseCSV(csvData);
            allMatrices.push_back(matrix);
            std::cout << "Downloaded " << folder << " with size "
                << matrix.size() << "x"
                << (matrix.empty() ? 0 : matrix[0].size()) << "\n";
        }
    }

    std::cout << "Total matrices pulled: " << allMatrices.size() << "\n";
    return 0;
}
*/