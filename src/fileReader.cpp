#include <iostream>
#include <string>
#include <fstream>
#include "fileReader.h"

static std::string fileReader(const std::string& filePath){

    std::ifstream stream(filePath);
    std::string line;
    std::string source = "";

    while (getline(stream, line)){
        source += line + "\n";
    }


    return source;
}
