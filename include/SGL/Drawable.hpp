#pragma once

#include "SGL/SGLdecl.hpp"

namespace sgl
{
    class Drawable
    {
    public:
        virtual ~Drawable() = 0;
        virtual void draw() const = 0;
    };
}
