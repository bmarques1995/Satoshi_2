#ifndef EXAMPLE_LAYER_HPP
#define EXAMPLE_LAYER_HPP

#include <Satoshi.hpp>

class ExampleLayer : public Satoshi::Layer
{
public:
    ExampleLayer();
    ~ExampleLayer();

    void OnUpdate() override;
    void OnEvent(Satoshi::Event& e) override;
private:

};


#endif //EXAMPLE_LAYER_HPP
