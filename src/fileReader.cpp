#include <iostream>
#include <string>
#include <fstream>
#include "fileReader.h"

std::string fileReader(const std::string& filePath){

    std::ifstream stream(filePath);
    std::string line;
    std::string source = "";

    while (getline(stream, line)){
        source += line + "\n";
    }


    return source;
}
