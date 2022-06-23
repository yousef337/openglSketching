#include "Texture.h"

Texture::Texture(const unsigned int offset){
   glGenTextures(1, &textureId);
}

unsigned int Texture::getOffset() const {
        return offset;
}


unsigned int Texture::getTexturId() const {
        return textureId;
}

std::string Texture::getType() const {
        return type;
}
