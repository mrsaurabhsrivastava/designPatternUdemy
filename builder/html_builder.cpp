/* Requirement is to create HTML writer 
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

class htmlBuilder;
class htmlElement 
{
    friend class htmlBuilder;
    private:  
    std::string dName {};
    std::string dText {};
    std::vector<htmlElement*> dChildElementsList;
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

    /* static htmlBuilder create(const std::string& xName)
    {
        //return htmlBuilder(xName);
    }
 */
};

class htmlBuilder
{
    private: 
    std::unique_ptr<htmlElement> dRoot;

    public:
    htmlBuilder(std::string xRootName)
    {
        dRoot = std::unique_ptr<htmlElement>(new htmlElement (xRootName, ""));
    } 

    htmlBuilder(htmlBuilder &obj)
    {
        dRoot = std::unique_ptr<htmlElement>(obj.dRoot.get());
    }
    htmlBuilder & addChild(const std::string &xName,const std::string &xText)
    {
        dRoot->dChildElementsList.emplace_back(new htmlElement{xName, xText});
        return *this;
    }

    operator htmlElement() 
    {
        return *(dRoot.get());
    }

};

int main ()
{
    htmlBuilder f("root");
    htmlElement f1 = f.addChild("p", "hwllo").addChild("q", "ok");
    std::cout<<f1.str()<<std::endl;
}