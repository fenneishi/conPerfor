
// 第一步:包含conTime.h头文件
#include "conTime.h"
// 第二步:引入接口名称ConTime
using ConTimeSpace::ConTime;
// 第三步：调用接口:见使用举例


// // 以下为GNU平台上的一种分配器，其他编译器请略过
// #ifdef __GNUC__
// #include <ext/pool_allocator.h>
// using __gnu_cxx::__pool_alloc;
// #endif

#include "myClass.h"//引入自定义类型，方便后面测试。

int main(int argc, char const *argv[])
{
    // 使用举例：

    // 容器类型为vector,元素类型为string,元素规模为1000个，测量类型为insertTime
    // (计算并输出“向空的vector中插入1000个string”所花费的时间!(单位为千分之一毫秒)
    // 不能指定元素的内容,例如指定string为“hello,world”。算法会自动调用string的默认构造函数作为容器中的元素。如果元素类型为自己定义的，请确保自定义类型拥有默认构造函数。
    cout<<"vector<string>,insertTime,1000:"
        <<ConTime<vector,string>(1000).testor.insertTime()
        <<endl;

    // 容器类型为vector,元素类型myString(自己定义的类型)，元素规模为1000个，测量类型为insertTime
    ConTime<vector,myString>  temp(1000);
    cout<<"vector<myString>,insertTime,1000:"
        <<temp.testor.insertTime()
        <<endl;

    // 指定分配器为std::allocator,实际上如果不指定，默认的分配器也是这个！
    cout<<"list<myMoveString,std::allocator>,insertTime,1000:"
        <<ConTime<list,myMoveString,std::allocator<myMoveString> >(1000).testor.insertTime()
        <<endl;

    // 指定分配器为std::allocator,实际上如果不指定，默认的分配器也是这个！
    cout<<"list<myMoveString,std::allocator>,insertTime,1000:"
        <<ConTime<list,myMoveString,std::allocator<myMoveString> >(1000).testor.insertTime()
        <<endl;

    // // 注意：非GNU编译器无法编译下面这个例子。
    // // 指定分配器为__gnu_cxx::pool_allocator(GNU特有的分配器，不属于标准，不具有可移植性，需要包含<ext/pool_allocator.h>，)
    // cout<<"list<myMoveString,__pool_alloc>,insertTime,1000:"
    //     <<ConTime<list,myMoveString,__pool_alloc<myMoveString> >(1000).testor.insertTime()
    //     <<endl;
    



    //批量测试并输出到文件
    ofstream fout;
    fout.open("result/list.txt");
    for(auto num:{1000,2,3,4,5})
    {
        fout<<"unordered_map<int,myString>:"
            <<ConTime<unordered_multimap,int,string>(num).testor.insertTime()
            <<endl;
    }

    // 使用默认的KeyEqual函数对象、hash函数对象的两种方式：
    fout<<"unordered_multimap<int,myString,std::equal_to,std::hash>,insertTime,1000:"
        <<ConTime<unordered_multimap,int,string>(1000).testor.insertTime()
        <<endl;
    fout<<"unordered_multimap<int,myString,std::equal_to,hash>,std::hash,1000:"
        <<ConTime<unordered_multimap,int,string,std::hash<int>,std::equal_to<int> >(1000).testor.insertTime()
        <<endl;




    // 使用自定义的compare函数对象类型、hash函数对象类型
    // 自定义hasn函数对象的类型
    struct myHash
    {
        size_t operator()(myString const& s) const
        {
            return std::hash<char *>()(s.getStr());
        }
    };
    // 自定义keyEqual函数对象的类型
    struct myKeyEqual
    {
        bool operator()(myString const& Sleft,myString const& Sright) const
        {
            return Sleft==Sright;
        }
    };
    fout<<"unordered_multimap<myString,int,lambda,lambda>,insertTime,1000:"
        << ConTime<unordered_multimap,myString,string,myHash,myKeyEqual>(1000).testor.insertTime();



    // 测试容器的拷贝构造效率
    cout<<"vector<string>,copyConstructTime,1000:"
        <<ConTime<vector,string>(1000).testor.copyConstructTime()
        <<endl;
    // 测试容器的拷贝赋值效率
    cout<<"vector<string>,copyAssignmentTime,1000:"
        <<ConTime<vector,string>(1000).testor.copyAssignmentTime()
        <<endl;


    // 一次构建，多次测试！
    ConTime<vector,myString> testObject(1000);
    cout<<"vector<string>,insertTime,1000:"
        <<testObject.testor.insertTime()
        <<endl;
    cout<<"vector<string>,copyConstructTime,1000:"
        <<testObject.testor.copyConstructTime()
        <<endl;
    cout<<"vector<string>,copyAssignmentTime,1000:"
        <<testObject.testor.copyAssignmentTime()
        <<endl;


    // 所有使用形式，即所有接口(以insertTime()为例):
    // vector
    ConTime<vector,string>(1000).testor.insertTime();
    ConTime<vector,string,std::allocator<string> >(1000).testor.insertTime();
    // list
    ConTime<list,string>(1000).testor.insertTime();
    ConTime<list,string,std::allocator<string> >(1000).testor.insertTime();
    // deque
    ConTime<deque,string>(1000).testor.insertTime();
    ConTime<deque,string,std::allocator<string> >(1000).testor.insertTime();


    // set
    ConTime<set,int>(1000).testor.insertTime();
    ConTime<set,int,std::less<int> >(1000).testor.insertTime();
    ConTime<set,int,std::less<int>,std::allocator<int> >(1000).testor.insertTime();
    // multiset
    ConTime<multiset,int>(1000).testor.insertTime();
    ConTime<multiset,int,std::less<int> >(1000).testor.insertTime();
    ConTime<multiset,int,std::less<int>,std::allocator<int> >(1000).testor.insertTime();
    // unordered_set
    ConTime<unordered_set,int>(1000).testor.insertTime();
    ConTime<unordered_set,int,std::hash<int> >(1000).testor.insertTime();
    ConTime<unordered_set,int,std::hash<int>,std::equal_to<int> >(1000).testor.insertTime();
    ConTime<unordered_set,int,std::hash<int>,std::equal_to<int>,std::allocator<int> >(1000).testor.insertTime();
    // unordered_multiset
    ConTime<unordered_multiset,int>(1000).testor.insertTime();
    ConTime<unordered_multiset,int,std::hash<int> >(1000).testor.insertTime();
    ConTime<unordered_multiset,int,std::hash<int>,std::equal_to<int> >(1000).testor.insertTime();
    ConTime<unordered_multiset,int,std::hash<int>,std::equal_to<int>,std::allocator<int> >(1000).testor.insertTime();



    // map
    ConTime<map,int,string>(1000).testor.insertTime();
    ConTime<map,int,string,std::less<int> >(1000).testor.insertTime();
    ConTime<map,int,string,std::less<int>,std::allocator<pair<const int,string> > >(1000).testor.insertTime();
    // multimap
    ConTime<multimap,int,string>(1000).testor.insertTime();
    ConTime<multimap,int,string,std::less<int> >(1000).testor.insertTime();
    ConTime<multimap,int,string,std::less<int>,std::allocator<pair<const int,string> > >(1000).testor.insertTime();
    // unordered_map
    ConTime<unordered_map,int,string>(1000).testor.insertTime();
    ConTime<unordered_map,int,string,std::hash<int> >(1000).testor.insertTime();
    ConTime<unordered_map,int,string,std::hash<int>,std::equal_to<int> >(1000).testor.insertTime();
    ConTime<unordered_map,int,string,std::hash<int>,std::equal_to<int>,std::allocator< pair<const int,string> > >(1000).testor.insertTime();
    // unordered_multimap
    ConTime<unordered_multimap,int,string>(1000).testor.insertTime();
    ConTime<unordered_multimap,int,string,std::hash<int> >(1000).testor.insertTime();
    ConTime<unordered_multimap,int,string,std::hash<int>,std::equal_to<int> >(1000).testor.insertTime();
    ConTime<unordered_multimap,int,string,std::hash<int>,std::equal_to<int>,std::allocator<pair<const int,string> > >(1000).testor.insertTime();




    
    
    
    
    
   




    return 0 ;
}




