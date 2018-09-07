#include <iomanip>
#include <iostream>

#include "hsprnd.hpp"





// ブシフレイム
// 0x83 0x75
// 0x83 0x56
// 0x83 0x74
// 0x83 0x8C
// 0x83 0x43
// 0x83 0x80
// 感覚を6上げる
int main()
{
    using namespace hsprnd;

    randomize(10501);
    const auto bushi_flame = random_title();

    size_t i{};
    for (const auto c : bushi_flame)
    {
        const auto n = static_cast<int>(static_cast<uint8_t>(c));
        std::cout << "0x" << std::setbase(16) << n << std::setbase(10);
        if (i != bushi_flame.size())
        {
            std::cout << " ";
        }
        ++i;
    }
    std::cout << std::endl;

    const auto weapon_type = WeaponType::melee;
    const auto level = 1;
    for (int i = 0; i < 50; ++i)
    {
        const auto seed = 50501 + level * 10 + i;
        randomize(seed);
        exrand_randomize(seed);
        const auto e_level = randomenclv(4);
        const auto e_type = randomenc(e_level, weapon_type);
        const auto has_ehekatl_feat = true;
        const auto hammer_enhancement = 0;
        const auto e_power = randomencp(has_ehekatl_feat, hammer_enhancement);
        const auto e_type2 = encadd(e_type);
        std::cout << get_e_desc(e_type2, e_power) << "," << e_power << std::endl;
        break;
    }

    return 0;
}
