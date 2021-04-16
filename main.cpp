#include <iostream>
#include <memory>
#include <utility>
#include "smartPointer.h"
using namespace std;
// 家长与子女：a Parent has a Child, a Child knows his/her Paren
/*
 public class Parent

　　private Child myChild;

public class Child

　　private Parent myParent;

如果使用原始指针作为成员，Child和Parent由谁释放？那么如何保证指针的有效性？如何防止出现空悬指针？

shared_ptr轻松解决生命周期的问题，不必担心空悬指针。但是这个模型存在循环引用的问题，注意其中一个指针应该为weak_ptr
 */

class Child;
//class Parent;


class Parent{
private:
    weak_ptr<Child> ChildPtr;
public:
    void setChild(const shared_ptr<Child>& child){
        this->ChildPtr = child; // 赋值
    }
    void doSomething(){
        if(this->ChildPtr.lock()){

        }
    }
    ~Parent()= default;
};

class Child{
private:
    shared_ptr<Parent> ParentPtr;
public:
    void setParent(shared_ptr<Parent> parent){
        this->ParentPtr = parent;
    }
    void doSomething(){
        if(this->ParentPtr.use_count()){

        }
    }
    ~Child() = default;
};

int main() {
    weak_ptr<Parent> wpp;
    weak_ptr<Child> wpc;
    {
        shared_ptr<Parent> p(new Parent);
        shared_ptr<Child> c(new Child);
        p->setChild(c);
        c->setParent(p);
        wpp = p;
        wpc = c;
        cout << p.use_count() <<endl;
        cout << c.use_count() <<endl;
        cout << wpp.use_count() <<endl;
        cout << wpc.use_count() <<endl;
    }
    cout << wpp.use_count() <<endl;
    cout << wpc.use_count() <<endl;



    {
        cout << '\n'<< "shared_ptr" <<endl;
        // shared_ptr
        int a = 10;
        shared_ptr<int> ptra = make_shared<int>(a);
        shared_ptr<int> ptra2(ptra); //copy
        cout << "ptra.use_count:" << ptra.use_count() << endl;

        int b = 20;
        int *pd = &a;
        shared_ptr<int> ptrb = make_shared<int>(b);
        ptra2 = ptrb;
        pd = ptrb.get();
        cout << "pd:" << *pd << endl;
        cout << "ptra.use_count:" << ptra.use_count() << endl;
        cout << "ptrb.use_count:" << ptrb.use_count() << endl;
    }
    {
        cout << '\n'<< "unique_ptr" <<endl;
        //unique_ptr
        unique_ptr<int> uptr(new int(10));
        //unique_ptr<int> uptr2 = uptr; //error 不能赋值
        //unique_ptr<int> uptr2(uptr); //error 不能拷贝
        unique_ptr<int> uptr2 = move(uptr); // 转换所有权

        cout << *uptr2 << endl;
        uptr2.release();
    }
    {
        cout << '\n'<< "weak_ptr" <<endl;
        //weak_ptr
        shared_ptr<int> sh_ptr = make_shared<int>(10);
        cout <<"sh_ptr.use_count :" << sh_ptr.use_count() <<endl;

        weak_ptr<int> wp(sh_ptr); //支持赋值 拷贝
        cout<< "wp.use_count :" << wp.use_count() <<endl;
        if(!wp.expired()){
            shared_ptr<int> sh_ptr2 = wp.lock();  // 从被观测的shared_ptr获得一个可用的对象
            *sh_ptr = 100;
            int *t = sh_ptr2.get();
            cout<< wp.use_count()<<endl;
            cout<<"sh_ptr2 : " << *t <<endl;
        }
    }
    {
        cout <<'\n'<<"smartPointer"<<endl;
        smartPointer<int> sp(new int(10));
        smartPointer<int> sp2(sp);
        smartPointer<int> sp3(new int(20));
        sp2 = sp3;
        cout<<sp.use_count()<<endl;
        cout<<sp3.use_count()<<endl;


    }

}
