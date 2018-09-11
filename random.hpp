#pragma once

#include <cstdint>
#include <random>


/*
This class is based on a HSP's DLL, EXRand.


0〜32kじゃ何もできん!! 拡張乱数 EXRand
(c)2002 D.N.A. Softwares
このDLLはフリーソフトウェアです。


乱数生成部は松本眞氏と西村拓士氏による
Mersenne Twisterを使用しています。a


Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

3. The names of its contributors may not be used to endorse or promote
products derived from this software without specific prior written
permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/



namespace gentleman
{
namespace random
{



class Generator
{
public:
    Generator(std::random_device::result_type seed = 0)
    {
        randomize(seed);
    }


    template <typename Integer>
    int32_t rnd(Integer max)
    {
        return rndex(max);
    }


    template <typename Integer>
    int32_t rndex(Integer max)
    {
        return std::uniform_int_distribution<Integer>{Integer{0}, std::max(Integer{0}, max - 1)}(engine);
    }


    void randomize(int32_t new_seed)
    {
        engine.seed(new_seed);
    }



private:
    std::mt19937 engine;
};



}
}
