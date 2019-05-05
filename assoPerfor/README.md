# about
本实验主要探究了各种Associative Container的插入性能(时间性能)
# Data
![analyseT.png](https://github.com/fenneishi/conPerfor/tree/master/assoPerfor/picture/analyseT.png)
![analyseG.png](https://github.com/fenneishi/conPerfor/tree/master/assoPerfor/picture/analyseG.png)
# analyse
1. 所有关联式容器的插入时间复杂度都是O(n)
1. unordered_multimap和其他所有关联式容器不是一个量级的，非常慢。可以说站在在unordered_multimap的角度，其他关联式容器的插入时间复杂度都是O(1)
2. 除去unordered_multimap:(set约等于multiset)>multimap>unordered_multiset>(map约等于unordered_map)>unordered_set
# more
1. 增加实验的组数，取平均值，增加实验数据说服力。
2. 在更多的平台进行测试。
3. 探究更多容器对移动语义的性能敏感性。
4. 借助Python,使得数据分析更加自动化。
# mail
fenneishitiger@gmail.com
