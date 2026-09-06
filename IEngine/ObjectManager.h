#pragma once

#include <cstddef>

namespace IEngine
{
    class ObjectManager
    {
    public:
        static std::size_t GenerateGUID();
    };
}