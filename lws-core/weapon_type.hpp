#pragma once


enum class WeaponType
{
    melee,
    ranged,
};


inline int to_category(WeaponType type)
{
    return type == WeaponType::melee ? 10000 : 24000;
}
