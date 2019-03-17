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
    for(auto num:{1000000,2000000,3000000,4000000,5000000,6000000,7000000,8000000,9000000,10000000})
    {

        cout<<"test num:"<<num<<endl;
        fout<<"vector,myString,insertTime,"<<num<<":"
            <<ConTime<vector,myString>(num).testor.insertTime()
            <<endl;
        fout<<"vector,myMoveString,insertTime,"<<num<<":"
            <<ConTime<vector,myMoveString>(num).testor.insertTime()
            <<endl;
        fout<<"vector,myString,copyConstructTime,"<<num<<":"
            <<ConTime<vector,myString>(num).testor.copyConstructTime()
            <<endl;
        fout<<"vector,myMoveString,copyConstructTime,"<<num<<":"
            <<ConTime<vector,myMoveString>(num).testor.copyConstructTime()
            <<endl;
        fout<<"vector,myString,copyAssignmentTime,"<<num<<":"
            <<ConTime<vector,myString>(num).testor.copyAssignmentTime()
            <<endl;
        fout<<"vector,myMoveString,copyAssignmentTime,"<<num<<":"
            <<ConTime<vector,myMoveString>(num).testor.copyAssignmentTime()
            <<endl;

    
        fout<<"unordered_set,myString,intsertTime,"<<num<<":"
            <<ConTime<unordered_set,myString>(num).testor.insertTime()
            <<endl;
        fout<<"unordered_set,myMoveString,intsertTime,"<<num<<":"
            <<ConTime<unordered_set,myMoveString>(num).testor.insertTime()
            <<endl;
        fout<<"unordered_set,myString,copyConstructTime,"<<num<<":"
            <<ConTime<unordered_set,myString>(num).testor.copyConstructTime()
            <<endl;
        fout<<"unordered_set,myMoveString,copyConstructTime,"<<num<<":"
            <<ConTime<unordered_set,myMoveString>(num).testor.copyConstructTime()
            <<endl;
        fout<<"unordered_set,myString,copyAssignmentTime,"<<num<<":"
            <<ConTime<unordered_set,myString>(num).testor.copyAssignmentTime()
            <<endl;
        fout<<"unordered_set,myMoveString,copyAssignmentTime,"<<num<<":"
            <<ConTime<unordered_set,myMoveString>(num).testor.copyAssignmentTime()
            <<endl;
    }

    fout.close();
    cout<<"close file!"<<endl;


    return 0;
}
