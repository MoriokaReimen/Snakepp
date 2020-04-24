#pragma once

#include <Eigen/Dense>
#include <vector>

class NeuralNet
{
  int iNodes_;
  int hNodes_;
  int oNodes_;
  int hLayers_;
  std::vector<Eigen::MatrixXd> weights_;
public:
NeuralNet(int input, int hidden, int output, int hiddenLayers);
void mutate(const float& mr);
NeuralNet cross_over(const NeuralNet& other);
std::vector<float> output(std::vector<float> inputsArr);

};
