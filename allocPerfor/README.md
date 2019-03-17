[toc]
# about

![stl](https://github.com/fenneishi/allocator/blob/master/picture/STL.png)

分配器的选取对容器效率直观重要，C++标准规定的默认的分配器是std：allocator,但是GNU其实提供了很多分配器供开发者选择,如下：
* std::allocator（默认分配器）
* malloc_allocator
* new_allocator
* __pool_alloc
* __mt_alloc
* bitmap_allocator

“非标准分配器”源文件位置： 
![源文件位置](https://github.com/fenneishi/allocator/blob/master/picture/%E6%BA%90%E6%96%87%E4%BB%B6%E4%BD%8D%E7%BD%AE)
以上分配器，除了std::allocator意外，存放在ext文件夹下，并归为命名空间__gnu_cxx中，使用这些分配器前需要进行如下操作：
```C++
#ifdef __GNUC__	
#include <ext/array_allocator.h>
#include <ext/mt_allocator.h>
#include <ext/debug_allocator.h>
#include <ext/pool_allocator.h>
#include <ext/bitmap_allocator.h>
#include <ext/malloc_allocator.h>
#include <ext/new_allocator.h> 
#endif
using namespace __gnu_cxx;
```
注意因为这些分配器是GNU自己提供的，不属于标准库的，所以以上编译器不具有可移植性。
本实验将针对3个主要的序列容器(list,vector,deque)进行分配器效率测试，测试内容如下

|  | deque | list | vector |
| --- | --- | --- | --- |
| std::allocator | ✔️ | ✔️ | ✔️ |
| malloc_allocator | ✔️ | ✔️ | ✔️ |
| new_allocator | ✔️ | ✔️ | ✔️ |
| __pool_alloc | ✔️ | ✔️ | ✔️ |
| __mt_alloc | ✔️ | ✔️ | ✔️ |
| bitmap_allocator | ✔️ | ✔️ | ✔️ |

注：

1. std::forward_list的底层实现和list类似，所以选一个就好
2. queue和stack严格来讲是适配器，不是容器，其底层一般为deque,所以这里并没有进行相关测试。
3. 本实验仅是各种常见分配器对序列容器的空间效率影响做的测试，对于关联容器，对于时间效率，可能在以后的实验中进行尝试。
# result
## 同一容器不同分配器
### deque
![8819cea43a00265ac943a98e68a932b0.png](https://github.com/fenneishi/allocator/blob/master/picture/deque.png)
![fb5f5e443bc3438d254cd9cf434c4e9b.png](https://github.com/fenneishi/allocator/blob/master/picture/dequeG.png)
说明：
![d1d1d7e4a31a152b078cd0b81f17c6c2.png](https://github.com/fenneishi/allocator/blob/master/picture/data_explain.png)

* 折线图是根据表“用平均值进行归一化”进行绘制的，原因见原理部分。
* 在折线图中，系统默认的分配器已经用黑色的点划线重点标出，
* 余下图表原理和此图表完全一致。

### list
![f7f22c145a60ca356b305383882cecad.png](https://github.com/fenneishi/allocator/blob/master/picture/list.png)
以下4张表为同一数据，只不过不断缩小纵坐标尺度。
![ace3afad9c8bdd1d82ce94e55076fc55.png](https://github.com/fenneishi/allocator/blob/master/picture/listG1.png)
![c4adba1515b78d52b15e431fef46acf8.png](https://github.com/fenneishi/allocator/blob/master/picture/listG2.png)
![c8bae809940e55dc11969fafa6132f38.png](https://github.com/fenneishi/allocator/blob/master/picture/listG3.png)
![5b0a278633afebe346b611750f6b19dc.png](https://github.com/fenneishi/allocator/blob/master/picture/listG4.png)
### vector
![fa90927318253de29f25a416a1295b5c.png](https://github.com/fenneishi/allocator/blob/master/picture/vector.png)
![1877524ee6b08d0adf0208c510663196.png](https://github.com/fenneishi/allocator/blob/master/picture/vectorG.png)
## 同一分配器不同容器
### std::allocator（默认分配器）
![e2b2719e27b4d1a05b13486b17d41823.png](https://github.com/fenneishi/allocator/blob/master/picture/std.png)
![93ce3da08b38ae268fbb27a4184b5d0c.png](https://github.com/fenneishi/allocator/blob/master/picture/stdG.png)
### malloc_allocator
![551f78dddd74b31a59a8b876fc674ad3.png](https://github.com/fenneishi/allocator/blob/master/picture/malloc.png)
![d397c5b3487049f1b49e80b6170cceab.png](https://github.com/fenneishi/allocator/blob/master/picture/mallocG.png)
### __pool_alloc
![0d5fc20165d2b77ed79d65e2f2f5efbf.png](https://github.com/fenneishi/allocator/blob/master/picture/pool.png)
![1d4e97ed0c55172bcdd4d51ae771241e.png](https://github.com/fenneishi/allocator/blob/master/picture/poolG.png)
### new_allocator
![de974d17c241b3a2d5238c62358f42c5.png](https://github.com/fenneishi/allocator/blob/master/picture/new.png)
![e8046778a735d7715e0266a5fce4c652.png](https://github.com/fenneishi/allocator/blob/master/picture/newG.png)
### __mt_alloc
![335c12341e4b58fe21831840bf70c462.png](https://github.com/fenneishi/allocator/blob/master/picture/mt.png)
![eee8d1f342d3b06f1731535d02285a5f.png](https://github.com/fenneishi/allocator/blob/master/picture/mtG.png)
### bitmap_allocator
![9701801e387833a1fc0e282e34afbb1e.png](https://github.com/fenneishi/allocator/blob/master/picture/bitmap.png)
![fe914a501df1e2bcb8bea3c8e146f26a.png](https://github.com/fenneishi/allocator/blob/master/picture/bitmapG.png)
# principle

1. 基本原理
    1. 本实验通过不断的往容器里添加元素来测试性能，所以并不牵扯元素查找，容器复制，元素排序等方面的性能。
    2. 本实验的测量数据有3个维度：不同的容器(3种)，不同分配器(6种），不同的数据规模(10种)，所以共有3*6*10=180个原始测量数据
2. 注意事项：
    1. 由基本原理可知，本实验共有180个测量数据，所以就有180次测量，为了防止内存不够用，每次测量都必须及时及时释放容器，否则很有可能内存被耗尽。
    2. 如果你想进行更大规模的测量，例如1亿的数据量，一定要注意提前或者你的硬件平台极限，防止内存被耗尽而程序中断。
    3. 如果你想用自己的设计的类作为元素类型，一定要设计移动构造函数，否则对于vector这种内增长的容器来说，可能会非常慢！
3. 可能问题：
    1. 编译器过度优化：本实验代码中每次存入的元素都是string("a"),由于每个元素都一样，就有可能被编译器过度优化，进而影响实验结果，本次实验中目前并没有发现这个现象。

# analyze

1. 系统默认选择(std::allocator)具有一定合理性：
    1. vector容器下，表现最好的就是std::allocator。
    2. std::allocator在queue和list中，相较于其他非标准容器表现也不算太差
    3. 所以仅从序列容器角度来看，选用std::allocator作为统一默认分配器，是一个比较均衡的选择！
    4. 另一方面从理论上来讲，当数据规模逐渐增大时，vector需要不断的内增长来适应，每次内增长都会进行大量数据迁移(如果元素没有定义移动拷贝构造，迁移的数据量更大，消耗时间更多)，但是list是链式存储，deque是分段连续存储，均没有这个问题，所以理论上，不管用什么分配器，相同的数据规模下，vector一般会更耗费时间。由以上分析可知，只能选择一个分配器作为默认的分配器时，选择对于vector更加友好的std::allocator不失为一个good choice!
2. deque：各种类型的分配器性能差别不大。
3. list:表现较好的分配器为
    1. __pool_alloc
    2. __mt_alloc
    3. bitmap_allocator
4. vector:表现最好的额就是std::allocator.
5. 一些有意思的结果：
    1. std::allocator和malloc_allocator这两款分配器对deque非常不友好，这两款分配器在list和vecto中的性能是deque的十几倍。而且这和理论上vector最慢有悖，原因可能是分配器采取了某种特殊的处理机制，也有可能是数据不准确，有待进一步复验！

# more

1. 非序列容器的探究：
    1. 本实验仅仅探究了GNU下常见分配器在序列容器上的时间性能，并未探讨在关联容器上的时间性能。
    2. 常见的关联容器底部不是红黑树，就是hash表，红黑树每次添加元素都可能需要进行必要的结构调整，而hash表，每次都需要计算hash函数，这些计算工作可能会对元素添加效率产生影响，尤其是当数据规模很大时候.
    3. 由于对于非基础类型来说，需要开发者自己提供hash函数，所以性能的hash函数也会对性能产生影响，这是在探究分配器性能时候需要注意控制的环境变量。
    4. 在hash表的设计中，C++STL采用的是separate chaining的冲突解决技术，而非open addressing，所以必须设计有效手段防止单个链表过长，而C++采取的手段非常简单，就是永远保证“篮子数>=元素数”，在这个机制下，当元规模不断扩大时候，就需要不断的进行数据迁移以制造更多的篮子，更可怕的是，每次迁移，所有数据都需要重新计算一遍hash值，当数据规模很多时，这可能非常耗时，所以理论上，不管用什么分配器，相同数据规模下，以hash表为基础数据结构的容器(unordered_set、unordered_map、unordered_multiset、unordered_multimap)比以红黑树为基础数据结构的容器(set、map、multiset、multimap)更加耗费时间！
2. 空间复杂度的探究：
    1. 本实验仅针对分配器的时间性能进行了测试，并未对空间复杂度进行测试。
    2. 由STL源码可知，所有的分配器的底层调用都是C语言的函数malloc()，但是使用malloc()获取内存有很多浪费。如下图所示，在VC6中，我们申请了大小为size内存(蓝色部分),但是实际分配给你的是下图整块内存，其中灰色部分是debug模式专有的(release模式下没有),红色部分为cookie(用来记录内存块大小和状态，例如00000041的意思是内存大小为Ox40=48字节，而状态为已经分配出去),绿色部分为自动对齐所需(vc分配的内存大小都是16的倍数)，这些“多余”的东西是内存管理所需，但是在容器中，因为容器元素都是一致的，所以这些多余的东西实际上是可以省略的。
![a663804d1f97997e4920b56d802163e8.tiff](https://github.com/fenneishi/allocator/blob/master/picture/Snip20190314_1.png)
    3. 但是std::allocator似乎只是简单的调用了malloc，而并没有针对malloc的内存浪费进行有效设计以避免，GNU的__pool_alloc分配器有针对这种浪费做了特殊的设计。如下图，__pool_alloc每次通过malloc向OS申请一大块内存，挂在索引上，然后再把一大块内存切分成小块分配给容器里的每一个元素，这样就可以有效的避免malloc的内存浪费。所以，可以通过具体的性能试验，验证__pool_alloc是否采取了有效的内存机制来防止内存浪费！
![45a0e7a7fb70842409804ee32081c8f6.tiff](https://github.com/fenneishi/allocator/blob/master/picture/Snip20190314_5.png)
3. 欢迎大家，在各种硬件平台上进行复测！
