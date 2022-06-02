#pragma once
#include "../external/stb_image/stb_image.cpp"

class Image{
private:
    int width, height, nrChannels;
    unsigned char* data;
public:

    Image(const char* filePath){
        data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    }

    unsigned char* getImgData(){
        return data;
    }

    void freeData(){
        stbi_image_free(data);
    }

    int getWidth(){
        return width;
    }

    int getHeight(){
        return height;
    }

    int getNRChannels(){
        return nrChannels;
    }
};
