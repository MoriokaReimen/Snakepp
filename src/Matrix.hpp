#pragma once
#include <Eigen/Dense>
#include <vector>

Eigen::MatrixXd mutate(const Eigen::MatrixXd& mat, const float& mutation_ratio);
Eigen::MatrixXd crossover(const Eigen::MatrixXd& lhs, const Eigen::MatrixXd& rhs);
std::vector<float> to_array(const Eigen::MatrixXd& in);
Eigen::MatrixXd from_array(const std::vector<float>& in);
Eigen::MatrixXd randomize(const Eigen::MatrixXd& in);
Eigen::MatrixXd add_bias(const Eigen::MatrixXd& in);
Eigen::MatrixXd activate(const Eigen::MatrixXd& in);
