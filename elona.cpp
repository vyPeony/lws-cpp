#include "elona.hpp"
#include <array>
#include <iostream>
#include <vector>
#include "random.hpp"


namespace
{

int64_t seed;



struct EncRef
{
    int id;
    int level;
    int rarity;
};

const std::vector<EncRef> encref_base{
    {1,  1, 3000},
    {2,  3, 7500},
    {3,  0, 4500},
    {6,  0, 4500},
    {7,  2, 900},
    {22, 1, 150},
    {23, 1, 400},
    {24, 2, 300},
    {25, 1, 400},
    {26, 1, 600},
    {27, 1, 600},
    {28, 2, 500},
    {32, 1, 250},
    {33, 3, 200},
    {34, 3, 250},
    {48, 1, 300},
    {56, 0, 30},
    {57, 2, 200},
    {58, 2, 200},
    {59, 0, 30},
    {61, 2, 150},
};


std::array<std::array<std::vector<std::pair<int, int>>, 5>, 2> enclist_table;
std::array<std::array<int, 5>, 2> enclist_sum;





std::string skillname(int id)
{
    switch (id)
    {
    case 10: return u8"筋力";
    case 11: return u8"耐久";
    case 12: return u8"器用";
    case 13: return u8"感覚";
    case 14: return u8"意思";
    case 15: return u8"習得";
    case 16: return u8"魔力";
    case 17: return u8"魅力";
    case 18: return u8"速度";
    case 19: return u8"運勢";
    case 50: return u8"火炎";
    case 51: return u8"冷気";
    case 52: return u8"電撃";
    case 53: return u8"暗黒";
    case 54: return u8"幻惑";
    case 55: return u8"毒";
    case 56: return u8"地獄";
    case 57: return u8"音";
    case 58: return u8"神経";
    case 59: return u8"混沌";
    case 60: return u8"魔法";
    case 150: return u8"読書";
    case 151: return u8"遺伝子学";
    case 152: return u8"戦術";
    case 153: return u8"重量挙げ";
    case 154: return u8"治癒";
    case 155: return u8"瞑想";
    case 156: return u8"交渉";
    case 157: return u8"隠密";
    case 158: return u8"鍵開け";
    case 159: return u8"探知";
    case 160: return u8"投資";
    case 161: return u8"解剖学";
    case 162: return u8"自然鑑定";
    case 163: return u8"採掘";
    case 164: return u8"魔力の限界";
    case 165: return u8"暗記";
    case 166: return u8"二刀流";
    case 167: return u8"両手持ち";
    case 168: return u8"盾";
    case 169: return u8"重装備";
    case 170: return u8"中装備";
    case 171: return u8"軽装備";
    case 172: return u8"詠唱";
    case 173: return u8"回避";
    case 174: return u8"魔道具";
    case 175: return u8"罠解体";
    case 176: return u8"大工";
    case 177: return u8"裁縫";
    case 178: return u8"錬金術";
    case 179: return u8"宝石細工";
    case 180: return u8"栽培";
    case 181: return u8"信仰";
    case 182: return u8"旅歩き";
    case 183: return u8"演奏";
    case 184: return u8"料理";
    case 185: return u8"釣り";
    case 186: return u8"心眼";
    case 187: return u8"見切り";
    case 188: return u8"魔力制御";
    case 189: return u8"射撃";
    default: return "";
    }
}


}






/*
This license is applied for inner exrand namespace and HSPexrand_rnd/HSPexrand_randomize.


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
namespace exrand
{


    /* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UMASK 0x80000000UL /* most significant w-r bits */
#define LMASK 0x7fffffffUL /* least significant r bits */
#define MIXBITS(u,v) ( ((u) & UMASK) | ((v) & LMASK) )
#define TWIST(u,v) ((MIXBITS(u,v) >> 1) ^ ((v)&1UL ? MATRIX_A : 0UL))

    unsigned long state[N]; /* the array for the state vector  */
    int left = 1;
    int initf = 0;
    unsigned long *next;

    //MT関連の内部関数
    //MTのソースコードからEXRandで使ってるとこだけ抜粋

    /* initializes mt[N] with a seed */
    void init_genrand(unsigned long s)
    {
        int j;
        state[0] = s & 0xffffffffUL;
        for (j = 1; j<N; j++) {
            state[j] = (1812433253UL * (state[j - 1] ^ (state[j - 1] >> 30)) + j);
            /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
            /* In the previous versions, MSBs of the seed affect   */
            /* only MSBs of the array state[].                     */
            /* 2002/01/09 modified by Makoto Matsumoto             */
            state[j] &= 0xffffffffUL;  /* for >32 bit machines */
        }
        left = 1; initf = 1;
    }

    void next_state()
    {
        unsigned long *p = state;
        int j;

        /* if init_genrand() has not been called, */
        /* a default initial seed is used         */
        if (initf == 0) init_genrand(5489UL);

        left = N;
        next = state;

        for (j = N - M + 1; --j; p++)
            *p = p[M] ^ TWIST(p[0], p[1]);

        for (j = M; --j; p++)
            *p = p[M - N] ^ TWIST(p[0], p[1]);

        *p = p[M - N] ^ TWIST(p[0], state[0]);
    }

    /* generates a random number on [0,1)-real-interval */
    double genrand_real2()
    {
        unsigned long y;

        if (--left == 0) next_state();
        y = *next++;

        /* Tempering */
        y ^= (y >> 11);
        y ^= (y << 7) & 0x9d2c5680UL;
        y ^= (y << 15) & 0xefc60000UL;
        y ^= (y >> 18);

        return (double)y * (1.0 / 4294967296.0);
        /* divided by 2^32 */
    }

}



namespace hsprnd
{



int rnd(int max)
{
    seed = seed * 214013 + 2531011;
    return static_cast<int>((seed >> 16) & 32767) % max;
}


void randomize(int new_seed)
{
    seed = new_seed;
}



int exrand_rnd(int max)
{
    return static_cast<int>(exrand::genrand_real2() * max);
}



void exrand_randomize(int new_seed)
{
    exrand::init_genrand(static_cast<uint64_t>(new_seed));
}



void init_enclist_table()
{
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 5; ++j)
        {
            int sum{};
            for (const auto& ref : encref_base)
            {
                if (ref.id == 34 && i == 1)
                {
                    continue;
                }
                if (ref.level > static_cast<int>(j))
                {
                    continue;
                }
                sum += ref.rarity;
                enclist_table[i][j].push_back(std::make_pair(ref.id, sum));
            }
            enclist_sum[i][j] = sum;
        }
    }
}











int randomenc(int e_level, WeaponType weapon_type)
{
    const auto& enclist = enclist_table[static_cast<size_t>(weapon_type)][e_level];
    const auto sum = enclist_sum[static_cast<size_t>(weapon_type)][e_level];

    const auto p = exrand_rnd(sum);
    for (const auto& e : enclist)
    {
        if (p < e.second)
        {
            return e.first;
        }
    }
    return 0;
}



int randomencp(bool has_ehekatl_feat, int hammer_enhancement)
{
    if (hammer_enhancement)
    {
        return 0;
        // return rndex2(rndex2((500 + has_ehekatl_feat * 50) * std::min(1 + hammer_enhancement * hammer_enhancement, 50)) + 1) + 1;
    }
    else
    {
        return rnd(rnd(500 + has_ehekatl_feat * 50) + 1) + 1;
    }
}



std::string get_e_desc(int e_type, int e_power)
{
    switch (e_type / 10000)
    {
    case 1:
        return skillname(e_type % 10000) + u8"を" + std::to_string(e_power / 50 + 1) + "上げる";
    case 2:
        return skillname(e_type % 10000) + u8"への耐性を授ける";
    case 3:
        return skillname(e_type % 10000) + u8"の技能を" + std::to_string(e_power / 50 + 1) + "上げる";
    case 6:
        return skillname(e_type % 10000) + u8"を維持する";
    case 7:
        return skillname(e_type % 10000) + u8"属性の追加ダメージを与える";
    default:
        break;
    }
    switch (e_type)
    {
    case 21: return u8"ランダムなテレポートを引き起こす";
    case 22: return u8"テレポートを妨害する";
    case 23: return u8"盲目を無効にする";
    case 24: return u8"麻痺を無効にする";
    case 25: return u8"混乱を無効にする";
    case 26: return u8"恐怖を無効にする";
    case 27: return u8"睡眠を無効にする";
    case 28: return u8"毒を無効にする";
    case 29: return u8"速度を上げ、ワールドマップでの移動時間を短くする";
    case 30: return u8"エーテルの風からあなたを保護する";
    case 31: return u8"雷雨と雪による足止めを無効にする";
    case 32: return u8"あなたを浮遊させる";
    case 33: return u8"あなたを変異から保護する";
    case 34: return u8"魔法の威力を高める";
    case 35: return u8"透明な存在を見ることを可能にする";
    case 36: return u8"攻撃対象からスタミナを吸収する";
    case 37: return u8"全てを終結させる";
    case 38: return u8"攻撃対象からマナを吸収する";
    case 39: return u8"完全貫通攻撃発動の機会を増やす";
    case 40: return u8"稀に時を止める";
    case 41: return u8"アイテムを盗まれなくする";
    case 42: return u8"腐ったものを難なく消化させる";
    case 43: return u8"呪いの言葉から保護する";
    case 44: return u8"クリティカルヒットの機会を増やす";
    case 45: return u8"使用者の生き血を吸う";
    case 46: return u8"あなたの成長を妨げる";
    case 47: return u8"魔物を呼び寄せる";
    case 48: return u8"異物の体内への侵入を防ぐ";
    case 49: return u8"演奏報酬の品質を上げる";
    case 50: return u8"追加打撃の機会を増やす";
    case 51: return u8"追加射撃の機会を増やす";
    case 52: return u8"被る物理ダメージを軽減する";
    case 53: return u8"被るダメージを稀に無効にする";
    case 54: return u8"攻撃された時、相手に切り傷のダメージを与える";
    case 55: return u8"出血を抑える";
    case 56: return u8"神が発する電波をキャッチする";
    case 57: return u8"竜族に対して強力な威力を発揮する";
    case 58: return u8"不死者に対して強力な威力を発揮する";
    case 59: return u8"他者の信仰を明らかにする";
    case 60: return u8"深い音色で聴衆を酔わす";
    case 61: return u8"神に対して強力な威力を発揮する";
    default: return "Unknown: " + std::to_string(e_type);
    }
}



int randomele()
{
    const std::array<int, 11> rarity{{
        1,
        1,
        1,
        2,
        2,
        3,
        4,
        3,
        3,
        4,
        5,
    }};

    auto e = rnd(11);
    const auto r = rarity[e];
    for (int i = 0; i < r - 1; ++i)
    {
        const auto e2 = rnd(11);
        const auto r2 = rarity[e2];
        if (r2 < r)
        {
            if (rnd(2) == 0)
            {
                e = e2;
            }
        }
    }

    return e + 50;
}



int encadd(int e_type)
{
    if (e_type >= 20 || e_type == 0)
    {
        return e_type;
    }

    switch (e_type)
    {
    case 1: return 10000 + rnd(10) + 10;
    case 2: return 20000 + randomele();
    case 3: return 30000 + rnd(40) + 150;
    case 6: return 60000 + rnd(10) + 10;
    case 7: return 70000 + randomele();
    default: return 0;
    }
}


}
