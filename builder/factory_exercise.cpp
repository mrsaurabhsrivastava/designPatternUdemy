#include<iostream>
#include <string>
using namespace std;

struct Person
{
  string name;
  int id;
  explicit Person(string xName, int xId)
  :name (std::move(xName)), 
   id(xId) 
  {

  }
};

class PersonFactory
{
    static int sId;
public:
  Person create_person(const string& name)
  {
      return Person{name, sId++};
  }
};

int PersonFactory::sId = 0;

int main () 
{

}