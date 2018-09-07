#include <iomanip>
#include <iostream>

#include "elona.hpp"




// MODIFY HERE.

// [begin, end)
constexpr auto begin = 0;
constexpr auto end = 1 * 10000 * 10000;
constexpr auto seaching_type = 34;
constexpr auto power_threshold = 545;

constexpr auto has_ehekatl_feat = true;
constexpr auto hammer_enhancement = 0;
constexpr auto weapon_type = WeaponType::melee;
constexpr auto level = 1;





using namespace hsprnd;

std::string get_weapon_title(int weapon_seed)
{
    randomize(weapon_seed);
    return random_title();
}



void process_one_title(int page, int n)
{
    const auto weapon_seed = 50500 + page * 17 + n;
    const auto weapon_title = get_weapon_title(weapon_seed - 40000);
    randomize(weapon_seed);
    const auto blood = 4 + rnd(12);

    std::string desc;

    for (int i = 0; i < 50; ++i)
    {
        const auto seed = weapon_seed + level * 10 + i;
        randomize(seed);
        exrand_randomize(seed);
        const auto e_level = rnd(5);
        const auto e_type = randomenc(e_level, weapon_type);
        const auto e_power = randomencp(has_ehekatl_feat, hammer_enhancement);
        const auto e_type2 = encadd(e_type);
        if (e_type2 != 0)
        {
            if (e_type2 == 34)
            {
                if (rnd(3))
                {
                    continue;
                }
            }
            desc = get_e_desc(e_type2, e_power);
            break;
        }
    }

    std::cout << weapon_seed << "," << (page + 1) << "," << weapon_title << "," << desc << "," << blood << std::endl;
}



template <int type, int threshold>
bool match_enchantment(int page, int n)
{
    const auto weapon_seed = 50500 + page * 17 + n;

    for (int i = 0; i < 50; ++i)
    {
        const auto seed = weapon_seed + level * 10 + i;
        randomize(seed);
        exrand_randomize(seed);
        const auto e_level = rnd(5);
        const auto e_type = randomenc(e_level, weapon_type);
        if (type >= 20 && e_type != type)
        {
            return false;
        }
        const auto e_power = randomencp(has_ehekatl_feat, hammer_enhancement);
        const auto e_type2 = encadd(e_type);
        if (e_type2 != 0)
        {
            if (e_type2 == 34)
            {
                if (rnd(3))
                {
                    continue;
                }
            }
            return e_type2 == type && e_power >= threshold;
        }
    }

    return false;
}


// int main()
// {
//     std::cout << "Id,Name,Enchantment,Power" << std::endl;
//
//     const auto page_max = 1;
//     for (int page = 0; page < page_max; ++page)
//     {
//         for (int i = 0; i < 17; ++i)
//         {
//             if (i % 17 == 0)
//             {
//                 std::cout << "(選択不可)" << std::endl;
//                 continue;
//             }
//             process_one_title(page, i);
//         }
//     }
//
//     return 0;
// }
int main()
{
    init_enclist_table();

    std::cout << "Id,Name,Enchantment,Power" << std::endl;



    // for (int i = 0; i < 8; ++i)
    // {
    //     int n = 1047492392 - i - 10500 - 40000 - 13*10;
    //     int p = n / 17;
    //     int j = n % 17;
    //     if (j == 0)
    //         continue;
    //
    //     process_one_title(p, j);
    // }

    // int begin = 0;
    // int end = 100;

    const auto page_begin = begin / 17;
    const auto page_end = end / 17;

    for (int p = page_begin; p < page_end; ++p)
    {
        for (int i = 1; i < 17; ++i)
        {
            const auto match = match_enchantment<seaching_type, power_threshold>(p, i);
            if (match)
            {
                process_one_title(p, i);
            }
        }
    }

    return 0;
}
