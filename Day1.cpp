#pragma once

#include "solution.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>

void day1AProcess()
{
    const char* filePath = "data/Day1/DataA.txt";
    std::ifstream inputFile(filePath);

    // Check if the file is successfully opened
    if (!inputFile.is_open()) 
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }

    std::string line;
    std::string pair = "00";
    int count = 0;
    bool foundAny = false;
    char first;
    char last;

    char x;
    while (inputFile.get(x))
    {
        line += x;
        if (isdigit(x))
        {
            if (!foundAny)
            {
                first = x;
                last = x;
                foundAny = true;
            }
            else
            {
                last = x;
            }
        }
        else if (x == '\n' && foundAny)
        {            
            pair[0] = first;
            pair[1] = last;
            count += atoi(pair.c_str());
            foundAny = false;

            line.clear();
        }
    }

    std::cout << "Total found : " << count << std::endl;


    inputFile.close();
}

void day1BProcess()
{
    const char* filePath = "data/Day1/BData.txt";
    std::ifstream inputFile(filePath);
    std::vector<std::string> wordsToDetect = 
    { 
        "one", 
        "two", 
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine" 
    };
    std::unordered_map<std::string, std::string> wordToValue =
    {
        {"zero","0"},
        {"one","1"},
        {"two","2"},
        {"three","3"},
        {"four","4"},
        {"five","5"},
        {"six","6"},
        {"seven","7"},
        {"eight","8"},
        {"nine","9"}
    };

    std::string patternStr = "\\b(";
    for (const std::string& word : wordsToDetect) 
    {
        patternStr += word + "|";
    }
    patternStr.pop_back();
    patternStr += ")\\b.*\\b(";
    for (const std::string& word : wordsToDetect) 
    {
        patternStr += word + "|";
    }
    patternStr.pop_back();
    patternStr += ")\\b";

    std::regex pattern(patternStr);



    // Check if the file is successfully opened
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }

    std::string line;
    int count = 0;

    char x;
    while (inputFile.get(x))
    {
        line += x;
        if (x == '\n')
        {
            line = "abcone2threexyz";
            std::smatch match;
            if (std::regex_search(line, match, pattern) && match.size() == 2) {
                std::string first = match[1].str();
                std::string last = match[2].str();

                // Check if the detected word is in the unordered_map
                auto it1 = wordToValue.find(first);
                auto it2 = wordToValue.find(last);
                if (it1 != wordToValue.end() && it2 != wordToValue.end())
                {
                    count += atoi((it1->second + it2->second).c_str());
                }
            }

            line.clear();
        }
    }

    std::cout << "Total found : " << count << std::endl;


    inputFile.close();
}
