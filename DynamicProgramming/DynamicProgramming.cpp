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

int longestCommonSubsequence(const string& left, const string& right);
int lcsRecurse(const string& left, const string& right, int leftIndex, int rightIndex, boost::numeric::ublas::matrix<int>& cache);
void reverseString(string& str);
int longestPalindromicSubsequence(const string& input, string& palindrome);
int LpsRecurse(const string& input, int begin, int end, boost::numeric::ublas::matrix<int>& cache);

int main(int argc, char* argv)
{
	//call fibonacci...
	cout<<fibonacci(9999)<<endl;

	//call Knapsack...
	cout<<knapsack(2000)<<endl;

	//call LCS..
	longestCommonSubsequence("empty bottle", "nematode knowledge");

	//call stringReverse...
	string toReverse = "AVEEKA";
	reverseString(toReverse);
	cout<<"Reversed: "<<toReverse<<endl;

	//Longest palindromic subsequence
	string output;
	string input = "ZZYAZBXXBAZ";
	cout<<"longest: "<<longestPalindromicSubsequence(input, output)<<endl;
	cout<<"Palindrome: "<<output<<endl;

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

int longestCommonSubsequence(const string& left, const string& right)
{
	int leftSize = left.size();
	int rightSize = right.size();

	boost::numeric::ublas::matrix<int> cache(leftSize + 1, rightSize + 1, -1);

	int longestCommonSubsequenceLength = lcsRecurse(left, right, 0, 0, cache);

	int i = 0;
	int j = 0;
	stringstream match;

	while(i < leftSize && j < rightSize)
	{
		if(left[i] == right[j])
		{
			match<<left[i];
			++i;
			++j;
		}
		else if(cache(i + 1, j) > cache(i, j + 1))
		{
			++i;
		}
		else
		{
			++j;
		}
	}

	string matchReverse = match.str();
	cout<<"left: "<<left<<endl;
	cout<<"right: "<<right<<endl;
	cout<<"Longest sequence: "<<matchReverse<<endl;
	return longestCommonSubsequenceLength;
}

int lcsRecurse(const string& left, const string& right, int leftIndex, int rightIndex, boost::numeric::ublas::matrix<int>& cache)
{
	if(cache(leftIndex, rightIndex) != -1)
	{
		return cache(leftIndex, rightIndex); 
	}

	if(leftIndex == left.size() || rightIndex == right.size())
	{
		cache(leftIndex, rightIndex) = 0;
	}
	else if(left[leftIndex] == right[rightIndex])
	{
		cache(leftIndex, rightIndex) = 1 + lcsRecurse(left, right, leftIndex + 1, rightIndex + 1, cache);
	}
	else
	{
		int a = lcsRecurse(left, right, leftIndex + 1, rightIndex, cache);
		int b = lcsRecurse(left, right, leftIndex, rightIndex + 1, cache);
		cache(leftIndex, rightIndex) = a > b ? a : b;
	}

	return cache(leftIndex, rightIndex);
}


void reverseString(string& str)
{
	if(str.size() == 0 || str.size() == 1)
	{
		return;
	}

	int mirrorLeft = -1;
	int mirrorRight = -1;
	if(str.size() % 2 == 0)
	{
		mirrorRight = str.size() / 2;
		mirrorLeft = mirrorRight - 1;
	}
	else
	{
		mirrorLeft = mirrorRight = str.size() / 2;
	}

	while(mirrorLeft != str.size())
	{
		char temp = str[mirrorLeft];
		str[mirrorLeft] = str[mirrorRight];
		str[mirrorRight] = temp;
		++mirrorLeft;
		--mirrorRight;
	}
}


int longestPalindromicSubsequence(const string& input, string& palindrome)
{
	palindrome = "";
	boost::numeric::ublas::matrix<int> cache(input.size(), input.size(), -1);
	int longest = LpsRecurse(input, 0, input.size() - 1, cache);
	int i = input.size() - 1;
	int j = 0;

	while(j <= input.size() - 1 && i >= 0)
	{
		if(input[i] == input[j] || i == j)
		{
			palindrome += input[i];
			--i;
			++j;
		}
		else
		{
			if(cache(i -1, j) > cache(i, j - 1))
			{
				--i;
			}
			else
			{
				++j;
			}
		}
	}

	palindrome += palindrome[0];

	return longest;
}


int LpsRecurse(const string& input, int begin, int end, boost::numeric::ublas::matrix<int>& cache)
{
	if(cache(begin, end) != -1)
	{
		return cache(begin, end);
	}
	if(end < begin)
	{
		cache(begin, end) = 0;
	}
	else if(begin + 1 == end && input[begin] == input[end])
	{
		cache(begin, end) = 2;
	}
	else if(begin == end)
	{
		cache(begin, end) = 1;
	}
	else
	{
		if(input[begin] == input[end])
		{
			cache(begin, end) = 2 + LpsRecurse(input, begin + 1, end - 1, cache);
		}
		else
		{
			int a = LpsRecurse(input, begin + 1, end, cache);
			int b = LpsRecurse(input, begin, end - 1, cache);
			cache(begin, end) = a > b ? a : b;
		}
	}

	return cache(begin, end);
}



















