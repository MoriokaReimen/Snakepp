#include <Food.hpp>
#include <random>

static int get_random(const int &min, const int &max);

Food::Food(const int& field_width, const int& field_height)
: x_(get_random(0, field_width)),
  y_(get_random(0, field_height))
{
}

static int get_random(const int &min, const int &max)
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(min, max);

    return dis(e);
}