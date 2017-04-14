#pragma once
#include <vector>
#include <iostream>
using namespace std;


class BitMap
{
public:
	BitMap()
	{}

	BitMap(size_t size)
	{
		_table.resize((size>>5)+1);
	}

	// 1
	void Set(int data)
	{
		size_t byteNo = data>>5;
		size_t bitNo = data%32;

		_table[byteNo] |= (1 << bitNo); 
	}

	// data所在字节的比特位置0
	void ReSet(int data)
	{
		size_t byteNo = data>>5;
		size_t bitNo = data%32;
		_table[byteNo] &= ~(1<<bitNo);
	}

	// 检测是否存在
	bool Test(int data)
	{
		size_t byteNo = data>>5;
		size_t bitNo = data%32;

		if ((1<<bitNo) & _table[byteNo])
			return true;

		return false;
	}

private:
	std::vector<int> _table;
};

void Test()
{
	BitMap bm(100);
	bm.Set(1);
	bm.Set(20);
	bm.Set(30);
	bm.Set(40);
	bm.Set(55);
	bm.Set(65);
	bm.Set(89);

	if(bm.Test(65))
	{
		cout<<"65 In"<<endl;
	}

	if(bm.Test(66))
	{
		cout<<"55 In"<<endl;
	}
	else
	{
		cout<<"55 is Not"<<endl;
	}
}

