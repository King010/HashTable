#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include"common.h"
#include"BitMap.h"
using namespace std;

template<class K, class HashFunc = __HashFunc1<string>>
class BloomFile
{
public:
	BloomFile(size_t size)
		:_map(size)
	{}
	bool Insert(string str)
	{
		size_t idx1 = __HashFunc1()(str);
		size_t idx2 = __HashFunc2()(str);
		size_t idx3 = __HashFunc3()(str);
		size_t idx4 = __HashFunc4()(str);
		size_t idx5 = __HashFunc5()(str);
		_map.Set(idx1); _map.Set(idx2);
		_map.Set(idx3); _map.Set(idx4);
		_map.Set(idx5);

	}
	bool Find(string str)
	{
		size_t idx1 = __HashFunc1()(str);
		size_t idx2 = __HashFunc2()(str);
		size_t idx3 = __HashFunc3()(str);
		size_t idx4 = __HashFunc4()(str);
		size_t idx5 = __HashFunc5()(str);
		if (!_map.Test(idx1))
			return false;
		if (!_map.Test(idx2))
			return false;
		if (!_map.Test(idx3))
			return false;
		if (!_map.Test(idx4))
			return false;
		if (!_map.Test(idx5))
			return false;
		return true;
	}
private:
	BitMap _map;

};
