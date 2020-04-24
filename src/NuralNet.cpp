#include <NeuralNet.hpp>
#include <Matrix.hpp>

NeuralNet::NeuralNet(int input, int hidden, int output, int hiddenLayers)
    : iNodes_(input), hNodes_(hidden),
      oNodes_(output), hLayers_(hiddenLayers),
      weights_(hLayers_, Eigen::MatrixXd::Random(hNodes_, iNodes_ + 1))
{
    weights_.push_back(Eigen::MatrixXd::Random(oNodes_, iNodes_ + 1));
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
#if 0
std::vector<float> NeuralNet::output(std::vector<float> inputsArr)
{
     Matrix inputs = weights[0].singleColumnMatrixFromArray(inputsArr);
     
     Matrix curr_bias = inputs.addBias();
     
     for(int i=0; i<hLayers; i++) {
        Matrix hidden_ip = weights[i].dot(curr_bias); 
        Matrix hidden_op = hidden_ip.activate();
        curr_bias = hidden_op.addBias();
     }
     
     Matrix output_ip = weights[weights.length-1].dot(curr_bias);
     Matrix output = output_ip.activate();
     
     return output.toArray();
  }
#endif