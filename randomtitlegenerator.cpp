#include "randomtitlegenerator.hpp"
#include <fstream>
#include "random.hpp"



namespace
{



size_t byte_count(uint8_t c)
{
    if (c <= 0x7F)
        return 1;
    else if (c >= 0xc2 && c <= 0xdf)
        return 2;
    else if (c >= 0xe0 && c <= 0xef)
        return 3;
    else if (c >= 0xf0 && c <= 0xf7)
        return 4;
    else if (c >= 0xf8 && c <= 0xfb)
        return 5;
    else if (c >= 0xfc && c <= 0xfd)
        return 6;
    else
        return 1;
}



size_t byte_count(char c)
{
    return byte_count(static_cast<uint8_t>(c));
}



size_t calc_width(const std::string& str)
{
    int ret = 0;
    for (size_t i = 0; i < str.size();)
    {
        const auto byte = byte_count(str[i]);
        ret += byte == 1 ? 1 : 2;
        i += byte;
    }
    return ret;
}



std::vector<std::string> split_record(const std::string& line)
{
    std::vector<std::string> fields{15};

    size_t pos{};
    for (size_t i = 0; i < fields.size(); ++i)
    {
        const auto comma_pos = line.find(',', pos);
        if (comma_pos == std::string::npos)
        {
            fields[i] = line.substr(pos);
            break;
        }
        fields[i] = line.substr(pos, comma_pos - pos);
        pos = comma_pos + 1;
    }

    return fields;
}



std::vector<std::vector<std::string>> load_word_table(const std::string& filename)
{
    std::vector<std::vector<std::string>> word_table;

    std::ifstream in{filename, std::ios::binary};
    if (!in)
    {
        throw std::runtime_error{"Failed to load ndata.csv."};
    }
    std::string buf;
    while (std::getline(in, buf))
    {
        word_table.push_back(split_record(buf));
    }

    return word_table;
}



}



namespace gentleman
{
namespace elona
{



void RandomTitleGenerator::initialize()
{
    word_table_cp932 = load_word_table("ndata-utf8.csv");
    word_table_utf8 = load_word_table("ndata-utf8.csv");
}



std::string RandomTitleGenerator::generate(int seed) const
{
    gentleman::random::Generator gen{seed};

    // "具"
    const auto category_concrete = u8"具";

    // "万能"
    const auto category_general = u8"万能";

    // "の"
    const auto no = u8"の";

    // "・オブ・"
    const auto of = u8"・オブ・";

    // "・"
    const auto sep = u8"・";

    int p_1;
    int p_2;
    int p_4;
    std::string randn2_;
    std::string randn2_u;
    std::string randn2_1;

retry:
    while (true)
    {
        p_2 = gen.rnd(static_cast<int>(word_table_cp932.size()));
        p_1 = gen.rnd(14);
        if (!word_table_cp932[p_2][p_1].empty())
        {
            break;
        }
    }
    if (word_table_cp932[p_2][14] == category_concrete)
    {
        goto retry;
    }
    randn2_ = word_table_cp932[p_2][p_1];
    randn2_u = word_table_utf8[p_2][p_1];
    randn2_1 = word_table_cp932[p_2][14];
    do
    {
        if (p_1 == 10 || p_1 == 11)
        {
            if (gen.rnd(5) == 0)
            {
                p_1 = 0;
                if (gen.rnd(2) == 0)
                {
                    randn2_ += no;
                    randn2_u += "の";
                }
                break;
            }
            switch (gen.rnd(5))
            {
            case 0:
                randn2_ += of;
                randn2_u += "・オブ・";
                break;
            case 1:
                return "ザ・" + randn2_u;
            case 2:
                randn2_ += sep;
                randn2_u += "・";
                break;
            default:
                break;
            }
        }
        if (p_1 == 0 || p_1 == 1)
        {
            randn2_ += no;
            randn2_u += "の";
            if (gen.rnd(10) == 0)
            {
                p_1 = 10;
            }
        }
    } while (false);

    bool ok{};
    for (int i = 0; i < 100; ++i)
    {
        p_4 = gen.rnd(static_cast<int>(word_table_cp932.size()));
        if (p_4 == p_2)
        {
            continue;
        }
        if (word_table_cp932[p_4][14] == randn2_1)
        {
            if (word_table_cp932[p_4][14] != category_general && randn2_1 != category_general)
            {
                continue;
            }
        }
        if (p_1 < 10)
        {
            p_1 = gen.rnd(2);
        }
        else
        {
            p_1 = 10 + gen.rnd(2);
        }
        if (word_table_cp932[p_4][p_1].empty())
        {
            continue;
        }
        ok = true;
        break;
    }
    if (!ok)
    {
        goto retry;
    }

    randn2_ += word_table_cp932[p_4][p_1];
    randn2_u += word_table_utf8[p_4][p_1];
    if (calc_width(randn2_) >= 28)
    {
        goto retry;
    }

    return randn2_u;
}



}
}
