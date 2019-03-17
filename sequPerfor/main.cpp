#include "myClass.h"
#include "conTime.h"
#include <fstream>

using ConTimeSpace::ConTime;
using namespace std;




int main(int argc, char const *argv[])
{
    fstream fout;
    
    cout<<"open file!"<<endl;
    fout.open("result.txt");
    for(auto num:{1000000,2000000,3000000,4000000,5000000,6000000,7000000,8000000,9000000,10000000})
    {

        cout<<"test num:"<<num<<endl;

        fout<<"vector,"<<num<<":"
            <<ConTime<vector,myString>(num).testor.insertTime()
            <<endl;
        fout<<"deque,"<<num<<":"
            <<ConTime<deque,myString>(num).testor.insertTime()
            <<endl;
        fout<<"list,"<<num<<":"
            <<ConTime<deque,myString>(num).testor.insertTime()
            <<endl;
    }

    fout.close();
    cout<<"close file!"<<endl;


    return 0;
}
