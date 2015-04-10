// DynamicProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <synchapi.h>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace std;

typedef struct
	{
		long size;
		long value;
		int itemNumber;
	} knapsackItems;

long fibonacci(long n);
long knapsack(long bagSize);
long recurseKnapsack(const vector<knapsackItems>& items, int index, long sizeLeft, boost::numeric::ublas::matrix<long>& cache
					 , boost::numeric::ublas::matrix<bool>& taken);

int main(int argc, char* argv)
{
	cout<<fibonacci(9999)<<endl;
	cout<<knapsack(2000)<<endl;
	getchar();
	return 0;
}

long fibonacci(long n)
{
	long first;
	long second;
	long fib;
	if(n == 0)
	{
		return 0;
	}
	if(n == 1)
	{
		return 1;
	}

	first = 0;
	second = 1;
	for(int i = 2; i <= n; ++i)
	{
		fib = first + second;
		first = second;
		second = fib;
	}

	return fib;
}


long knapsack(long bagSize)
{
	vector<knapsackItems> items;
	for(int i = 0; i < 5; ++i)
	{
		knapsackItems item;
		item.itemNumber = i + 1;
		Sleep(1000);
		srand(time(NULL));
		item.size = rand() % (1000 - 500) + 500;
		Sleep(1000);
		srand(time(NULL));
		item.value = rand() % 5000 + 1;
		items.push_back(item);
	}
	
	boost::numeric::ublas::matrix<long> cache(items.size() + 1, bagSize + 1, -1);

	for(int i = 0; i < cache.size1(); ++i)
	{
		cache(i, 0) = 0;
	}

	for(int i = 0; i < cache.size2(); ++i)
	{
		cache(0, i) = 0;
	}

	boost::numeric::ublas::matrix<bool> taken(items.size() + 1, bagSize + 1, false); 

	long val =  recurseKnapsack(items, items.size(), bagSize, cache, taken);
	for(int i = items.size(); i >= 1; --i)
	{
		if(taken(i, bagSize))
		{
			cout<<"added ";
			cout<<i;
			cout<<" with size ";
			cout<<items[i -1].size;
			cout<<" and value ";
			cout<<items[i -1].value<<endl;
			bagSize -= items[i -1].size;
		}
	}
	return val;

}

long recurseKnapsack(const vector<knapsackItems>& items, int index, long sizeLeft, 
					 boost::numeric::ublas::matrix<long>& cache, boost::numeric::ublas::matrix<bool>& taken)
{
	long returnValue;

	if(cache(index, sizeLeft) != -1)
	{
		returnValue = cache(index, sizeLeft);
		return returnValue;
	}

	if(items[index - 1].size > sizeLeft)
	{
		returnValue = cache(index - 1, sizeLeft);
		cache(index, sizeLeft) = returnValue;
		taken(index, sizeLeft) = false;
		return returnValue;
	}

	long added = recurseKnapsack(items, index - 1, sizeLeft - items[index - 1].size, cache, taken) +  items[index - 1].value;
	long skipped = recurseKnapsack(items, index - 1, sizeLeft, cache, taken) ;
	if(added > skipped)
	{
		returnValue = added;
		taken(index, sizeLeft) = true;
	}
	else
	{
		taken(index, sizeLeft) = false;
		returnValue = skipped;
	}

	cache(index, sizeLeft) = returnValue;
	return returnValue;

}



