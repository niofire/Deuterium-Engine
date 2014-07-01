#include <iostream>
#include "d_ptr.h"
#include <iostream>
class some
{
public:
	some() {}
	~some() {}

	void print() { std::cout << "HELLO FROM PRINT";}
	void callback() { std::cout << "callback";}
};

int main()
{
	int* sd = new int(1);

	d_ptr<some> g(new some);
	d_ptr<some> d ;//= g;
	d = g;
	if(true)
	{
		d_ptr<some> asff = d;
	}
	d_ptr<some> q = d;
	q.clear();

	std::cout << g.num_handles() << " " << d.num_handles();// << " " << q.num_handles();

	return 0;
}