#include <functional>
using namespace std;

struct SingletonTester
{
  template <typename T>
  bool is_singleton(function<T*()> factory)
  {
      T *lInst1 = factory();
      T *lInst2 = factory();
      return lInst1 == lInst2;
  }
};

int main () 
{

}