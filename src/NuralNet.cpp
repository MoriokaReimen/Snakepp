#include <NeuralNet.hpp>
#include <Matrix.hpp>

NeuralNet::NeuralNet(int input, int hidden, int output, int hiddenLayers)
    : iNodes_(input), hNodes_(hidden),
      oNodes_(output), hLayers_(hiddenLayers),
      weights_(hLayers_, ::randomize(Eigen::MatrixXd(hNodes_, iNodes_ + 1)))
{
    weights_.push_back(::randomize(Eigen::MatrixXd(oNodes_, iNodes_ + 1)));
}

void NeuralNet::mutate(const float& mr)
{
    for (auto& weight : weights_)
    {
        weight = ::mutate(weight, mr);
    }
}

NeuralNet NeuralNet::cross_over(const NeuralNet& other)
{
    NeuralNet child(*this);

    for(int i = 0; i < weights_.size(); i++)
    {
        child.weights_[i] = ::crossover(weights_[i], other.weights_[i]);
    }

    return child;
}

std::vector<float> NeuralNet::output(std::vector<float> inputsArr)
{
    Eigen::MatrixXd inputs = ::from_array(inputsArr);
     
    Eigen::MatrixXd curr_bias = add_bias(inputs);
     
    for(int i=0; i< hLayers_; i++) {
        Eigen::MatrixXd hidden_ip = weights_[i] * curr_bias; 
        Eigen::MatrixXd hidden_op = activate(hidden_ip);
        curr_bias = add_bias(hidden_op);
    }
     
    Eigen::MatrixXd output_ip = weights_[weights_.size() - 1] * curr_bias;
    Eigen::MatrixXd output = activate(output_ip);
     
     return to_array(output);
}
