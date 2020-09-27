/* Requirement is to create HTML writer 
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

class htmlElement 
{
    private: 
    std::string dName {};
    std::string dText {};
    std::vector<std::unique_ptr<htmlElement>> dChildElementsList;
    const size_t dIndetSize = 2;

    htmlElement(std::string xName, std::string xText)
    :dName(std::move(xName)), 
     dText(std::move(xText))
     {

     }

    public:
    std::string str(int xIndent = 0) const
    {
        std::ostringstream oss;
        std::string s(dIndetSize*xIndent, ' ');
        oss << s <<"<"<<dName<<">"<<std::endl;
        if (!dText.empty()) 
            oss << std::string(dIndetSize*xIndent+1, ' ') <<dText<<std::endl;
        
        for (const auto &e : dChildElementsList)
            oss << e->str(xIndent+1);
        
        oss <<"</"<<dName<<">"<<std::endl;
        return oss.str();
    } 
};

int main ()
{

}