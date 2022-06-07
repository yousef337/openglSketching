#include "Texture.h"


    Texture::Texture(const Image img, const unsigned int offset): imgTexture(img){
        glGenTextures(1, &textureId);
        this->offset = offset;
        this->imgTexture = img;
        setUpTexture();
        updateImage();
    }

    Texture::Texture() : imgTexture(""){
        this->offset = 0;
    }


    void Texture::setUpTexture(){
        glBindTexture(GL_TEXTURE_2D, textureId);
        glActiveTexture(GL_TEXTURE0 + offset);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

    }


    void Texture::updateImage(){
        glBindTexture(GL_TEXTURE_2D, textureId);

        if (imgTexture.getImgData()){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgTexture.getWidth(), imgTexture.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgTexture.getImgData());
            imgTexture.freeData();
        }

        glBindTexture(GL_TEXTURE_2D, 0);

    }

    unsigned int Texture::getOffset() const{
        return offset;
    }

    unsigned int Texture::getTexturId() const {
        return textureId;
    }
