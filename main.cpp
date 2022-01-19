#include"Vector.h"
#include<string>
#include<cstring>

class test {
	int k;
public:
	test(int f)
	{
		k = f;
	}
	~test(){
		k = 0;
	}
};



int main()
{
	TokameinE::vector<std::string> p;
	int size = p.size();
	int cap = p.capacity();

	for (int i = 0; i < 5; ++i) {
		p.push_back(std::string("a"));
	}
	TokameinE::vector<std::string> t;
	for (int i = 0; i < 5; ++i) {
		t.push_back(std::string("b"));
	}

	bool x =( p == t);
	p.swap(t);

}