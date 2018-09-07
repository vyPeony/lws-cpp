#pragma once

#include <string>
#include "weapon_type.hpp"


namespace hsprnd
{


// Random number generator in HSP's standard library.
int rnd(int max);
void randomize(int new_seed);

// Random number generator in exrand.dll.
int exrand_rnd(int max);
void exrand_randomize(int new_seed);


std::string generate_title(int seed);


int randomenc(int e_level, WeaponType weapon_type);
int randomencp(bool has_ehekatl_feat, int hammer_enhancement);

std::string get_e_desc(int e_type, int e_power);

int encadd(int e_type);

void init_enclist_table();


}
