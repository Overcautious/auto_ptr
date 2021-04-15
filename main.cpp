#include <iostream>
#include <memory>
using namespace std;

int main() {
    int a = 10;
    shared_ptr<int> ptra = make_shared<int>(a);
    shared_ptr<int> ptra2(ptra); //copy
    cout << ptra.use_count() <<endl;

    int b = 20;
    int *pd = &a;
    shared_ptr<int> ptrb = make_shared<int>(b);
    ptra2 = ptrb;
    pd = ptrb.get();
    cout << "pd:" << *pd <<endl;
    cout << "ptra.use_count:"<< ptra.use_count() <<endl;
    cout << "ptrb.use_count:"<< ptrb.use_count() << endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
