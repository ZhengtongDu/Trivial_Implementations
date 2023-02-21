#include<iostream>
#include<unordered_set>
#include<vector>

using namespace std;
int main()
{
  unordered_set<int> table;
  table.emplace(1);
  table.emplace(1);
  table.emplace(2);
  // 由于vector不能进行hash计算，因此不可以用unordered_set进行存储！
  // unordered_set<vector<int>> t2;
  // t2.emplace(vector<int>{1,2});
  // t2.emplace(vector<int>{2,2});
  // t2.emplace(vector<int>{1,2});
  // t2.emplace(vector<int>{1, 2, 3});
  // for(auto i = t2.begin(); i != t2.end(); i++){
  //   for(auto j = 0; j < *i.size(); i++)
  //     cout << *i[j] << " ";
  //   cout << endl;
  // }

  // for(auto i = table.begin(); i != table.end(); i++)
  //   cout << *i << endl;
  return 0;
}
