# <信号与系统>课程实验
该项目是北京航空航天大学电子信息工程学院2016级《信号与系统》课程的实验内容。主要是一些有关信号处理的程序实现(例如卷积, 抽样, 调制等等)

根据实验要求, 所有的操作, 甚至包括**制图**， 都 **必须用C语言** 独立完成，不允许调用第三方库. 这使得该实验成为了一个绝佳的 `Hack on C` 的机会。 

在完成实验的过程中， 尝试了以下有趣的东西

1. 基于 `struct`和函数指针的C语言**面向对象**编程.

2. 基于 `GCC` 编译器所支持的`statement expression`特性的C语言**Lambda表达式**.


# 关于实现HOF时的一些奇怪现象


用这样的方式实现高阶函数，那么返回的函数只能调用一次

    Func_RealSV GetAffunc(int k){ 
        return Lambda(double _(double x){return k*x;});
    }

但是用这样的方式实现高阶函数，那么可以实现高阶函数的功能。

    Func_RealSV GetAffunc(int s){ 
        int k=s;
        return Lambda(double _(double x){return k*x;});
    }






