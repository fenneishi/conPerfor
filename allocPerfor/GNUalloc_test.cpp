/*
内容：
GNU下常见分配器时间性能测试。
注意：
1、必须用GNU进行编译
2、需要启用-std=c++11
代改进：
1、进一步提升数据与逻辑的分离性，目前是硬编码在一起的。
2、增加关联式容器的测试。
3、增加空间效率的测试。
4、绘图自动化。
*/

// 容器
#include <list>
#include <deque>
#include <vector>
#include <map>
#include <unordered_map>
#include <initializer_list>

// 常规
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip> //用来设置输出格式；

// 标准分配器头文件
#include <memory> //內含 std::allocator

// GNU自带分配器头文件
// 欲使用 std::allocator 以外的 allocator, 得自行 #include <ext\...>
// ext/里面的库文件都是GNU自己的，并非标准规定的，所以不具有平台可移植性。
#ifdef __GNUC__
#include <ext/array_allocator.h>
#include <ext/mt_allocator.h>
#include <ext/debug_allocator.h>
#include <ext/pool_allocator.h>
#include <ext/bitmap_allocator.h>
#include <ext/malloc_allocator.h>
#include <ext/new_allocator.h>
#endif

// 其他头文件
// #include <stdexcept>
// #include <cstdlib> 		//abort()
// #include <cstdio>  		//snprintf()
// #include <cstddef>

using namespace std;
using namespace __gnu_cxx; //非标准分配器的命名空间

/*
本实验共有3个维度，分别通过3层函数调用予以实现:
1、不同的容器(3种):test_con()
2、不同的分配器(6种):test_con_alloc()
3、不同的测试次数(10种):test_con_alloc_time()
*/
template <template <typename _Tp, typename _Allocator = allocator<_Tp>> class con>
void test_con(const char *fileName, const initializer_list<long> &il);

template <typename Con_Type>
void test_con_alloc(const Con_Type &testCon, const string &allocName, const initializer_list<long> &il);

template <typename Con_Type>
void test_con_alloc_time(const Con_Type &Con, long times);

// 建立全局的文件输出流对象
ofstream fout;

int main(int argc, char const *argv[])
{
    cout << "this is a test" << endl;
    // 设置测试数据集
    long base = 10000;
    initializer_list<long> il = {100 * base, 200 * base, 300 * base, 400 * base, 500 * base, 600 * base, 700 * base, 800 * base, 900 * base, 1000 * base};
    // 进行测试
    test_con<list>("result/list", il);
    test_con<deque>("result/deque", il);
    test_con<vector>("result/vector", il);
    return 0;
}

template <template <typename _Tp, typename _Allocator = allocator<_Tp>> class con>
void test_con(const char *fileName, const initializer_list<long> &il)
{
    // 建立不同分配器的容器
    con<string>                                 c1;
    con<string,malloc_allocator<string> >       c2;
    con<string,new_allocator<string> >          c3;
    con<string,__pool_alloc<string> >           c4;
    con<string,__mt_alloc<string> >             c5;
    con<string,bitmap_allocator<string> >       c6;

    // 打开数据存入文件
    fout.open(fileName);

    // 进行必须要输出
    cout << "---------------" << fileName << "------------------" << endl;
    fout << setw(20) << setiosflags(ios_base::right) << fileName << ":";
    // cout<<setw(20)<<setiosflags(ios_base::right)<<"test time:";
    for (auto x : il)
    {
        fout << setw(10) << x << ",";
        // cout<<setw(10)<<x<<",";
    }
    fout << endl;

    // 进行测试
    test_con_alloc(c1, "default", il);
    test_con_alloc(c2, "malloc_allocator", il);
    test_con_alloc(c3, "new_allocator", il);
    test_con_alloc(c4, "__pool_alloc", il);
    test_con_alloc(c5, "__mt_alloc", il);
    test_con_alloc(c6, "bitmap_allocator", il);

    // 关闭文件
    fout.close();
}

template <typename Con_Type>
void test_con_alloc(
    const Con_Type &Con,
    const string &allocName,
    const initializer_list<long> &il)
{

    // cout << setw(20) << setiosflags(ios_base::right) << allocName;
    fout << setw(20) << setiosflags(ios_base::right) << allocName << ":";

    for (auto times : il)
    {
        test_con_alloc_time(Con, times);
    }

    fout << endl;
}

template <typename Con_Type>
void test_con_alloc_time(const Con_Type &Con, long times)
{
    Con_Type c;
    clock_t start = clock();
    for (long i = 0; i < times; i++)
    {
        c.push_back("a");
    }
    clock_t useTime = (clock() - start);
    // cout << setw(10) << setiosflags(ios_base::right) << x << ":"
    //      << setw(10) << setiosflags(ios_base::right) << useTime << "ms" << endl;
    fout << setw(10) << useTime << ",";
    // cout << setw(10) << useTime << ",";
}
