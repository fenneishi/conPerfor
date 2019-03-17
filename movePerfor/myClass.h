
#if !defined(MYCLASS_H_)
#define MYCLASS_H_

#include <cstring>
#include <cstddef>
using namespace std;
class myString
{
private:
    char *s;
public:
    myString()
    {
        s= static_cast<char *>(new char[1]);
        s[0]='\0';
    }
    myString(const char *ms)
    {
        s=static_cast<char *>(new char[strlen(ms)+1]);
        strcpy(s,ms);
    }
    myString(const myString &ms)
    {
        s=static_cast<char *>(new char[strlen(ms.s)+1]);
        strcpy(s,ms.s);
    }
    myString & operator=(const myString &ms)
    {
        if(this==&ms)return *this;
        delete[] s;
        s=static_cast<char *>(new char[strlen(ms.s)+1]);
        strcpy(s,ms.s);
        return *this;
    }
    bool operator<(const myString &ms) const
    {
        if(this==&ms)return true;
        if(strcmp(s,ms.s)<=0)
            return true;
        else 
            return false;
    }
    bool operator==(const myString &ms) const
    {
        if(this==&ms)return true;
        if(strcmp(s,ms.s)==0)
            return true;
        else
            return false;
    }
    char *getStr() const
    {
        return s;
    }
    ~myString() 
    {
        delete[] s;
    }
};


class myMoveString
{
private:
    char *s;
public:
    myMoveString()
    {
        s= static_cast<char *>(new char[1]);
        s[0]='\0';
    }
    myMoveString(const char *ms)
    {
        s=static_cast<char *>(new char[strlen(ms)+1]);
        strcpy(s,ms);
    }

    myMoveString(const myMoveString &ms)
    {
        s=static_cast<char *>(new char[strlen(ms.s)+1]);
        strcpy(s,ms.s);
    }
    
    /*注意这里的形参不能加const,两个原因：
    1、加了const,就无法修改。
    2、若形参是个const左值，则因为const左值也可以当成一种右值，所以不会出现参数匹配无法匹配的情况。*/
    myMoveString(myMoveString &&ms)
    {
        s=ms.s;
        ms.s=nullptr;
    }

    
    myMoveString & operator=(const myMoveString &ms)
    {
        if(this==&ms)return *this;
        delete[] s;
        s=static_cast<char *>(new char[strlen(ms.s)+1]);
        strcpy(s,ms.s);
        return *this;
    }
    myMoveString & operator=(myMoveString &&ms)
    {
        if(this==&ms)return *this;
        delete[] s;
        s=ms.s;
        ms.s=nullptr;
        return *this;
    }

    bool operator<(const myMoveString &ms) const
    {
        if(this==&ms)return true;
        if(strcmp(s,ms.s)<=0)
            return true;
        else 
            return false;
    }

    bool operator==(const myMoveString &ms) const
    {
        if(this==&ms)return true;
        if(strcmp(s,ms.s)==0)
            return true;
        else
            return false;
    }

    char *getStr() const
    {
        return s;
    }

    ~myMoveString() 
    {
        delete[] s;
    }
};



#endif // MYCLASS_H_
