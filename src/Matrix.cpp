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

std::vector<float> to_array(const Eigen::MatrixXd& in)
{
    std::vector<float> ret;
    for(int i = 0; i < in.rows(); i++)
    for(int j = 0; j < in.cols(); j++)
    {
        ret.push_back(in(i, j));

    }
    return ret;
}

Eigen::MatrixXd from_array(const std::vector<float>& in)
{
    Eigen::MatrixXd ret(in.size(), 1);
    for(int i = 0; i < in.size(); i++)
    {
        ret(i, 0) = in[i];
    }

    return ret;
}

Eigen::MatrixXd randomize(const Eigen::MatrixXd& in)
{
    Eigen::MatrixXd ret(in);
    for(int i = 0; i < in.rows(); i++)
    for(int j = 0; j < in.cols(); j++)
    {
        ret(i, j) = get_random(-1.0, 1.0);
    }

    return ret;
}

Eigen::MatrixXd add_bias(const Eigen::MatrixXd& in)
{
    Eigen::MatrixXd ret(in.rows() + 1, 1);

    for(int i = 0; i < in.rows(); i++)
    {
        ret(i, 0) = in(i, 0); 
    }
    ret(in.rows(), 0) = 1.f;

    return ret;
}

Eigen::MatrixXd activate(const Eigen::MatrixXd& in)
{
    Eigen::MatrixXd ret(in);
    for(int i = 0; i < in.rows(); i++)
    for(int j = 0; j < in.cols(); j++)
    {
        ret(i, j) = std::max(static_cast<float>(ret(i, j)), 0.f);
    }

    return ret;
}

static float get_random(const float &min, const float &max)
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(min, max);

    return dis(e);
}