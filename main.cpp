#include <iomanip>
#include <iostream>

#include "hsprnd.hpp"




// MODIFY HERE.

// [begin, end)
constexpr auto begin = 0;
constexpr auto end = 1000 * 1000 * 100;
constexpr auto seaching_type = 34;
constexpr auto power_threshold = 545;






using namespace hsprnd;

std::string get_weapon_title(int weapon_seed)
{
    randomize(weapon_seed);
    return random_title();
}



void show_weapon_title(int weapon_seed)
{
    std::cout << "title = [";
    const auto title = get_weapon_title(weapon_seed);
    for (const auto c : title)
    {
        const auto n = static_cast<int>(static_cast<uint8_t>(c));
        std::cout << n << ",";
    }
    std::cout << "].pack('c*').force_encoding('Shift_JIS').encode('UTF-8')" << std::endl;
}



void process_one_title(int page, int n)
{
    const auto has_ehekatl_feat = true;
    const auto hammer_enhancement = 0;
    const auto weapon_type = WeaponType::melee;
    const auto level = 1;

    const auto weapon_seed = 10500 + page * 17 + n;
    show_weapon_title(weapon_seed);
    randomize(weapon_seed + 40000);
    const auto blood = 4 + rnd(12);

    for (int i = 0; i < 50; ++i)
    {
        const auto seed = weapon_seed + 40000 + level * 10 + i;
        randomize(seed);
        exrand_randomize(seed);
        const auto e_level = randomenclv(4);
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
            std::cout << "desc = '" << get_e_desc(e_type2, e_power) << "," << e_power << "'" <<std::endl;
            break;
        }
    }

    std::cout << "puts \"" << weapon_seed + 40000 << "," << (page + 1) << ",#{title},#{desc}," << blood << "\"" << std::endl;
}



template <int type, int threshold>
bool match_enchantment(int page, int n)
{
    const auto has_ehekatl_feat = true;
    const auto hammer_enhancement = 0;
    const auto weapon_type = WeaponType::melee;
    const auto level = 1;

    const auto weapon_seed = 10500 + page * 17 + n;

    for (int i = 0; i < 50; ++i)
    {
        const auto seed = weapon_seed + 40000 + level * 10 + i;
        randomize(seed);
        exrand_randomize(seed);
        const auto e_level = randomenclv(4);
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
            return e_type2 == type && e_power >= threshold;
        }
    }

    return false;
}


// int main()
// {
//     std::cout << "puts 'Id,Name,Enchantment,Power'" << std::endl;
//
//     const auto page_max = 1;
//     for (int page = 0; page < page_max; ++page)
//     {
//         for (int i = 0; i < 17; ++i)
//         {
//             if (i % 17 == 0)
//             {
//                 std::cout << "puts '(選択不可)'" << std::endl;
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
    std::cout << "puts 'Id,Page,Name,Enchantment,Power'" << std::endl;

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
