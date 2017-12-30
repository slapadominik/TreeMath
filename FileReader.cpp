//
// Created by Ululula on 28.12.2017.
//

#include "FileReader.h"
#include <fstream>
#include <iostream>

std::vector<std::string> FileReader::readFromFile(std::string sFileName) {
    std::vector<std::string> lines;
    std::string line;
    std::ifstream myfile(sFileName);
    if (myfile.is_open())
    {
        while (std::getline(myfile,line) )
        {
            lines.push_back(line);
        }
        myfile.close();
    }
    else {
        std::cout << "Unable to open file";
    }
    return lines;
}

std::vector<double> FileReader::retriveXValuesFromVector(std::vector<std::string> text) {
    std::vector<double> x_values;
    for (int i=0; i<text.size();i++){
        x_values.push_back(std::stod(split(text.at(i),';').at(0)));
    }
    return x_values;
}

std::vector<std::string> FileReader::split(std::string sStringToSplit, char chRegnex) {
    std::string accumulator = "";
    std::vector<std::string> splited;
    for (int i = 0; i < sStringToSplit.size(); ++i)
        if (sStringToSplit[i] != chRegnex)
            accumulator += sStringToSplit[i];
        else if (accumulator.size() != 0) {
            splited.push_back(accumulator);
            accumulator = "";
        }
    splited.push_back(accumulator);
    return splited;
}

std::vector<double> FileReader::retriveYValuesFromVector(std::vector<std::string> text) {
    std::vector<double> y_values;
    for (int i=0; i<text.size();i++){
        y_values.push_back(std::stod(split(text.at(i),';').at(1)));
    }
    return y_values;
}

std::vector<double> FileReader::retriveFXYValuesFromVector(std::vector<std::string> text) {
    std::vector<double> fxy_values;
    for (int i=0; i<text.size();i++){
        fxy_values.push_back(std::stod(split(text.at(i),';').at(2)));
    }
    return fxy_values;
}

std::vector<double> FileReader::splitTextIntoDoubleVector(std::vector<std::string> text) {
    std::vector<double> file_text_converted;
    std::vector<std::string> splitted;
    for (int i=0; i<text.size();i++){
        splitted = split(text.at(i),';');
        file_text_converted.push_back(std::stod(splitted.at(0)));
        file_text_converted.push_back(std::stod(splitted.at(1)));
        file_text_converted.push_back(std::stod(splitted.at(2)));
    }
    return file_text_converted;
}
