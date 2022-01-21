#include"Vector.h"
#include<string>
#include<cstring>

class test {
public:
	int k;
public:
	test(char f)
	{
		k = f;
	}
	~test(){
		k = 0;
	}
	bool operator==(test& v)
	{
		return k == v.k;
	}
	bool operator!=(test& v)
	{
		return !(k == v.k);
	}

};



int main()
{
	TokameinE::vector<test> p;
	int size = p.size();
	int cap = p.capacity();

	for (int i = 0; i < 5; ++i) {
		p.push_back(test('a'));
	}
	TokameinE::vector<test> t;
	for (int i = 0; i < 5; ++i) {
		t.push_back(test('b'+i));
	}
	p = t;
	//p.erase(p.begin() + 1);
	bool x =( p == t);
	p.swap(t);

}