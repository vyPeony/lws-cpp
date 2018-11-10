#include <iomanip>
#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <locale>
#include <Windows.h>
#include "getopt.h"

#include "elona.hpp"
#include "randomtitlegenerator.hpp"




// MODIFY HERE.

// [begin, end)
auto begin = 0;
auto end = 1 * 10000 * 10000;
auto seaching_type = 34;
auto power_threshold = 545;

auto has_ehekatl_feat = true;
auto hammer_enhancement = 0;
auto weapon_type = WeaponType::melee;
auto level = 1;

struct option longoptions[] = {
	{ "Begin",      required_argument, NULL, 'b' },
	{ "End",        required_argument, NULL, 'e' },
	{ "SearchType", required_argument, NULL, 's' },
	{ "Threshold",  required_argument, NULL, 't' },
	{ "Ehekatl",    no_argument,       NULL, 'u' },
	{ "Hammer",     required_argument, NULL, 'h' },
	{ "WeaponType", required_argument, NULL, 'w' },
	{ "Level",      required_argument, NULL, 'l' },
	{0, 0, 0, 0},
};

using namespace std;
using namespace hsprnd;

gentleman::elona::RandomTitleGenerator title_generator;
std::mutex cout_mutex;

void process_one_title(gentleman::random::Generator& gen, int weapon_seed)
{
    const auto weapon_title = title_generator.generate(weapon_seed - 40000);
    gen.randomize(weapon_seed);
    const auto blood = 4 + gen.rnd(12);

    int type{};
    int power{};
    for (int i = 0; i < 50; ++i)
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



bool match_enchantment(gentleman::random::Generator& gen, int weapon_seed, int type, int threshold)
{
    for (int i = 0; i < 50; ++i)
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
    return (std::max)(std::thread::hardware_concurrency(), 1U);
}



void search(gentleman::random::Generator& gen, int page)
{
    for (int i = 1; i < 17; ++i)
    {
        const auto weapon_seed = 50500 + page * 17 + i;
        const auto match = match_enchantment(gen, weapon_seed, seaching_type, power_threshold);
        if (match)
        {
            process_one_title(gen, weapon_seed);
        }
    }
}



int main(int argc, char* argv[])
{
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1024);
	int opt = -1;
	int longindex = -1;
	while ((opt = getopt_long(argc, argv, "b:e:s:t:uh:w:l::", longoptions, &longindex)) != -1) {
		switch (opt) {
		case 'b':
			::begin = atoi(optarg);
			break;
		case 'e':
			::end = atoi(optarg);
			break;
		case 's':
			::seaching_type = atoi(optarg);
			break;
		case 't':
			::power_threshold = atoi(optarg);
			break;
		case 'u':
			break;
		case 'h':
			::hammer_enhancement = atoi(optarg);
			break;
		case 'w':
			weapon_type = static_cast<WeaponType>(atoi(optarg));
			break;
		case 'l':
			::level = atoi(optarg);
			break;
		default:
			std::cout << "Usage: ...." << std::endl;
			break;
		}
	}

    title_generator.initialize();

    init_enclist_table();

    std::cout << "Id,Page,Name,Enc,Power,Blood" << std::endl;

    const auto page_begin = ::begin / 17;
    const auto page_end = ::end / 17;

    const auto num_threads = get_num_threads();
    const auto page_per_thread = (std::max)(1, (page_end - page_begin) / static_cast<int>(num_threads));

    std::vector<std::thread> threads;

    int b = page_begin;
    for (; b < page_end - page_per_thread; b += page_per_thread)
    {
        threads.emplace_back([=] {
            gentleman::random::Generator gen;
            for (int page = b; page < b + page_per_thread; ++page)
            {
                search(gen, page);
            }
        });
    }
    threads.emplace_back([=] {
        gentleman::random::Generator gen;
        for (int page = b; page < page_end; ++page)
        {
            search(gen, page);
        }
    });

    for (auto&& thread : threads)
    {
        thread.join();
    }

    return 0;
}
