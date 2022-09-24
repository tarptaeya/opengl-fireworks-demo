#pragma once

#include "camera.h"

class XObject
{
public:
    virtual ~XObject() { }
    virtual void update(float delta_time) = 0;
    virtual void render(Camera *camera) = 0;
};