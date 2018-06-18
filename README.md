# <信号与系统>课程实验
该项目是北京航空航天大学电子信息工程学院2016级《信号与系统》课程的实验内容。主要是一些有关信号处理的程序实现(例如卷积, 抽样, 调制等等)

根据实验要求, 所有的操作, 甚至包括**制图**， 都 **必须用C语言** 独立完成，不允许调用第三方库. 这使得该实验成为了一个绝佳的 `Hack on C` 的机会。 

在完成实验的过程中， 尝试了以下有趣的东西

1. 基于 `struct`和函数指针的C语言**面向对象**编程.

2. 基于 `GCC` 编译器所支持的`statement expression`特性的C语言**Lambda表达式**.


## 编译指南

    $ git clone git@github.com:CNLHC/Signals-and-Systems.git
    $ cd Signals-and-Systems
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make ex5 #编译实验5程序
    $ make ex3 #编译实验3程序
    
程序在如下环境测试通过

    $ gcc --version
    gcc (Ubuntu 7.3.0-16ubuntu3) 7.3.0
    Copyright (C) 2017 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    $ cmake --version
    cmake version 3.10.2

    CMake suite maintained and supported by Kitware (kitware.com/cmake).
    $ gnuplot --version
    gnuplot 5.2 patchlevel 2

## 关于Statement Expression

[GCC 官方文档( Statements and Declarations in Expressions)](https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html)


>> A compound statement enclosed in parentheses may appear as an expression in GNU C. This allows you to use loops, switches, and local variables within an expression.

这个特性的本意应该是为了更好的组织代码逻辑。但当我无意中看到这个特性时，正好在学`Scala`，所以自然而然的联想到了Lambda表达式..

实践了一把后发现，该特性并不适合在生产环境中使用

1. 变量的生命周期非常奇怪。如后文中提到的尝试实现HOF的例子
2. 出现bug难于调试。gdb无法定位到Statement expression 中的错误
3. 代码提示支持不好。至少基于Clang的 `vscode` 和基于MSVC的 `visual studio`都不能识别这种特有的语法。不过vim-`YouCompleteMe`插件的代码检查工具倒是可以直接识别这种语法。
4. 兼容性差。在windows使用`MinGW-w64`可以编译，但是无法正常运行。


## 关于实现HOF时的一些奇怪现象


用这样的方式实现高阶函数，那么返回的函数只能**调用一次**(第一次调用是正常的，第二次调用会直接抛出`Segment fault`)

    Func_RealSV GetAffunc(int k){ 
        return Lambda(double _(double x){return k*x;});
    }

但是用这样的方式实现高阶函数，那么可以实现高阶函数的功能。

    Func_RealSV GetAffunc(int s){ 
        int k=s;
        return Lambda(double _(double x){return k*x;});
    }






