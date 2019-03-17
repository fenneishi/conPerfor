#include "myClass.h"
#include "conTime.h"
#include <fstream>

using ConTimeSpace::ConTime;
using namespace std;

// 定义myString,myMoveString的hash函数对象类型，并注入到标准库的hash模板中.
namespace std
{
    template<> 
    struct hash<myString>
    {
        size_t operator()(const myString & ms) const
        {
            return hash<char *>()(ms.getStr());
        };
    };

    template<> 
    struct hash<myMoveString>
    {
        size_t operator()(const myMoveString & ms) const
        {
            return hash<char *>()(ms.getStr());
        };
    };

}




int main(int argc, char const *argv[])
{
    fstream fout;
    
    cout<<"open file!"<<endl;
    fout.open("result");
    for(auto num:{10000,20000,30000,40000,50000,60000,70000,80000,90000,100000})
    {

        cout<<"test num:"<<num<<endl;


        fout<<"set,single,intsertTime,"<<num<<":"
            <<ConTime<set,myString>(num).testor.insertTime()
            <<endl;
        fout<<"map,single,intsertTime,"<<num<<":"
            <<ConTime<map,int,myString>(num).testor.insertTime()
            <<endl;
        fout<<"unordered_set,single,intsertTime,"<<num<<":"
            <<ConTime<unordered_set,myString>(num).testor.insertTime()
            <<endl;
        fout<<"unordered_map,single,intsertTime,"<<num<<":"
            <<ConTime<unordered_map,int,myString>(num).testor.insertTime()
            <<endl;

        
        fout<<"set,multi,intsertTime,"<<num<<":"
            <<ConTime<multiset,myString>(num).testor.insertTime()
            <<endl;
        fout<<"map,multi,intsertTime,"<<num<<":"
            <<ConTime<multimap,int,myString>(num).testor.insertTime()
            <<endl;
        fout<<"unordered_set,multi,intsertTime,"<<num<<":"
            <<ConTime<unordered_multiset,myString>(num).testor.insertTime()
            <<endl;
        fout<<"unordered_map,multi,intsertTime,"<<num<<":"
            <<ConTime<unordered_multimap,int,myString>(num).testor.insertTime()
            <<endl;

    }

    fout.close();
    cout<<"close file!"<<endl;


    return 0;
}
