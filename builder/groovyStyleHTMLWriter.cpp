// Needed c++17

#include<iostream>
#include<string>
#include<vector>
#include<initializer_list>
#include<ostream>

class HTMLTag
{
    private: 
    std::string dName;
    std::string dText;

    std::vector<std::pair<std::string, std::string>> dAtrribute;
    std::vector<HTMLTag> dChildTags;
    public:

    HTMLTag(std::string xName, std::string xText)
    :dName(std::move(xName)), 
     dText(std::move(xText))
     {

     }
    
    HTMLTag(std::string xName, std::vector<HTMLTag> xChildTags)
    :dName(std::move(xName)), 
     dChildTags(std::move(xChildTags))
    {

    }

    void AddAttribute(const std::string& xName, const std::string& xValue)
    {
        //dAtrribute.emplace_back(std::pair<std::string, std::string>{xName, xValue});
        dAtrribute.emplace_back(std::pair{xName, xValue});
    }

    friend std::ostream & operator <<(std::ostream &os, const HTMLTag &obj)
    {
        os << "<"<<obj.dName;
        for (const auto &att : obj.dAtrribute)
            os << R"foo(")foo" << att.first << R"foo("=")foo"<<att.second<< R"foo(")foo";

        if (obj.dChildTags.empty() && obj.dText.empty())
        {
            os << "/>"<<std::endl;
        }
        else 
        {
            os <<">"<<::std::endl; // close angular braces
            if (!obj.dText.empty())
                os <<obj.dText<<std::endl;
            for (const auto &child : obj.dChildTags)
                os << child;
            
            os <<"</" <<obj.dName<<">"<<std::endl;
        }
    }
    
};


class P : public HTMLTag
{
    public: 
    P(std::string xText)
    : HTMLTag("p", xText)
    {

    }

    P(std::initializer_list<HTMLTag> xList)
    :HTMLTag("p", xList)
    {

    }
};

class IMG : public HTMLTag
{
    public: 
    IMG(std::string URL)
    :HTMLTag("img", "")
    {
        AddAttribute("src", URL);
    }
};
int main () 
{
    std::cout<< 
    P {
        P{"test"},
        IMG 
        {
            {"hdl"}
        }
    };

}