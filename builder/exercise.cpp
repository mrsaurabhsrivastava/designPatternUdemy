#include<iostream>
#include<ostream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

class Code 
{
    friend class CodeBuilder;
    string class_name;
    std::vector<std::pair<string, string>> filed_list; 
    public: 
    Code(string xClassName) : class_name(std::move(xClassName)) {};

    string str() const 
    {
        ostringstream oss;
        oss<<"class "<<class_name<<std::endl;
        oss<<"{"<<std::endl;
        for (const auto &v:filed_list)
            oss<<'\t'<<v.second<<" "<<v.first<<";"<<std::endl;
        oss<<"};"<<std::endl;
        return oss.str();
    } 
};

class CodeBuilder
{
    Code root;

public:
  CodeBuilder(const string& class_name)
  :root{class_name}
  {
  }

  CodeBuilder& add_field(const string& name, const string& type)
  {
      root.filed_list.emplace_back(make_pair(name, type));
      return *this;
  }

  friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
  {
      os<<obj.root.str();
      return os;
  }
};


int main () 
{
    auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
    cout<<cb;
}