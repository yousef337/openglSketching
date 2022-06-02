#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Intermediate/Image.cpp"

class Texture{

private:
    unsigned int textureId;
    unsigned int offset;
    Image imgTexture;

    void setUpTexture(){
        glBindTexture(GL_TEXTURE_2D, textureId);
        glActiveTexture(GL_TEXTURE0 + offset);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

    }


    void updateImage(){
        glBindTexture(GL_TEXTURE_2D, textureId);

        if (imgTexture.getImgData()){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgTexture.getWidth(), imgTexture.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, imgTexture.getImgData());
            imgTexture.freeData();
        }

        glBindTexture(GL_TEXTURE_2D, 0);

    }

public:
    Texture(const Image img, unsigned int offset = 0): imgTexture(img){
        glGenTextures(1, &textureId);
        this->offset = offset;
        this->imgTexture = img;
        setUpTexture();
        updateImage();
    }


    unsigned int getOffset(){
        return offset;
    }

    unsigned int getTexturId(){
        return textureId;
    }

};
