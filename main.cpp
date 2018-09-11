#include <iomanip>
#include <iostream>
#include <thread>
#include <mutex>

#include "elona.hpp"
#include "randomtitlegenerator.hpp"




// MODIFY HERE.

// [begin, end)
constexpr auto begin = 0;
constexpr auto end = 5000 * 17;
constexpr auto seaching_type = 34;
constexpr auto power_threshold = 400;

constexpr auto has_ehekatl_feat = true;
constexpr auto hammer_enhancement = 0;
constexpr auto weapon_type = WeaponType::melee;
constexpr auto level = 1;





using namespace hsprnd;


gentleman::elona::RandomTitleGenerator title_generator;




std::mutex cout_mutex;

void process_one_title(gentleman::random::Generator& gen, int weapon_seed, int level)
{
    const auto weapon_title = title_generator.generate(weapon_seed - 40000);
    gen.randomize(weapon_seed);
    const auto blood = 4 + gen.rnd(12);

    int type{};
    int power{};
    for (int i = 0; i < 3; ++i)
    {
        const auto seed = weapon_seed + level * 10 + i;
        gen.randomize(seed);
        const auto e_level = gen.rnd(5);
        const auto e_type = randomenc(gen, e_level, weapon_type);
        const auto e_power = randomencp(gen, has_ehekatl_feat, hammer_enhancement);
        const auto e_type2 = encadd(gen, e_type);
        if (e_type2 != 0)
        {
            if (e_type2 == 34)
            {
                if (gen.rnd(3))
                {
                    continue;
                }
            }
            type = e_type2;
            power = e_power;
            break;
        }
    }

    std::lock_guard<std::mutex> guard{cout_mutex};
    std::cout << weapon_seed << "," << ((weapon_seed - 50500) / 17 + 1) << "," << weapon_title << "," << get_e_desc(type, power) << "," << power << "," << blood << std::endl;
}



bool match_enchantment(gentleman::random::Generator& gen, int weapon_seed, int type, int threshold, int level)
{
    for (int i = 0; i < 3; ++i)
    {
        const auto seed = weapon_seed + level * 10 + i;
        gen.randomize(seed);
        const auto e_level = gen.rnd(5);
        const auto e_type = randomenc(gen, e_level, weapon_type);
        const auto e_power = randomencp(gen, has_ehekatl_feat, hammer_enhancement);
        const auto e_type2 = encadd(gen, e_type);
        if (e_type2 != 0)
        {
            if (e_type2 == 34)
            {
                if (gen.rnd(3))
                {
                    continue;
                }
            }
            return e_type2 == type && e_power >= threshold;
        }
    }

    return false;
}



uint32_t get_num_threads()
{
    return std::max(std::thread::hardware_concurrency(), 1U);
}



void search(gentleman::random::Generator& gen, int page)
{
    for (int i = 1; i < 17; ++i)
    {
        const auto weapon_seed = 50500 + page * 17 + i;
        const auto match = match_enchantment(gen, weapon_seed, seaching_type, power_threshold, level);
        if (match)
        {
            process_one_title(gen, weapon_seed, level);
        }
    }
}



int main()
{
    title_generator.initialize();

    init_enclist_table();

    std::cout << "Id,Page,Name,Enc,Power,Blood" << std::endl;

    gentleman::random::Generator gen;
    for (int level = 1; level < 15; ++level)
    {
        std::cout << level << "→" << (level+1) << std::endl;
        const auto id_base = 126651 + (level-1) * -10 - 2;
        for (int i = 0; i < 3; ++i)
        {
            const auto id = id_base + i;
            if ((id - 50500) % 17 == 0)
            {
                continue;
            }
            process_one_title(gen, id, level);
        }
        std::cout << std::endl;
    }

    // const auto page_begin = begin / 17;
    // const auto page_end = end / 17;
    //
    // const auto num_threads = get_num_threads();
    // const auto page_per_thread = std::max(1, (page_end - page_begin) / static_cast<int>(num_threads));
    //
    // std::vector<std::thread> threads;
    //
    // int b = page_begin;
    // for (; b < page_end - page_per_thread; b += page_per_thread)
    // {
    //     threads.emplace_back([=] {
    //         gentleman::random::Generator gen;
    //         for (int page = b; page < b + page_per_thread; ++page)
    //         {
    //             search(gen, page);
    //         }
    //     });
    // }
    // threads.emplace_back([=] {
    //     gentleman::random::Generator gen;
    //     for (int page = b; page < page_end; ++page)
    //     {
    //         search(gen, page);
    //     }
    // });
    //
    // for (auto&& thread : threads)
    // {
    //     thread.join();
    // }

    return 0;
}
