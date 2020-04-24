#include <Matrix.hpp>
#include <random>
#include <cmath>
#include <algorithm>

static float get_random(const float &min, const float &max);

Eigen::MatrixXd mutate(const Eigen::MatrixXd &mat, const float &mutation_ratio)
{
    Eigen::MatrixXd ret(mat);

    for (int i = 0; i < mat.rows(); i++)
    {
        for (int j = 0; j < mat.cols(); j++)
        {
            float elem = ret(i, j) + get_random(-mutation_ratio, mutation_ratio);
            ret(i, j) = std::min(std::max(elem, -1.f), 1.f);
        }
    }

    return mat;
}

Eigen::MatrixXd crossover(const Eigen::MatrixXd &lhs, const Eigen::MatrixXd &rhs)
{
    Eigen::MatrixXd child(lhs);

    for (int i = 0; i < lhs.rows(); i++)
    {
        for (int j = 0; j < lhs.cols(); j++)
        {
            int choice = std::rand();
            if(choice % 2 == 0)
            {
                child(i, j) = rhs(i, j);
            }
        }
    }

    return child;
}

static float get_random(const float &min, const float &max)
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(min, max);

    return dis(e);
}