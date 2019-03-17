/*
模板参数有三种类型
偏特化的理解
不定长模板参数的偏特化方式
模板模板参数的偏特化方式
*/

#if !defined(CONTime_H_)
#define CONTime_H_

#include <fstream>
#include <iostream>
#include <string>
#include <memory> //std::allocator()
#include <ctime> //clock()
#include <utility>  //pair<key,T>(...)
#include <functional> //std::less<int>
#include <initializer_list>

#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;






namespace ConTimeSpace
{

template<typename _ConType>
class _timeComputer
{
protected:
    _ConType con;
    long testNum;
public:
    _timeComputer(long num):testNum(num),con(){}
    virtual size_t insertTime()=0;
    size_t copyConstructTime()
    {
        insertTime();
        size_t start=clock();
        _ConType temp(con);
        return clock()-start;
    }
    size_t copyAssignmentTime()
    {
        insertTime();
        _ConType temp;
        size_t start=clock();
        temp=con;
        return clock()-start;
    }
};
template <typename _ConType,typename _EleType>
class _seqConCom:public _timeComputer<_ConType>
{
private:
    typedef _timeComputer<_ConType> Father;
public:
    _seqConCom(long num=10000):Father(num){};
    virtual size_t insertTime()
    {
        size_t start=clock();
        for(int i=0;i<Father::testNum;i++)
        {
            Father::con.push_back(_EleType());
        }
        return clock()-start;
    }
};
template <typename _ConType,typename _Key,typename _Data>
class _mapCom:public _timeComputer<_ConType>
{
private:
    typedef _timeComputer<_ConType> Father;
public:
    _mapCom(long num=10000):Father(num){};
    virtual size_t insertTime()
    {
        size_t start=clock();
        for(int i=0;i<Father::testNum;i++)
        {
            Father::con.insert(pair<_Key,_Data>( _Key(),_Data() ) );
        }
        return clock()-start;
    }
};
template <typename _ConType,typename _Key>
class _setCom:public _timeComputer<_ConType>
{
private:
    typedef _timeComputer<_ConType> Father;
public:
    _setCom(long num=10000):Father(num){};
    virtual size_t insertTime()
    {
        size_t start=clock();
        for(int i=0;i<Father::testNum;i++)
        {
            Father::con.insert(_Key());
        }
        return clock()-start;
    }
};




// 统一接口定义(泛化接口)
template < template <typename... Tail  > class con ,typename... Tail>
class ConTime{};


// 定义各种sequence container接口(特化接口)
// vector
template < typename EleType>
struct ConTime<vector,EleType>
{
    typedef vector<EleType> conType;
    _seqConCom<conType,EleType> testor;
    ConTime(long num):testor(num){};
};
template < typename EleType,typename alloc>
struct ConTime<vector,EleType,alloc> 
{
    typedef vector<EleType,alloc> conType;
    _seqConCom<conType,EleType> testor;
    ConTime(long num):testor(num){};
};
// list
template < typename EleType>
struct ConTime<list,EleType>
{
    typedef list<EleType> conType;
    _seqConCom<conType,EleType> testor;
    ConTime(long num):testor(num){};
};
template < typename EleType,typename alloc>
struct ConTime<list,EleType,alloc>
{
    typedef list<EleType,alloc> conType;
    _seqConCom<conType,EleType> testor;
    ConTime(long num):testor(num){};
};
// deque
template < typename EleType>
struct ConTime<deque,EleType>
{
    typedef deque<EleType> conType;
    _seqConCom<conType,EleType> testor;
    ConTime(long num):testor(num){};
};
template < typename EleType,typename alloc>
struct ConTime<deque,EleType,alloc>
{
    typedef deque<EleType,alloc> conType;
    _seqConCom<conType,EleType> testor;
    ConTime(long num):testor(num){};
};

// 定义各种set container接口(特化接口)
// set
template < class Key>
struct ConTime<set,Key>
{
    typedef set<Key> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Compare>
struct ConTime<set,Key,Compare>
{
    typedef set<Key,Compare> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Compare,class Allocator>
struct ConTime<set,Key,Compare,Allocator>
{
    typedef set<Key,Compare,Allocator> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
// multiset
template < class Key>
struct ConTime<multiset,Key>
{
    typedef multiset<Key> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Compare>
struct ConTime<multiset,Key,Compare>
{
    typedef multiset<Key,Compare> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Compare,class Allocator>
struct ConTime<multiset,Key,Compare,Allocator>
{
    typedef multiset<Key,Compare,Allocator> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
// unordered_set
template < class Key>
struct ConTime<unordered_set,Key>
{
    typedef unordered_set<Key> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Hash>
struct ConTime<unordered_set,Key,Hash>
{
    typedef unordered_set<Key,Hash> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Hash,class KeyEqual>
struct ConTime<unordered_set,Key,Hash,KeyEqual>
{
    typedef unordered_set<Key,Hash,KeyEqual> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Hash,class KeyEqual,class Allocator>
struct ConTime<unordered_set,Key,Hash,KeyEqual,Allocator>
{
    typedef unordered_set<Key,Hash,KeyEqual,Allocator> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
// unordered_multiset
template < class Key>
struct ConTime<unordered_multiset,Key>
{
    typedef unordered_multiset<Key> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Hash>
struct ConTime<unordered_multiset,Key,Hash>
{
    typedef unordered_multiset<Key,Hash> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Hash,class KeyEqual>
struct ConTime<unordered_multiset,Key,Hash,KeyEqual>
{
    typedef unordered_multiset<Key,Hash,KeyEqual> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Hash,class KeyEqual,class Allocator>
struct ConTime<unordered_multiset,Key,Hash,KeyEqual,Allocator>
{
    typedef unordered_set<Key,Hash,KeyEqual,Allocator> conType;
    _setCom<conType,Key> testor;
    ConTime(long num):testor(num){};
};

// // 定义各种map container接口(特化接口)
// map
template < class Key,class Data>
struct ConTime<map,Key,Data>
{
    typedef map<Key,Data> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Data,class Compare>
struct ConTime<map,Key,Data,Compare>
{
    typedef map<Key,Data,Compare> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Data,class Compare,class Allocator>
struct ConTime<map,Key,Data,Compare,Allocator>
{
    typedef map<Key,Data,Compare,Allocator> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
// multimap
template < class Key,class Data>
struct ConTime<multimap,Key,Data>
{
    typedef multimap<Key,Data> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Data,class Compare>
struct ConTime<multimap,Key,Data,Compare>
{
    typedef multimap<Key,Data,Compare> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Data,class Compare,class Allocator>
struct ConTime<multimap,Key,Data,Compare,Allocator>
{
    typedef multimap<Key,Data,Compare,Allocator> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
// unordered_map
template < class Key,class Data>
struct ConTime<unordered_map,Key,Data>
{
    typedef unordered_map<Key,Data> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Data,class Hash>
struct ConTime<unordered_map,Key,Data,Hash>
{
    typedef unordered_map<Key,Data,Hash> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Data,class Hash,class KeyEqual>
struct ConTime<unordered_map,Key,Data,Hash,KeyEqual>
{
    typedef unordered_map<Key,Data,Hash,KeyEqual> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Data,class Hash,class KeyEqual,class Allocator>
struct ConTime<unordered_map,Key,Data,Hash,KeyEqual,Allocator>
{
    typedef unordered_map<Key,Data,Hash,KeyEqual,Allocator> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
// unordered_multimap
template < class Key,class Data>
struct ConTime<unordered_multimap,Key,Data>
{
    typedef unordered_multimap<Key,Data> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Data,class Hash>
struct ConTime<unordered_multimap,Key,Data,Hash>
{
    typedef unordered_multimap<Key,Data,Hash> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Data,class Hash,class KeyEqual>
struct ConTime<unordered_multimap,Key,Data,Hash,KeyEqual>
{
    typedef unordered_multimap<Key,Data,Hash,KeyEqual> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};
template < class Key,class Data,class Hash,class KeyEqual,class Allocator>
struct ConTime<unordered_multimap,Key,Data,Hash,KeyEqual,Allocator>
{
    typedef unordered_map<Key,Data,Hash,KeyEqual,Allocator> conType;
    _mapCom<conType,Key,Data> testor;
    ConTime(long num):testor(num){};
};





}//namespace ConTimeSpace








#endif // CONTime_H_
