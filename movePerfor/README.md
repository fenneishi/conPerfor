# movePerfor

## about
本实验主要探究了容器vector和unordered_set对移动语义的性能敏感(时间性能)。C++11定义了移动语义，使得拷贝过程更加灵活，在原有的深拷贝、浅拷贝的基础上增加了移动拷贝。如果原object是一种右值(const型、临时对象)，那么便可以使用移动拷贝构造。右值使用移动拷贝既有浅拷贝的效率，又有深拷贝的安全性。
本实验之所以选择vector和unordered_set作为测试对象，是因为这两种容器会有较大规模的内增长迁移行为，这种行为往往会使得容器对于移动拷贝非常敏感。
本实验的两种元素类型为：myString,myMoveString，前者没有定义移动语义，后者定义了。
![moveCopy](https://github.com/fenneishi/conPerfor/blob/master/movePerfor/picture/moveCopy.png)
## Data
![analyseT](https://github.com/fenneishi/movePerfor/blob/master/movePerfor/picture/analyseT.png)
![analyseG](https://github.com/fenneishi/movePerfor/blob/master/movePerfor/picture/analyseG.png)
## analyse
1. 对于Vector:
    1. “大规模逐个插入元素”的行为对移动语义比较敏感，这与理论思考比较一致。
    2. 拷贝构造 和 拷贝赋值，对移动语义并不敏感
    3. 造成以上情况最有可能的原因就是 conTime接口默认调用元素的默认构造函数，而默认构造出来的对象很小，并不能体现出移动语义的优势。
2. 对于unordered_set:
    1. 很明显，unordered_set的拷贝构造和拷贝赋值采用特殊的机制使得时间复杂度为O(1),猜测可能是用了引用计数+COW.
    2. “大规模逐个插入元素”对移动语义不敏感，这点其实很好理解，因为unordered_set内增长的是篮子，而不是元素，所以内增长速度和元素类型无任何关系，顶多和hash函数有关系。
## more
1. **修正自定义类型的默认构造函数，使得默认构造对象体积更大，以充分体现出移动语义的优势。**
2. 增加实验的组数，取平均值，增加实验数据说服力。
3. 在更多的平台进行测试。
4. 探究更多容器对移动语义的性能敏感性。
5. 借助Python,使得数据分析更加自动化。
## mail
fenneishitiger@gmail.com
