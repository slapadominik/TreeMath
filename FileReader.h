//
// Created by Ululula on 28.12.2017.
//

#ifndef TREEMATH_FILEREADER_H
#define TREEMATH_FILEREADER_H

#include <string>
#include <vector>

class FileReader {
public:
    static std::vector<std::string> readFromFile(std::string sFileName);
    static std::vector<double> splitTextIntoDoubleVector(std::vector<std::string>text);
    static std::vector<double> retriveXValuesFromVector(std::vector<std::string> text);
    static std::vector<double> retriveYValuesFromVector(std::vector<std::string> text);
    static std::vector<double> retriveFXYValuesFromVector(std::vector<std::string> text);

private:
    static std::vector<std::string> split(std::string sStringToSplit, char chRegnex);
};


#endif //TREEMATH_FILEREADER_H
