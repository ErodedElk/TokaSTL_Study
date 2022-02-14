#include"Vector.h"
#include<string>
#include<cstring>
#include"List.h"
using namespace std;

class test
{
private:
    //int* _ptr;
    string _id;
public:
    test(string id = "-1")
    {
        _id = id;
        //_ptr = new int(0x1000);
        cout << _id << " constructed." << endl;
    }

    ~test()
    {
        cout << _id << " destroyed." << endl;
        //delete _ptr;
    }
};

int main()
{

    TokameinE::list<int> k;
    TokameinE::list<int>::iterator f = k.begin();
    f = k.end();
    bool tt = k.empty();
    int siz = k.size();
    k.push_back(1);


    //k.empty();
   // TokameinE::vector<test> test1;
   // test1.push_back(test("test"));
   // test1.erase(test1.begin());

    return 0;
}