#pragma once
#include "../Renderer.h"
#include "../Camera.h"

class Program {

public:
    virtual void main(const Renderer renderer, const Camera camera){};
    virtual void imGui(){};
    virtual ~Program(){};
};
