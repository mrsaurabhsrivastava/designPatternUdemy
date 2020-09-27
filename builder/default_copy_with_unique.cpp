#include<iostream>
#include<memory>

class A 
{
    std::unique_ptr<int> dPtr;
    public: 
    A() = default;
};

int main () 
{
    A obj;
    A obj1 = obj;
}
