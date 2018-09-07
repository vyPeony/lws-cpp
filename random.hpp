#pragma once



namespace gentleman
{
namespace random
{


class Generator
{
public:
    Generator(int32_t seed)
        : seed(static_cast<int64_t>(seed))
    {
    }


    int32_t operator()(int32_t max)
    {
        seed = seed * 214013 + 2531011;
        return static_cast<int>((seed >> 16) & 32767) % max;
    }


private:
    int64_t seed;
};


}
}
