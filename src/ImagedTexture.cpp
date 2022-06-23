#include "ImagedTexture.h"


    ImagedTexture::ImagedTexture(const Image img, const unsigned int offset): Texture(offset), imgTexture(img){
        this->imgTexture = img;
        setUpTexture();
        updateImage();
    }

    ImagedTexture::ImagedTexture() : Texture(0), imgTexture(""){
    }


    void ImagedTexture::setUpTexture() {
        glBindTexture(GL_TEXTURE_2D, getTexturId());
        glActiveTexture(GL_TEXTURE0 + getOffset());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

    }


    void ImagedTexture::updateImage(){
        glBindTexture(GL_TEXTURE_2D, getTexturId());

        if (imgTexture.getImgData()){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgTexture.getWidth(), imgTexture.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgTexture.getImgData());
            imgTexture.freeData();
        }

        glBindTexture(GL_TEXTURE_2D, 0);

    }
