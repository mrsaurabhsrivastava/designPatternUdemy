// Filter class , filter design pattern

#include<iostream>
#include<vector>
#include<string>
enum class eColor
{
    RED,
    GREEN,
    YELLOW
};

enum class eSize
{
    LARGE,
    MEDIUM,
    SMALL
};

class product 
{
    public:
    std::string dName;
    eColor dColor;
    eSize dSize;
        product(std::string xName,
                eColor xColor,
                eSize xSize)
            : dName(xName),
              dColor(xColor),
              dSize(xSize)
        {
        }
};

template <typename T>
class andFilterCreteria;

template <typename T>
class filterCreteria 
{
    public: 
    virtual bool is_matched(const T &xItem) const = 0;
    andFilterCreteria<T> operator&& (filterCreteria<T> &x)
    {
        return andFilterCreteria<T>(this, &x);
    }

};

template <typename T> 
class filterCls 
{
    public:
    virtual std::vector<T> filter(const std::vector<T> &xItemList, 
                          const filterCreteria<T> &xCreteria) const = 0;
};

template <typename T>
class matchFilterCls : public filterCls<T> 
{
    public:
    std::vector<T> filter(const std::vector<T> &xItemList, 
                          const filterCreteria<T> &xCreteria) const override
    {
        std::vector<T> lResult;
        for (auto &v:xItemList)
        {
            if (xCreteria.is_matched(v))
                lResult.push_back(v);
        }
        return lResult;
    }
};

class colorFilterCreteria : public filterCreteria<product> 
{
    eColor dColor;
    public: 
    colorFilterCreteria(eColor xColor) : dColor(xColor){}
    bool is_matched(const product &xItem) const override
    {
        if (xItem.dColor == dColor)
            return true;
        return false;
    }
};

class sizeFilterCretaria : public filterCreteria<product> 
{
    eSize dSize;
    public: 
    sizeFilterCretaria(eSize xSize): dSize(xSize) {}
    bool is_matched(const product &xItem) const override
    {
        if (xItem.dSize == dSize)
            return true;
        return false;
    }
};

template <typename T>
class andFilterCreteria : public filterCreteria<T> 
{
    filterCreteria<T> *dF1;
    filterCreteria<T> *dF2;
    public: 
    andFilterCreteria(filterCreteria<T> *x1, filterCreteria<T> *x2)
    :dF1(x1),
     dF2(x2)
    {

    }

    bool is_matched(const product &xItem) const override
    {
        if (dF1->is_matched(xItem) && dF2->is_matched(xItem)) 
            return true;
        return false;
    }
};

int main ()
{
    product p1{"Mango", eColor::YELLOW, eSize::MEDIUM};
    product p2{"RawMango", eColor::GREEN, eSize::SMALL};
    product p3{"Watermelon", eColor::GREEN, eSize::LARGE};
    product p4{"Cherry", eColor::RED, eSize::SMALL};

    std::vector<product> lProducts;
    lProducts.push_back(p1);
    lProducts.push_back(p2);
    lProducts.push_back(p3);
    lProducts.push_back(p4);

    colorFilterCreteria colorFilter(eColor::GREEN);
    matchFilterCls<product> matchFilter;
    std::vector<product> lResult = matchFilter.filter(lProducts, colorFilter);

    sizeFilterCretaria sizeFilterCr(eSize::SMALL);
    matchFilterCls<product> sizeFilter;
    lResult = sizeFilter.filter(lProducts, sizeFilterCr);

    auto f = colorFilter && sizeFilterCr;
    //andFilterCreteria<product> f(&colorFilter, &sizeFilterCr);
    lResult = sizeFilter.filter(lProducts, f);

    for (const auto &v : lResult)
        std::cout<<v.dName<<std::endl;
}
