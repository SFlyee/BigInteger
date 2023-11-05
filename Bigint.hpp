#include <vector>
#include <string>
class Bint;
Bint to_Bint(std::string num);
class Bint
{
public:
    Bint()=default;
    Bint(long long num){
        *this=to_Bint(std::to_string(num));
    }
    bool operator<(Bint b){
        if(sign<b.sign)
            return false;
        else if(sign>b.sign)
            return true;
        else if(sign==1)
            return abs_bigger(*this,b);
        else 
            return abs_less(*this,b); 
    }
    bool operator==(Bint b){
        if(sign!=b.sign)
            return false;
        return abs_equal(*this,b);
    }
    bool operator>(Bint b){
        return !(*this>b||*this==b);
    }
    Bint operator=(long long num){
        *this=to_Bint(std::to_string(num));
    }
    Bint operator+(Bint b){
        return add(*this,b);
    }
    Bint operator-(Bint b){
        return sub(*this,b);
    }
    Bint operator*(Bint b){
        return mul(*this,b);
    }
    Bint operator/(long long b){
        return div(*this,b);
    }
    friend std::ostream& operator<<(std::ostream& t,Bint c);
    friend std::istream& operator<<(std::istream& t,Bint c);
    friend void jinwei(Bint &a);
    friend void jiewei(Bint &a);
    friend void remove_0(Bint &a);
    friend Bint operator+(long long num,Bint a);
    friend Bint operator+(Bint a,long long num);
    friend Bint to_Bint(std::string num);
private:
    friend bool abs_less (Bint a, Bint b);
    friend bool abs_equal (Bint a, Bint b);
    friend bool abs_bigger (Bint a, Bint b);
    friend Bint add(Bint a, Bint b);//加
    friend Bint sub(Bint a, Bint b);//减
    friend Bint mul(Bint a, Bint b);//乘
    friend Bint div(Bint a, long long b);//除
    std::vector<int> data;
    bool sign = 0; // 0表示正数
};
Bint operator+(long long num,Bint a){
    return a+to_Bint(std::to_string(num));
}
Bint operator+(Bint a,long long num){
    return num+a;
}
std::ostream& operator<<(std::ostream& t,Bint c){
    if (c.sign == 1)
        t << "-";
    for (auto it = c.data.rbegin(); it != c.data.rend(); it++)
    {
        t << *it;
    }
    return t;
}
std::istream& operator>>(std::istream& t,Bint c){
    std::string s; 
    t>>s;
    c=to_Bint(s);
    return t;
}
bool abs_less (Bint a, Bint b)
{ // 这里比较的是绝对值
    if (a.data.size() > b.data.size())
        return false;
    else if (a.data.size() < b.data.size())
        return true;
    for (int i = a.data.size() - 1; i >= 0; i--)
    {
        if (a.data[i] < b.data[i])
            return true;
        else if (a.data[i] > b.data[i])
            return false;
    }
    return false; // 相等
}
bool abs_equal (Bint a, Bint b)
{
    if (a.data.size() != b.data.size())
        return false;
    for (int i = a.data.size() - 1; i >= 0; i--)
    {
        if (a.data[i] != b.data[i])
            return false;
    }
    return true; // 相等
}
bool abs_bigger (Bint a, Bint b)
{
    return !(abs_less(a, b) || abs_equal (a, b));
}
void remove_0(Bint &c)
{
    while (c.data.size() > 1 && c.data.back() == 0)
        c.data.pop_back();
}
void jinwei(Bint &a)
{
    int i = 0;
    for (; i < a.data.size(); i++)
    {
        if (i == a.data.size() - 1 && a.data[i] > 9)
            a.data.push_back(0);
        while (a.data[i] > 9)
        {
            a.data[i + 1] += a.data[i] / 10;
            a.data[i] %= 10;
        }
    }
}
void jiewei(Bint &a)
{
    for (int i = 0; i < a.data.size(); i++)
    {
        while (a.data[i] < 0)
        {
            a.data[i + 1]--;
            a.data[i] += 10;
        }
    }
}
Bint to_Bint(std::string num)
{
    Bint a;
    for (auto it = num.rbegin(); it != num.rend(); it++)
    {
        if (*it != '-')
            a.data.push_back(*it - '0');
        else
            a.sign = 1;
    }
    remove_0(a);
    return a;
}

Bint add(Bint a, Bint b)
{
    Bint c;
    if (a.sign == 0 && b.sign == 1)
    {
        c = b;
        c.sign = 0;
        return sub(a, c);
    }
    else if (a.sign == 1 && b.sign == 0)
    {
        c = a;
        c.sign = 0;
        return sub(b, c);
    }
    Bint &bnum = a.data.size() > b.data.size() ? a : b;
    Bint &mnum = b.data.size() < a.data.size() ? b : a;
    c.sign = a.sign;
    for (int i = 0; i < bnum.data.size(); i++)
    {
        if (i < mnum.data.size())
        {
            c.data.push_back(bnum.data[i] + mnum.data[i]);
        }
        else
            c.data.push_back(bnum.data[i]);
    }
    jinwei(c);
    remove_0(c);
    if(abs_equal(c,to_Bint("0")))
        c.sign=0;
    return c;
}

Bint sub(Bint a, Bint b)
{
    Bint c;
    if (a.sign != b.sign)
        return add(a, b);
    b.sign = !b.sign;
    Bint &bnum = abs_bigger(a,b) ? a : b;
    Bint &mnum = abs_less(b,a) ? b : a;
    c.sign = bnum.sign;
    for (int i = 0; i < bnum.data.size(); i++)
    {
        if (i < mnum.data.size())
        {
            c.data.push_back(bnum.data[i] - mnum.data[i]);
        }
        else
            c.data.push_back(bnum.data[i]);
    }
    jiewei(c);
    remove_0(c);
    if(abs_equal(c,to_Bint("0")))
        c.sign=0;
    return c;
}
Bint mul(Bint a, Bint b)
{
    Bint c;
    c.sign = a.sign | b.sign;
    Bint &bnum = a.data.size() > b.data.size() ? a : b;
    Bint &mnum = b.data.size() < a.data.size() ? b : a;
    c.data.resize(bnum.data.size() + mnum.data.size() + 1, 0);
    for (int i = 0; i < mnum.data.size(); i++)
    {
        for (int j = 0; j < bnum.data.size(); j++)
        {
            c.data[j + i] += mnum.data[i] * bnum.data[j];
        }
    }
    jinwei(c);
    remove_0(c);
    if(abs_equal(c,to_Bint("0")))
        c.sign=0;
    return c;
}
Bint div(Bint a, long long b)
{
    Bint c;
    c.sign = a.sign | b<0;
    c.data.resize(a.data.size());
    for(int i=a.data.size()-1;i>=0;i--){
        if(i==0){
            c.data.push_back(a.data[0]/b);
            break;
        }
        if(a.data[i]>=b){
            c.data.push_back(a.data[i]/b);
            a.data[i]%=b;
            if(a.data[i]>0)
                a.data[i-1]+=10*a.data[i];
        }else{
            c.data.push_back(0);
            a.data[i-1]+=10*a.data[i];
            a.data[i]=0;
        }
    }
    reverse(c.data.begin(),c.data.end());
    remove_0(c);
    if(abs_equal(c,to_Bint("0")))
        c.sign=0;
    return c;
}
