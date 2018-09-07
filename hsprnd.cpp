#include "hsprnd.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <vector>


namespace
{

int64_t seed;


int limit(int x, int min, int max)
{
    return std::min(std::max(x, min), max);
}



bool encflt(int category, int filter)
{
    switch (filter)
    {
    case 1: return 30000 <= category && category < 50000;
    case 2: return 12000 <= category && category < 24000;
    case 3: return (12000 <= category && category < 24000) || category == 10000;
    default: return category == filter;
    }
}


const std::vector<std::array<int, 5>> encref{
    {{0, 0, 0, 0, 0}},
    {{1, 120, 3000, 0}},
    {{3, 150, 7500, 0}},
    {{0, 120, 4500, 0}},
    {{0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0}},
    {{0, 120, 4500, 0}},
    {{2, 120, 900, 10000, 24000}},
    {{99, 300, 15000, 0}},
    {{1, 120, 50000, 25000}},
    {{0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0}},
    {{-1, 50, 75, 0}},
    {{1, 150, 150, 0}},
    {{1, 120, 400, 0}},
    {{2, 120, 300, 0}},
    {{1, 120, 400, 0}},
    {{1, 120, 600, 0}},
    {{1, 120, 600, 0}},
    {{2, 120, 500, 0}},
    {{3, 200, 25, 18000}},
    {{3, 200, 25, 20000}},
    {{2, 200, 40, 32000}},
    {{1, 130, 250, 0}},
    {{3, 160, 200, 0}},
    {{3, 170, 250, 10000}},
    {{2, 170, 100, 12000, 32000}},
    {{99, 450, 1000, 10000, 24000}},
    {{99, 100, 1000, 10000, 24000}},
    {{99, 450, 1000, 10000, 24000}},
    {{99, 500, 500, 10000, 22000}},
    {{99, 550, 500, 10000, 24000}},
    {{99, 300, 1500, 0}},
    {{99, 300, 2000, 0}},
    {{99, 150, 2000, 0}},
    {{99, 300, 10000, 10000, 34000}},
    {{-1, 50, 100, 0}},
    {{-1, 50, 100, 0}},
    {{-1, 50, 50, 0}},
    {{1, 120, 300, 0}},
    {{100, 120, 300, 60000}},
    {{3, 180, 150, 32000, 34000}},
    {{3, 180, 150, 32000, 34000}},
    {{1, 140, 750, 14000}},
    {{2, 160, 500, 14000}},
    {{3, 180, 250, 14000, 16000}},
    {{3, 130, 40, 19000, 34000}},
    {{0, 200, 30, 0}},
    {{2, 170, 200, 10000, 24000}},
    {{2, 170, 200, 10000, 24000}},
    {{0, 200, 30, 0}},
    {{100, 120, 300, 60000}},
    {{2, 170, 150, 10000, 24000}},
};


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
    default:
        assert(false);
        break;
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



std::vector<std::string> csvsort(const std::string& line, char separator)
{
    std::vector<std::string> ret{15};

    size_t pos{};
    for (size_t i = 0; i < ret.size(); ++i)
    {
        const auto separator_pos = line.find(separator, pos);
        if (separator_pos == std::string::npos)
        {
            ret[i] = line.substr(pos);
            break;
        }
        ret[i] = line.substr(pos, separator_pos - pos);
        pos = separator_pos + 1;
    }

    return ret;
}



std::vector<std::vector<std::string>> load_rnlist()
{
    std::vector<std::vector<std::string>> rnlist;

    std::ifstream in{"ndata.csv", std::ios::binary};
    if (!in)
    {
        throw std::runtime_error{"Failed to load ndata.csv."};
    }
    std::string buf;
    while (std::getline(in, buf, '\r')) // Read until CR.
    {
        in.get(); // Skip leading LF.
        rnlist.push_back(csvsort(buf, ','));
    }

    return rnlist;
}



std::string random_title()
{
    static const auto rnlist = load_rnlist();

    // "具"
    const auto category_concrete = std::string{
        static_cast<char>(0x8B),
        static_cast<char>(0xEF),
    };

    // "万能"
    const auto category_general = std::string{
        static_cast<char>(0x96),
        static_cast<char>(0x9C),
        static_cast<char>(0x94),
        static_cast<char>(0x5C),
    };

    // "の"
    const auto no = std::string{
        static_cast<char>(0x82),
        static_cast<char>(0xCC),
    };

    // "ザ・"
    const auto the = std::string{
        static_cast<char>(0x83),
        static_cast<char>(0x55),
        static_cast<char>(0x81),
        static_cast<char>(0x45),
    };

    // "・オブ・"
    const auto of = std::string{
        static_cast<char>(0x81),
        static_cast<char>(0x45),
        static_cast<char>(0x83),
        static_cast<char>(0x49),
        static_cast<char>(0x83),
        static_cast<char>(0x75),
        static_cast<char>(0x81),
        static_cast<char>(0x45),
    };

    // "・"
    const auto sep = std::string{
        static_cast<char>(0x81),
        static_cast<char>(0x45),
    };

    int p_;
    int p_1;
    int p_2;
    int p_3;
    int p_4;
    std::string s_;
    std::string randn2_;
    std::string randn2_1;
    int rtval_;

retry:
    while (true)
    {
        p_2 = rnd(static_cast<int>(rnlist.size()));
        p_1 = rnd(14);
        if (!rnlist[p_2][p_1].empty())
        {
            break;
        }
    }
    if (rnlist[p_2][14] == category_concrete)
    {
        goto retry;
    }
    randn2_ = rnlist[p_2][p_1];
    randn2_1 = rnlist[p_2][14];
    rtval_ = -1;
    do
    {
        if (p_1 == 10 || p_1 == 11)
        {
            if (rnd(5) == 0)
            {
                p_1 = 0;
                p_3 = rnd(2);
                if (p_3 == 0)
                {
                    randn2_ += no;
                }
                break;
            }
            p_ = rnd(5);
            if (p_ == 0)
            {
                randn2_ += of;
            }
            if (p_ == 1)
            {
                randn2_ = the + randn2_;
                rtval_ = 1;
                break;
            }
            if (p_ == 2)
            {
                randn2_ += sep;
            }
        }
        if (p_1 == 0 || p_1 == 1)
        {
            randn2_ += no;
            p_3 = rnd(10);
            if (p_3 == 0)
            {
                p_1 = 10;
            }
        }
    } while (false);
    if (rtval_ == 1)
    {
        s_ = randn2_;
        goto the_end;
    }
    rtval_ = -1;
    for (int i = 0; i < 100; ++i)
    {
        p_4 = rnd(static_cast<int>(rnlist.size()));
        if (p_4 == p_2)
        {
            continue;
        }
        if (rnlist[p_4][14] == randn2_1)
        {
            if (rnlist[p_4][14] != category_general && randn2_1 != category_general)
            {
                continue;
            }
        }
        if (p_1 < 10)
        {
            p_1 = rnd(2);
        }
        else
        {
            p_1 = 10 + rnd(2);
        }
        if (rnlist[p_4][p_1].empty())
        {
            continue;
        }
        rtval_ = 1;
        break;
    }
    if (rtval_ == -1)
    {
        goto retry;
    }
    randn2_ += rnlist[p_4][p_1];
    s_ = randn2_;
    if (s_.size() >= 28)
    {
        goto retry;
    }

the_end:
    return s_;
}




int randomenclv(int base_level)
{
    return rnd(limit(base_level, 0, 4) + 1);
}



int randomenc(int e_level, WeaponType weapon_type)
{
    const auto category = to_category(weapon_type);

    int sum_{};
    std::vector<std::pair<int, int>> enclist;

    for (size_t i = 0; i < encref.size(); ++i)
    {
        if (encref[i][0] > e_level)
        {
            continue;
        }
        if (e_level >= 0 && encref[i][0] < 0)
        {
            continue;
        }
        if (encref[i][3] != 0)
        {
            if (!encflt(category, encref[i][3]))
            {
                if (encref[i][4] == 0)
                {
                    continue;
                }
                else if (!encflt(category, encref[i][4]))
                {
                    continue;
                }
            }
        }
        sum_ += encref[i][2];
        enclist.push_back(std::make_pair(static_cast<int>(i), sum_));
    }
    if (enclist.empty())
    {
        return 0;
    }

    const auto p = exrand_rnd(sum_);
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
    const std::vector<int> rarity = {
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
    };

    auto e = rnd(61 - 50) + 50;
    const auto r = rarity.at(e - 50);
    for (int i = 0; i < r - 1; ++i)
    {
        const auto e2 = rnd(61 - 50) + 50;
        const auto r2 = rarity.at(e2 - 50);
        if (r2 < r)
        {
            if (rnd(2) == 0)
            {
                e = e2;
            }
        }
    }

    return e;
}



int encadd(int e_type)
{
    if (e_type >= 20 || e_type == 0)
    {
        return e_type;
    }

    switch (e_type)
    {
    case 1:
        e_type = rnd(20 - 10) + 10;
        e_type += 1 * 10000;
        break;
    case 2:
        e_type = randomele();
        e_type += 2 * 10000;
        break;
    case 3:
        e_type = rnd(190 - 150) + 150;
        e_type += 3 * 10000;
        break;
    case 6:
        e_type = rnd(20 - 10) + 10;
        e_type += 6 * 10000;
        break;
    case 7:
        e_type = randomele();
        e_type += 7 * 10000;
        break;
    default:
        assert(false);
        break;
    }

    return e_type;
}


}
