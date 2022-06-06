#pragma once

class VAO {

private:
    unsigned int vaoId;
    unsigned int indexCount;

public:
    VAO();

    void setIndexCount(unsigned int count);

    unsigned int getVaoId();

    unsigned int getIndexCount();

};

