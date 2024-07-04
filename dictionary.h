#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <map>
#include <tuple>
#include <vector>

class Dictionary {
private:
    std::map<std::string, std::pair<std::string, std::string>> dictionary;

public:
    void addWord(const std::string& englishWord, const std::string& russianTranslation, const std::string& belarusianTranslation);
    void removeWord(const std::string& englishWord);
    std::tuple<std::string, std::string, std::string> findTranslation(const std::string& word);
    void replaceTranslation(const std::string& englishWord, const std::string& newRussianTranslation, const std::string& newBelarusianTranslation);
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    std::vector<std::tuple<std::string, std::string, std::string>> getAllWords();
};

#endif // DICTIONARY_H
