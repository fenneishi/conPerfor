# about
本实验主要探究了各种Sequence Container的插入性能(时间性能)
# Data
![analyseT.png](https://github.com/fenneishi/conPerfor/blob/master/sequPerfor/picture/analyseT.png)
![analyseG.png](https://github.com/fenneishi/conPerfor/blob/master/sequPerfor/picture/analyseG.png)
横坐标：插入元素个数(单位：个)
纵坐标：花费时间(单位:百万分之一秒)
# analyse
1. 插入时间复杂度都是O(n)
2. vector确实比较慢一下，猜测可能原因是内增长。
3. deque和list几乎没有任何差别。
# more
1. 增加实验的组数，取平均值，增加实验数据说服力。
2. 在更多的平台进行测试。
3. 借助Python,使得数据分析更加自动化。
# mail
fenneishitiger@gmail.com
