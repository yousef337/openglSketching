#pragma once

#include <iostream>
#include <string>
#include <fstream>

static std::string fileReader(const std::string& filePath){

    std::ifstream stream(filePath);
    std::string line;
    std::string source = "";

    while (getline(stream, line)){
        source += line + "\n";
    }


    return source;
}
