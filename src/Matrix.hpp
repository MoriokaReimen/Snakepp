#pragma once
#include <Eigen/Dense>

Eigen::MatrixXd mutate(const Eigen::MatrixXd& mat, const float& mutation_ratio);
Eigen::MatrixXd crossover(const Eigen::MatrixXd& lhs, const Eigen::MatrixXd& rhs);
