#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int main(){
  vector<int> a{1,2,3,4,5};
  vector<int> b{1,3,2,4,5,0};
  sort(b.begin(), b.end());
  for(int i = 0; i < b.size(); i++)
    cout << b[i] << " ";
  cout << endl;
  b.emplace(b.end(), 1);
  return 0;
}
