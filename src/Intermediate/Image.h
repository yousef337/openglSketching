#pragma once

class Image{

private:
    int width, height, nrChannels;
    unsigned char* data;
public:

    Image(const char* filePath);

    unsigned char* getImgData();

    void freeData();

    int getWidth();

    int getHeight();

    int getNRChannels();
};

