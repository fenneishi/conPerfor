# about
做这个接口的原因是最近做了大量有关于容器性能的测试的内容，例如不同分配器对性能的影响，例如定义移动造对性能的影响。由于每次测试一种可能性都要重复写一段测试代码，实在令人苦恼，于是做了这个统一接口。
这个接口几乎可以适用所有的容器、元素、分配器、hash函数、比较函数的组合，无论你要测试哪种你能想到的合都可以用这个接口，你甚至可以让接口使用默认的分配器、比较函数，hash函数。
另外，你可以测量插入效率，也可以测量拷贝效率。
当然这个接口也还有一些问题，见more。
欢迎感兴趣的朋友试用、建议、改进。
联系方式fenneishi@163.cm
## 使用：
```c++
// 第一步:包含conTime.h头文件
#include "conTime.h"
// 第二步:引入接口名称ConTime
using ConTimeSpace::ConTime;
// 第三步：调用接口:
ConTime<vector,string>(1000).testor.insertTime();
// 更多例子见下文
```
注意：

1. 需要支持C++11.
2. 我只测试了GNU和clang,vc没有测试，欢迎大家测试.
    1. g++ (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609
    2. Apple LLVM version 9.1.0 (clang-902.0.39.1)
3. 联系fenneishi@163.com.

## 功能:
使用本接口，你可以针对任何容器，元素的可能组合进行性能测试，目前可以测试:

| 测试内容 | 举例 |
| --- | --- |
| 插入n个数元素所需时间： | ConTime<vector,string>(1000).testor.insertTime(); |
| 拷贝构造一个规模为n的容器所需时间。 | ConTime<vector,string>(1000).testor.copyConstructTime(); |
| 向一个空的容器中进行拷贝赋值(规模为n)所需时间 | ConTime<vector,string>(1000).testor.copyAssignmentTime(); |
## 注意
    1. 容器的模板参数的指定方式和STL标准接口完全一致，这也是本接口的特色之一，例：
 

|创建一个容器|创建一个测试对象(测试规模为1000)并insertTime测试（返回值为花费时间）|
| --- | --- |
| vector<string> c1; | ConTime<vector,string>(1000).testor.insertTime(); |
| vector<string,allocator<string>> c2; | ConTime<vector,string,std::allocator<string> >(1000).testor.insertTime();|
| unordered_map<int,string> c3; |  ConTime<unordered_map,int,string>(1000).testor.insertTime(); |
| unordered_map<int,string,hash<int>>  c4; | ConTime<unordered_map,int,string,std::hash<int> >(1000).testor.insertTime(); |
| unordered_map<int,string,hash<int>,equal_to<int>> c5; | ConTime<unordered_map,int,string,std::hash<int>,std::equal_to<int> >(1000).testor.insertTime(); |
| unordered_map<int,string,hash<int>,equal_to<int>,allocator<pair<int,string>>> c6; | ConTime<unordered_map,int,string,std::hash<int>,std::equal_to<int>,std::allocator< pair<const int,string> > >(1000).testor.insertTime(); |

 
    2. 规模n是需要在构造测试对象时指定的.
    3. 实际上在进行测试的时候，你需要2步走,但为了方便你可以合并成1步：
```C++
 // 1、构建测试对象：
ConTime<vector,myString> testObject(1000);
// 2、生成测试子并进行测试:
testObject.testor.insertTime();
// 3、合并成一步：
ConTime<vector,myString>(1000).testor.insertTime();
```

# Eg:
```C++
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

    // 注意：非GNU编译器无法编译下面这个例子。
    // 指定分配器为__gnu_cxx::pool_allocator(GNU特有的分配器，不属于标准，不具有可移植性，需要包含<ext/pool_allocator.h>，)
    cout<<"list<myMoveString,__pool_alloc>,insertTime,1000:"
        <<ConTime<list,myMoveString,__pool_alloc<myMoveString> >(1000).testor.insertTime()
        <<endl;
    



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
```
 # more

1.  增加array、stack,queue
    1.  目前不支持array、stack,queue。后面有时间增加对这几种的支持。
2.  指定元素内容：目前的接口只能指定元素类型，例如string,不能指定元素内容。当你指定元素类型为string时候，真正放入容器的是string(),即调用默认构造函数创建的元素对象，后面有时间可让接口指定元素的内容。
3.  鲁棒性不够：目前接口的鲁棒性不够高，还不能对很多错误使用进行合理报错，可能的错误使用如下：
    1. 测试规模超过容器上限或者计算平台上限。
    2. 元素是否定义移动构造和移动拷贝对容器性能影响巨大，好在标准库的元素类型，例如string是有良好的移动定义，若要使用自定义类型需要注意这点。
    3. 测试以红黑树为底层实现的容器(set,map,multiset,multimap)，一定要重载<符号,这点和直接使用容器是一样的。
    4. 同理测试hash为底层实现的容器(unordered_....),重载==，若元素为自定义，还需定义hash函数对象类型，或注入namespace,部分特化标准库的hash模板。
    5. 若使用非标准的分配器，如__pool_malloc，则不具有可移植性。