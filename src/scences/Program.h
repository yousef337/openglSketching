#pragma once
#include "../Renderer.h"

class Program {

public:
    virtual void main(Renderer renderer){};
    virtual void imGui(){};
    virtual ~Program(){};
};
