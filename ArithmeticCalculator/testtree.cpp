#include"Tree.h"

using namespace std;


int main()
{
  //  string a = "1+(110.5-12/20))";
  //  string b = "2^(1+3)-5*(15.23)/(1+2)*3-5";
  string b = "1+(3*(1+2^2)*3-43)^(4-2)";
  vector<string> strv = split_string(b);
  cout << endl;
  for(int i = 0; i < strv.size(); i++)
    cout << strv[i] << " ";
  cout << endl;
  //  cout << "check substring:" << check_substr_logic(strv) << endl;
  TreeNode* root = generate_subtree(strv);
  cout << "result is " << compute_subtree(root) << endl;

  //  print_subtree(root);

  //  cout << root->left->num_element << " " << root->op_element << " " << root->right->num_element << endl;
  //  cout << endl << "generate and print list:" << endl;
  //  cout << check_parenthese(strv) << endl; 

  //  cout << stod("1.23") << endl;
  //  ListNode *head;
  //  head = generate_list(split_string(b));
  //  print_list(head);
  //  ListNode ptr1(1.0,num);
  //  ListNode ptr2('+',op);
  //  ListNode ptr3(&ptr1,brace_in);
  //  ListNode ptr4(&ptr2,brace_out);
  
  //  std::cout << ptr1.num_element << std::endl;
  //  std::cout << ptr2.op_element << std::endl;
  //  std::cout << ptr3.brace_in_element->num_element << std::endl;
  //  std::cout << ptr4->rightnum_element() << std::endl;
}
