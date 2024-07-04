#include "dictionary.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

void Dictionary::addWord(const std::string& englishWord, const std::string& russianTranslation, const std::string& belarusianTranslation) {
    std::string lowercaseWord = englishWord;
    std::transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);
    dictionary[lowercaseWord] = std::make_pair(russianTranslation, belarusianTranslation);
    std::cout << "Added word: " << lowercaseWord << std::endl;
}

void Dictionary::removeWord(const std::string& englishWord) {
    std::string lowercaseWord = englishWord;
    std::transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);
    dictionary.erase(lowercaseWord);
}

std::tuple<std::string, std::string, std::string> Dictionary::findTranslation(const std::string& word) {
    std::string lowercaseWord = word;
    std::transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);
    for (const auto& pair : dictionary) {
        if (pair.first == lowercaseWord || pair.second.first == lowercaseWord || pair.second.second == lowercaseWord) {
            return std::make_tuple(pair.first, pair.second.first, pair.second.second);
        }
    }
    return std::make_tuple("Translation not found", "Translation not found", "Translation not found");
}

void Dictionary::replaceTranslation(const std::string& englishWord, const std::string& newRussianTranslation, const std::string& newBelarusianTranslation) {
    std::string lowercaseWord = englishWord;
    std::transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);
    if (dictionary.count(lowercaseWord) > 0) {
        dictionary[lowercaseWord] = std::make_pair(newRussianTranslation, newBelarusianTranslation);
        std::cout << "Replaced translation for word: " << lowercaseWord << std::endl;
    } else {
        std::cout << "Word not found for replacement: " << lowercaseWord << std::endl;
    }
}

void Dictionary::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string englishWord, russianTranslation, belarusianTranslation;

        ss >> englishWord >> russianTranslation >> belarusianTranslation;
        if (!englishWord.empty() && !russianTranslation.empty() && !belarusianTranslation.empty()) {
            addWord(englishWord, russianTranslation, belarusianTranslation);
        }
    }
}

void Dictionary::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    for (const auto& pair : dictionary) {
        file << pair.first << ' ' << pair.second.first << ' ' << pair.second.second << '\n';
    }
}

std::vector<std::tuple<std::string, std::string, std::string>> Dictionary::getAllWords() {
    std::vector<std::tuple<std::string, std::string, std::string>> words;
    for (const auto& pair : dictionary) {
        words.emplace_back(pair.first, pair.second.first, pair.second.second);
    }
    return words;
}
