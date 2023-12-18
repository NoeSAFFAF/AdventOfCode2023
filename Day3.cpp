#pragma once

#include "solution.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>

using namespace std;

bool isConnectedGear(const std::vector<std::vector<char>>& matrix, size_t i, size_t j, int& gearI, int& gearJ)
{
    // Check the left neighbor
    if (j > 0 && (matrix[i][j - 1] == '*'))
    {
        gearI = i;
        gearJ = j-1;
        return true;
    }

    // Check the right neighbor
    if (j < matrix[i].size() - 1 && (matrix[i][j + 1] == '*'))
    {
        gearI = i;
        gearJ = j+1;
        return true;
    }

    // Check the above neighbor
    if (i > 0 && (matrix[i - 1][j] == '*'))
    {
        gearI = i-1;
        gearJ = j;
        return true;
    }

    // Check the below neighbor
    if (i < matrix.size() - 1 && (matrix[i + 1][j] == '*'))
    {
        gearI = i+1;
        gearJ = j;
        return true;
    }

    // Check the top-left diagonal neighbor
    if (i > 0 && j > 0 && (matrix[i - 1][j - 1] == '*'))
    {
        gearI = i-1;
        gearJ = j-1;
        return true;
    }

    // Check the top-right diagonal neighbor
    if (i > 0 && j < matrix[i].size() - 1 && (matrix[i - 1][j + 1] == '*'))
    {
        gearI = i-1;
        gearJ = j+1;
        return true;
    }

    // Check the bottom-left diagonal neighbor
    if (i < matrix.size() - 1 && j > 0  && (matrix[i + 1][j - 1] == '*'))
    {
        gearI = i+1;
        gearJ = j-1;
        return true;
    }

    // Check the bottom-right diagonal neighbor
    if (i < matrix.size() - 1 && j < matrix[i].size() - 1 && (matrix[i + 1][j + 1] == '*'))
    {
        gearI = i+1;
        gearJ = j+1;
        return true;
    }

    return false;
}

bool isConnectedIndex(const std::vector<std::vector<char>>& matrix, size_t i, size_t j) 
{
   // Check the left neighbor
    if (j > 0 && (!isdigit(matrix[i][j - 1]) && matrix[i][j - 1] != '.')) 
    {
        return true;
    }

    // Check the right neighbor
    if (j < matrix[i].size() - 1 && (!isdigit(matrix[i][j + 1]) && matrix[i][j + 1] != '.')) 
    {
        return true;
    }

    // Check the above neighbor
    if (i > 0 && (!isdigit(matrix[i - 1][j]) && matrix[i - 1][j] != '.'))
    {
        return true;
    }

    // Check the below neighbor
    if (i < matrix.size() - 1 && (!isdigit(matrix[i + 1][j]) && matrix[i + 1][j] != '.')) 
    {
        return true;
    }

    // Check the top-left diagonal neighbor
    if (i > 0 && j > 0 && (!isdigit(matrix[i - 1][j - 1]) && matrix[i - 1][j - 1] != '.')) 
    {
        return true;
    }

    // Check the top-right diagonal neighbor
    if (i > 0 && j < matrix[i].size() - 1 && (!isdigit(matrix[i - 1][j + 1]) && matrix[i - 1][j + 1] != '.')) 
    {
        return true;
    }

    // Check the bottom-left diagonal neighbor
    if (i < matrix.size() - 1 && j > 0 && (!isdigit(matrix[i + 1][j - 1]) && matrix[i + 1][j - 1] != '.')) 
    {
        return true;
    }

    // Check the bottom-right diagonal neighbor
    if (i < matrix.size() - 1 && j < matrix[i].size() - 1 && (!isdigit(matrix[i + 1][j + 1]) && matrix[i + 1][j + 1] != '.'))
    {
        return true;
    }

    return false;
}

void day3AProcess()
{
    const char* filePath = "data/Day3/DataA.txt";
    std::ifstream inputFile(filePath);

    // Check if the file is successfully opened
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }

    std::vector<std::string> lines;

    // Read lines from the file and store them in the vector
    std::string line;
    while (std::getline(inputFile, line))
    {
        lines.push_back(line);
    }

    // Determine the dimensions of the matrix
    size_t numRows = lines.size();
    size_t maxLineLength = 0;
    for (const auto& l : lines) {
        if (l.length() > maxLineLength) {
            maxLineLength = l.length();
        }
    }
    size_t numCols = maxLineLength;

    // Fill the matrix with characters
    std::vector<std::vector<char>> matrix(numRows, std::vector<char>(numCols, ' '));

    for (size_t i = 0; i < numRows; ++i) {
        const std::string& currentLine = lines[i];
        for (size_t j = 0; j < currentLine.length(); ++j) {
            matrix[i][j] = currentLine[j];
        }
    }

    int count = 0;
    string s;
    bool hasFoundComponent = false;
    bool isCheckingWord = false;

    // Print the matrix
    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            if (isdigit(matrix[i][j]))
            {
                s += matrix[i][j];
                isCheckingWord = true;
                if (!hasFoundComponent)
                {
                    hasFoundComponent = isConnectedIndex(matrix, i, j);
                }
            }

            else
            {
                if (isCheckingWord && hasFoundComponent)
                {
                    count += atoi(s.c_str());
                }
                s.clear();
                hasFoundComponent = false;
                isCheckingWord = false;
            }
        }

        if (isCheckingWord && hasFoundComponent)
        {
            count += atoi(s.c_str());
        }
        s.clear();
        hasFoundComponent = false;
        isCheckingWord = false;
    }

    cout << "Total found : " << count << endl;

    inputFile.close();
}

void day3BProcess()
{
    const char* filePath = "data/Day3/DataB.txt";
    std::ifstream inputFile(filePath);

    // Check if the file is successfully opened
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }

    std::vector<std::string> lines;

    // Read lines from the file and store them in the vector
    std::string line;
    while (std::getline(inputFile, line))
    {
        lines.push_back(line);
    }

    // Determine the dimensions of the matrix
    size_t numRows = lines.size();
    size_t maxLineLength = 0;
    for (const auto& l : lines) {
        if (l.length() > maxLineLength) {
            maxLineLength = l.length();
        }
    }
    size_t numCols = maxLineLength;

    // Fill the matrix with characters
    std::vector<std::vector<char>> matrix(numRows, std::vector<char>(numCols, ' '));

    for (size_t i = 0; i < numRows; ++i) {
        const std::string& currentLine = lines[i];
        for (size_t j = 0; j < currentLine.length(); ++j) {
            matrix[i][j] = currentLine[j];
        }
    }

    int count = 0;
    string s;
    bool hasFoundComponent = false;
    bool isCheckingWord = false;

    unordered_map<int, int> componentsFound;
    int gearI = 0;
    int gearJ = 0;

    // Print the matrix
    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            if (isdigit(matrix[i][j]))
            {
                s += matrix[i][j];
                isCheckingWord = true;
                if (!hasFoundComponent)
                {
                    hasFoundComponent = isConnectedGear(matrix, i, j, gearI, gearJ);
                }
            }

            else
            {
                if (isCheckingWord && hasFoundComponent)
                {
                    int currentGear = atoi(s.c_str());

                    auto it = componentsFound.find(gearI * numCols + gearJ);
                    if (it != componentsFound.cend())
                    {
                        int previousGear = it->second;
                        count += currentGear * previousGear;
                    }
                    else
                    {
                        componentsFound[gearI * numCols + gearJ] = currentGear;
                    }
                    
                }
                s.clear();
                hasFoundComponent = false;
                isCheckingWord = false;
            }
        }

        if (isCheckingWord && hasFoundComponent)
        {
            int currentGear = atoi(s.c_str());

            auto it = componentsFound.find(gearI * numCols + gearJ);
            if (it != componentsFound.cend())
            {
                int previousGear = it->second;
                count += currentGear * previousGear;
            }
            else
            {
                componentsFound[gearI * numCols + gearJ] = currentGear;
            }
        }
        s.clear();
        hasFoundComponent = false;
        isCheckingWord = false;
    }

    cout << "Total found : " << count << endl;

    inputFile.close();
}