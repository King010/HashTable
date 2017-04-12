#pragma once
#include "common.h"
#include <vector>
#include <string>
#include <assert.h>

/*
// 大数据-->
template<class K, class V>
struct HashTableNode
{
	HashTableNode(const K& key, const V& value)
		: _key(key)
		, _value(value)
		, _next(NULL)
	{}

	HashTableNode<K, V>* _next;
	K _key;
	V _value;
};

// 迭代器

// 增容 STL
template<class K, class V>
class HashTableBucket
{
public:
	HashTableBucket(size_t capacity = 10)
		: _size(0)
	{
		capacity = GetNextPrim(capacity);
		_table.resize(capacity);
		for (size_t idx = 0; idx < capacity; ++idx)
			_table[idx] = NULL;
	}

	bool Insert(const K& key, const V& value)
	{
		CheckCapacity();
		size_t index = HashFun(key);
		HashTableNode<K, V>* pCur = _table[index];
		while(NULL != pCur)
		{
			if(key == pCur->_key)
				return false;
			pCur = pCur->_next;
		}

		HashTableNode<K, V>* pNewNode = new HashTableNode<K, V>(key, value);
		pNewNode->_next = _table[index];
		_table[index] = pNewNode;
		_size++;

		return true;
	}

	bool Find(const K& key)
	{
		size_t index = HashFun(key);
		HashTableNode<K, V>* pCur = _table[index];
		while(NULL != pCur)
		{
			if(key == pCur->_key)
				return true;

			pCur = pCur->_next;
		}

		return false;
	}

	bool Remove(const K& key)
	{
		size_t index = HashFun(key);
		HashTableNode<K, V>* pCur = _table[index];
		HashTableNode<K, V>* pPre = pCur;
		while(NULL != pCur)
		{
			if(key == pCur->_key)
			{
				if(pCur == _table[index])
				{
					_table[index] = pPre->_next;
				}
				else
				{
					pPre->_next = pCur->_next;
				}
				
				delete pCur;
				--_size;
				return true;
			}

			pPre = pCur;
			pCur = pCur->_next;
			
		}

		return false;
	}

	void Clear()
	{
		for (size_t idx = 0; idx < _table.size(); ++idx)
		{
			HashTableNode<K, V>* pCur = _table[idx];
			while(pCur)
			{
				HashTableNode<K, V>* pDel = pCur;
				pCur = pCur->_next;
				delete pDel;
			}

			_table[idx] = NULL;
		}

		_size = 0;
	}

	~HashTableBucket()
	{
		Clear();
	}

	//HashTableBucket(HashTableBucket<T>& ht);
	//HashTableBucket<T>& operator=(HashTableBucket<T>& ht);

private:
	//
	void CheckCapacity()
	{
		if (_size == _table.size())
		{
			HashTableBucket<K, V> temp(GetNextPrim(_size));
			// 增容
			// 原哈希桶中的结点插入到新哈希桶
			for (size_t idx = 0; idx < _size; ++idx)
			{
				HashTableNode<K, V>* pCur = _table[idx];
				HashTableNode<K, V>* pPre = NULL;
				while(pCur)
				{
					pPre = pCur;
					pCur = pCur->_next;

					// 定位在新哈希桶中的位置
					size_t index = temp.HashFun(pPre->_key);
					pPre->_next = temp._table[index];
					temp._table[index] = pPre;
					temp._size++;
				}

				_table[idx] = NULL;
			}

			//Swap(temp);
			std::swap(_size, temp._size);
			std::swap(_table, temp._table);
		}
	}

private:
	size_t HashFun(const K& key)
	{
		return key % _table.capacity();
	}

private:
	vector<HashTableNode<K, V>*> _table;
	size_t _size;
};


void TestHashTableBucket()
{
	HashTableBucket<int, int> ht;
	ht.Insert(10, 10);
	ht.Insert(11, 11);
	ht.Insert(44, 44);
	ht.Insert(54, 54);
	ht.Insert(1, 1);

	bool ret = ht.Find(54);
	ret = ht.Find(6);
	// 非头
	//ht.Remove(1);
	ht.Remove(54);

	// 头
	ht.Remove(10);
}


void TestCapacity()
{
	HashTableBucket<int, int> ht;
	ht.Insert(1,1);
	ht.Insert(11,2);
	ht.Insert(21,3);
	ht.Insert(2,2);
	ht.Insert(3,3);
	ht.Insert(4,4);
	ht.Insert(5,5);
	ht.Insert(6,6);
	ht.Insert(7,7);
	ht.Insert(8,8);
	ht.Insert(9,9);
}
*/


// 大数据-->
template<class K, class V>
struct HashTableNode
{
	HashTableNode(const K& key, const V& value)
		: _kv(key, value)
		, _next(NULL)
	{}

	HashTableNode<K, V>* _next;
	pair<K,V> _kv;
};


template<class K, class V, class _HashFunc = HashFunDef<K>>
class HashTableBucket;


// 迭代器

template<class K, class V, class Ref, class Ptr, class _HashFunc = HashFunDef<K>>
struct _HashBucketIterator
{
	typedef HashTableNode<K, V> Node;
	typedef HashTableBucket<K, V, _HashFunc> HashTable;
	typedef _HashBucketIterator<K, V, Ref, Ptr, _HashFunc> Self;
public:
	_HashBucketIterator()
		: _node(NULL)
		, _ht(NULL)
	{}

	_HashBucketIterator(Node* node, HashTable* ht)
		: _node(node)
		, _ht(ht)
	{}

	Ref operator*()
	{
		return _node->_kv;
	}

	Ptr operator->()
	{
		return &(operator*());
	}

	Self& operator++()
	{
		_node = _Next(_node);
		return *this;
	}

	Self operator++(int)
	{
		Self temp(*this);
		++(*this);
		return temp;
	}

	bool operator==(const Self& self)const
	{
		return _node ==self._node;/* && _ht == self._ht;*/
	}

	bool operator!=(const Self& self)const
	{
		return !(*this == self);
	}

private:
	Node* _Next(Node* node)
	{
		Node* next = node->_next;
		if(next)
			return next;
		else
		{
			size_t index = _ht->HashFun(node->_kv.first)+1;
			for(; index < _ht->_table.size(); ++index)
			{
				Node* pHead = _ht->_table[index];
				if(pHead)
					return pHead;
			}

			return NULL;
		}
	}

private:
	Node* _node;
	HashTable* _ht;
};


template<class K, class V, class _HashFunc>
class HashTableBucket
{
public:
	friend struct _HashBucketIterator<K, V, pair<K, V>&, pair<K, V>* , _HashFunc>;
	typedef _HashBucketIterator<K, V, pair<K, V>&, pair<K, V>* , _HashFunc> Iterator;

public:
	HashTableBucket(size_t capacity = 10)
		: _size(0)
	{
		capacity = GetNextPrim(capacity);
		_table.resize(capacity);
		for (size_t idx = 0; idx < capacity; ++idx)
			_table[idx] = NULL;
	}

	// Insert（）---> key 相同
	pair<bool, Iterator> Insert(const pair<K, V>& kv)
	{
		CheckCapacity();
		size_t index = HashFun(kv.first);

		HashTableNode<K, V>* pCur = _table[index];
		while(NULL != pCur)
		{
			if(kv.first == pCur->_kv.first)
				return make_pair(false, Iterator());
			pCur = pCur->_next;
		}

		HashTableNode<K, V>* pNewNode = new HashTableNode<K, V>(kv.first, kv.second);
		pNewNode->_next = _table[index];
		_table[index] = pNewNode;
		_size++;

		return make_pair(true, Iterator(pNewNode, this));
	}

	bool Find(const K& key)
	{
		size_t index = HashFun(key);
		HashTableNode<K, V>* pCur = _table[index];
		while(NULL != pCur)
		{
			if(key == pCur->_kv.first)
				return true;

			pCur = pCur->_next;
		}

		return false;
	}

	bool Remove(const K& key)
	{
		size_t index = HashFun(key);
		HashTableNode<K, V>* pCur = _table[index];
		HashTableNode<K, V>* pPre = pCur;
		while(NULL != pCur)
		{
			if(key == pCur->_kv.first)
			{
				if(pCur == _table[index])
				{
					_table[index] = pPre->_next;
				}
				else
				{
					pPre->_next = pCur->_next;
				}

				delete pCur;
				--_size;
				return true;
			}

			pPre = pCur;
			pCur = pCur->_next;

		}

		return false;
	}

	void Clear()
	{
		for (size_t idx = 0; idx < _table.size(); ++idx)
		{
			HashTableNode<K, V>* pCur = _table[idx];
			while(pCur)
			{
				HashTableNode<K, V>* pDel = pCur;
				pCur = pCur->_next;
				delete pDel;
			}

			_table[idx] = NULL;
		}

		_size = 0;
	}

	~HashTableBucket()
	{
		Clear();
	}

	//
	V& operator[](const K& key)
	{
		size_t index = HashFun(key);
		HashTableNode<K, V>* pCur = _table[index];
		while(pCur)
		{
			if(pCur->_kv.first == key)
				return pCur->_kv.second;

			pCur = pCur->_next;
		}


		assert(false);
	}

	Iterator Begin()
	{
		for (size_t index = 0; index < _table.size(); ++index)
		{
			HashTableNode<K, V>* pCur = _table[index];
			if(pCur)
				return Iterator(pCur, this);
		}

		return Iterator();
	}

	Iterator End()
	{
		return Iterator(NULL, this);
	}

	//HashTableBucket(HashTableBucket<T>& ht);
	//HashTableBucket<T>& operator=(HashTableBucket<T>& ht);

private:
	//
	void CheckCapacity()
	{
		if (_size == _table.size())
		{
			HashTableBucket<K, V> temp(GetNextPrim(_size));
			// 增容
			// 原哈希桶中的结点插入到新哈希桶
			for (size_t idx = 0; idx < _size; ++idx)
			{
				HashTableNode<K, V>* pCur = _table[idx];
				HashTableNode<K, V>* pPre = NULL;
				while(pCur)
				{
					pPre = pCur;
					pCur = pCur->_next;

					// 定位在新哈希桶中的位置
					size_t index = temp.HashFun(pPre->_kv.first);
					pPre->_next = temp._table[index];
					temp._table[index] = pPre;
					temp._size++;
				}

				_table[idx] = NULL;
			}

			//Swap(temp);
			std::swap(_size, temp._size);
			std::swap(_table, temp._table);
		}
	}

private:
	size_t HashFun(const K& key)
	{
		return _HashFunc()(key)%_table.size();
		//return key % _table.capacity();
	}

private:
	vector<HashTableNode<K, V>*> _table;
	size_t _size;
};


template<class K, class V, class Ref, class Ptr, class _HashFunc = HashFunDef<K>>
class UnOrderMap
{
	typedef HashTableBucket<K, V, Ref, Ptr, _HashFunc> HashTable;
private:
	HashTable _hashTable;
};


void TestHashTableBucket()
{
	HashTableBucket<string, string> ht1;
	ht1.Insert(make_pair("杨过", "姑姑"));
	ht1.Insert(make_pair("靖哥哥", "蓉妹妹"));
	ht1.Insert(make_pair("无忌", "敏敏"));
	ht1.Insert(make_pair("9527", "秋香"));

	//<node, ht>
	HashTableBucket<string, string>::Iterator it = ht1.Begin();

	//it(node==NULL ht)
	while(it != ht1.End())//node==NULL ht==NULL
	{
		cout<<(*it).second<<endl;
		++it;
	}
}
