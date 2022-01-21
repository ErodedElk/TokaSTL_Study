#include"Vector.h"
#include<string>
#include<cstring>
using namespace std;

class test
{
private:
    int* _ptr;
    string _id;
public:
    test(string id = "-1")
    {
        _id = id;
        _ptr = new int(0x1000);
        cout << _id << " constructed." << endl;
    }

    ~test()
    {
        cout << _id << " destroyed." << endl;
        delete _ptr;
    }
};

int main()
{
    TokameinE::vector<test> test1;
    test1.push_back(test("test"));
    test1.erase(test1.begin());

    return 0;
}