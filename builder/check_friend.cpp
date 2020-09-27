#include<iostream>
#include<memory>

class A 
{
    friend class B;
    friend function std::make_unique;
    private: 
    A() = default;
};

class B 
{
    private: 
    std::unique_ptr<A> dPtr;
    public: 
    B() 
    {
        dPtr = std::make_unique<A>();
        //dPtr = std::unique_ptr<A>(new A());
    }
};

int main () 
{
}