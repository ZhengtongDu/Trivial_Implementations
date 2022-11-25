#include<iostream>
#include<string>
#include<vector>
using namespace std;
    int maxArea(vector<int>& height) {
        int n = height.size();
        vector<vector<int>> f(n, vector<int>(n, 0));
        int ret = min(height[0],height[n-1]) * (n-1);
        int l = height[0];
        int r = height[n-1];
        int i = 0;
        int j = n - 1;
        while(i < j){
            if(height[i] < l)
            i++;
            else if(height[j] < r)
            j--;
            else if(min(height[i], height[j])*(j - i) > ret){
                l = height[i];
                r = height[j];
                ret = min(height[i], height[j])*(j - i);
                i++;
            }
            else if(height[i] >= height[j])
            j--;
            else
            i++;
        }
        return ret;
    }

int main()
{
  vector<int> height{1,1000,1000,3,5,8,7};

  vector<vector<char>> table{{'I', 'V',
'X'}, {'X', 'L', 'C'}, {'C', 'D', 'M'}};
  string a = "123";
  a = 'b' + a;
  a = 'c' + a;
  cout <<a <<endl;
  return 0;

}
