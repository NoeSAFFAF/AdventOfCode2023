#pragma once

#include "solution.h"

#include <iostream>
#include <fstream>
#include <string>

void day1Process()
{
    const char* filePath = "data/Day1Data.txt";
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