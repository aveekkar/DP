#include <stdio.h>
#include "boost/shared_ptr.hpp"
#include "boost/numeric/ublas/matrix.hpp"
#include <vector>
#include <limits>

int MIN = std::numeric_limits<int>::min();

using namespace std;

int maxValueSubsequence(const vector<int>& input, int& start, int& end);
int maxValSubsequeceRecurse(const vector<int>& input, vector<int>& cache, int index, int& start, int& end);

int main(int argc, char **argv)
{
	vector<int> inputForMVS;
	inputForMVS.push_back(-1);
	inputForMVS.push_back(9);
	inputForMVS.push_back(-10);
	inputForMVS.push_back(3);
	inputForMVS.push_back(5);
	inputForMVS.push_back(2);
	inputForMVS.push_back(0);
	int start = 0;
	int end = 0;
	cout<<maxValueSubsequence(inputForMVS, start, end)<<endl;
	getchar();
	return 0;
}


int maxValueSubsequence(const vector<int>& input, int& start, int& end)
{
	vector<int> cache(input.size(), MIN);
	
	int maxVal = maxValSubsequeceRecurse(input, cache, input.size() - 1, start, end);
	cout<<"start: "<<start<<" end: "<<end<<endl;
	return maxVal;
}
int maxValSubsequeceRecurse(const vector<int>& input, vector<int>& cache, int index, int& start, int &end)
{
	if(index == 0)
	{
		cache[index] = input[0];
		return cache[index];
	}
	
	if(cache[index] != MIN)
	{
		return cache[index];
	}
	
	int included = maxValSubsequeceRecurse(input, cache, index - 1, start, end) + input[index];
	int startNew = input[index];
	
	if(startNew > included)
	{
		cache[index] = startNew;
		start = index; 
		end = index;
	}
	else
	{
		cache[index] = included;
		end = index;
	}
	
	return cache[index];
}





