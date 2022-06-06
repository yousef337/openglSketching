#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image/stb_image.h"

    Image::Image(const char* filePath){
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    }

    unsigned char* Image::getImgData(){
        return data;
    }

    void Image::freeData(){
        stbi_image_free(data);
    }

    int Image::getWidth(){
        return width;
    }

    int Image::getHeight(){
        return height;
    }

    int Image::getNRChannels(){
        return nrChannels;
    }

