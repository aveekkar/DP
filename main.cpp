#include <stdio.h>
#include "boost/shared_ptr.hpp"
#include "boost/numeric/ublas/matrix.hpp"
#include <vector>
#include <limits>
#include <unordered_set>

int MIN = std::numeric_limits<int>::min();
int MAX = std::numeric_limits<int>::max();

using namespace std;

int maxValueSubsequence(const vector<int>& input, int& start, int& end);
int maxValSubsequeceRecurse(const vector<int>& input, vector<int>& cache, int index, int& start, int& end);
bool wordBreak(const string& s, unordered_set<string>& dict);
void recurseMatrix(int** matrix, int j, vector<vector<string> >& results, const string& s, vector<string>& temp);
int maxDiff(const vector<int>& input, int& low, int& high);

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

  //word break...
  unordered_set<string> dict = {"aaaa","aa","a"};
  cout<<"word break?? "<<wordBreak("aaaaaaaa", dict)<<endl;

  //unordered_set<string> dict = {"ga","gas","skate", "ate", "kate"};
  //cout<<"word break?? "<<wordBreak("gaskate", dict)<<endl;
  
  //Max diff..
  vector<int> maxDiffInput;
  maxDiffInput.push_back(5);
  maxDiffInput.push_back(10);
  maxDiffInput.push_back(4);
  maxDiffInput.push_back(6);
  maxDiffInput.push_back(7);
  maxDiffInput.push_back(11);
  maxDiffInput.push_back(1);
  maxDiffInput.push_back(7);
  
  int low, high;
  int maxDifference  = maxDiff(maxDiffInput, low, high);
  cout<<"Max diff is "<<maxDifference<<" at "<<low<<" and "<<high<<endl;

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


bool wordBreak(const string& s, unordered_set<string>& dict)
{
  int len = s.size();
  if(len == 0)
  {
	  return false;
  }
  int **matrix = new int *[len];
  for(int i = 0; i < len; ++i)
  {
	  matrix[i] = new int[len];
  }

  for(int i = 0; i < len; ++i)
  {
	  for(int j = 0; j < len; ++j)
	  {
		  matrix[i][j] = -1;
	  }
  }

  for(int i = 0; i < len; ++i)
  {
	  for(int j = i; j < len; ++j)
	  {
		  string subString = s.substr(i, j -i + 1);
		  if(dict.find(subString) != dict.end())
		  {
			  matrix[i][j] = 1;
		  }
		  else
		  {
			  matrix[i][j] = 0;
		  }
	  }
  }

  vector<vector<string> > results;
  vector<string> temp;
  temp.push_back(" ");
  recurseMatrix(matrix, 0, results, s, temp);
  for(vector<vector<string> >::const_iterator i = results.begin(); i != results.end(); ++i)
  {
	  for(vector<string>::const_iterator j = i->begin(); j != i->end(); ++j)
	  {
		  cout<<(*j)<<" ";
	  }
	  cout<<endl;
  }

  for(int i = 0; i < len; ++i)
  {
	  for(int j = i; j < len; ++j)
	  {
		  for(int k = i; k < j; ++k)
		  {
			  if (matrix[i][j] != 1)
			  {
				  matrix[i][j] = ((matrix[i][k] == 1) && (matrix[k + 1][j] == 1)) ? 1 : 0;
			  }
		  }
	  }
  }


  bool ret = matrix[0][len - 1] == 1;

  for(int i = 0; i < len; ++i)
  {
	  delete[] matrix[i];
  }
  delete[] matrix;

  return ret;
}

void recurseMatrix(int** matrix, int j, vector<vector<string> >& results, const string& s, vector<string>& temp)
{
  int i = j;
  if(j == s.length())
  {
	  results.push_back(temp);
	  return;
  }
  for(;j < s.length(); ++j)
  {
	  if(matrix[i][j] == 1)
	  {
		  string subString = s.substr(0, j -i + 1);
		  temp.push_back(subString);
		  recurseMatrix(matrix, j + 1, results, s, temp);
		  if(!temp.empty())
		  {
			  temp.pop_back();
		  }
	  }
  }

}

int maxDiff(const vector<int>& input, int& low, int& high)
{
    int maxDiff = 0;
    int minimum = input[0];
    low = 0;
    high = 0;
    int minAt = 0;
    
    for(int i = 1; i < input.size(); ++i)
    {
        int diff = input[i] - minimum;
        if(input[i] < minimum)
        {
            minimum = input[i];
            minAt = i;
            continue;
        }
        if(diff > maxDiff)
        {
            low = minAt;
            high = i;
            maxDiff = diff;
        }
    }
    
    return maxDiff;
}




