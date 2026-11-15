#include "ObjectManager.h"
#include <cstdint>
#include <random>
#include <string>
#include <unordered_set>

namespace IEngine
{
    std::size_t ObjectManager::GenerateGUID()
    {
        static std::random_device rd;
        static std::mt19937_64 generator(rd());

        return generator();
    }
}