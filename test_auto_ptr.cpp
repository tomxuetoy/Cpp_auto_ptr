//文件名为test_auto_ptr.cpp
//auto_ptr位于<memory>头文件中

#include <memory>
#include <iostream>

using namespace std;
class MyClass
{
public:
    int i;
    MyClass(int s) {
        i=s;
    }
    ~MyClass() {
        cout<<"This class has been destroied.  "<<i<<endl;
    }
    void myFunc() {
        cout<<"myFunc() done.  "<<i<<endl;
    }
};

int main()
{
    auto_ptr<MyClass> ptr1(new MyClass(1));
    auto_ptr<MyClass>ptr2(new MyClass(2));
    ptr1->myFunc();
    ptr2->myFunc();
    cout<<"test 1 done\n"<<endl;

    ptr2 = ptr1; // original allocated ptr2 will be destroied, by Tom Xue
    ptr2->myFunc();
    // ptr1->myFunc();//取消注释会发生段错误或未定义结果
    cout<<"test 2 done\n"<<endl;

    MyClass* ptr = ptr2.get();
    ptr->myFunc();
    ptr2.reset(new MyClass(3)); // so ptr/ptr1 is destroied 
    ptr2->myFunc();
    ptr->myFunc(); //此处会产生未定义的结果
    cout<<"test 3 done\n"<<endl;
    return 0;   // then ptr2(3) will be destroied
}
/*
if we comment out it:
    // ptr1->myFunc();//取消注释会发生段错误或未定义结果
$ ./a.out 
myFunc() done.  1
myFunc() done.  2
test 1 done

This class has been destroied.  2
myFunc() done.  1
test 2 done

myFunc() done.  1
This class has been destroied.  1
myFunc() done.  3
myFunc() done.  0
test 3 done

This class has been destroied.  3



if we do not comment out it:
    ptr1->myFunc();//取消注释会发生段错误或未定义结果
$ ./a.out 
myFunc() done.  1
myFunc() done.  2
test 1 done

This class has been destroied.  2
myFunc() done.  1
Segmentation fault (core dumped)

 * */
