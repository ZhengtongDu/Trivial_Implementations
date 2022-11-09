#include"Tree.h"

using namespace std;


int main()
{
  string b = "2^(1+3)-5*(15.23)/(1+2)*3-5";
  string c = "1.25+(3*(1+2^2)*3-43)^(4-2)";
  vector<string> strb = split_string(b);
  for(int i = 0; i < strb.size(); i++)
    cout << strb[i] << " ";
  cout << endl;
  TreeNode* rootb = generate_subtree(strb);
  cout << "result is " << compute_subtree(rootb) << endl;
  vector<string> strc = split_string(c);
  for(int i = 0; i < strc.size(); i++)
    cout << strc[i] << " ";
  cout << endl;
  TreeNode* rootc = generate_subtree(strc);
  cout << "result is " << compute_subtree(rootc) << endl;

}
