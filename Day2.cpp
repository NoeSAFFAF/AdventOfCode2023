#pragma once

#include "solution.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>

using namespace std;

void day2AProcess()
{
    const char* filePath = "data/Day2/DataA.txt";
    std::ifstream inputFile(filePath);

    // Check if the file is successfully opened
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }

    int count = 0;
    int countAll = 0;
    int idLine = 0;
    string line;
    while (std::getline(inputFile, line))
    {
        idLine++;
        countAll += idLine;
        cout << line << endl;

        std::regex pattern("(\\d+)\\s+(\\w+)");

        // Create an iterator to iterate over matches
        std::sregex_iterator iter(line.begin(), line.end(), pattern);
        std::sregex_iterator end;

        // Store the captured substrings in a vector
        while (iter != end) {
            std::smatch match = *iter;
            int i = std::stoi(match[1].str());
            string s = match[2].str();
            
            if (s == "red" && i > 12)
            {
                cout << "Found extra red" << endl;
                count += idLine;
                break;
            }
            
            if (s == "green" && i > 13)
            {
                cout << "Found extra green" << endl;
                count += idLine;
                break;
            }

            if (s == "blue" && i > 14)
            {
                cout << "Found extra blue" << endl;
                count += idLine;
                break;
            }
            
            ++iter;
        }
    }

    std::cout << "Total found : " << count << std::endl;
    std::cout << "Final answer : " << countAll - count << std::endl;

    inputFile.close();
}


void day2BProcess()
{
    const char* filePath = "data/Day2/DataB.txt";
    std::ifstream inputFile(filePath);

    // Check if the file is successfully opened
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }

    int count = 0;
    int idLine = 0;
    string line;
    while (std::getline(inputFile, line))
    {
        int bestBlue = 0;
        int bestRed = 0;
        int bestGreen = 0;

        idLine++;
        cout << line << endl;

        std::regex pattern("(\\d+)\\s+(\\w+)");

        // Create an iterator to iterate over matches
        std::sregex_iterator iter(line.begin(), line.end(), pattern);
        std::sregex_iterator end;

        // Store the captured substrings in a vector
        while (iter != end) {
            std::smatch match = *iter;
            int i = std::stoi(match[1].str());
            string s = match[2].str();

            if (s == "red")
            {
                bestRed = max(i, bestRed);
            }

            if (s == "green")
            {
                bestGreen = max(i, bestGreen);
            }

            if (s == "blue")
            {
                bestBlue = max(i, bestBlue);
            }

            ++iter;
        }

        count += (bestBlue * bestGreen * bestRed);
    }

    std::cout << "Total found : " << count << std::endl;

    inputFile.close();
}