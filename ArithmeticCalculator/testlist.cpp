#include"List.h"

using namespace std;


int main()
{
  string a = "1+110.5-12/20";
  vector<string> strv = split_string(a);
  for(int i = 0; i < strv.size(); i++)
    cout << "strv[i] is " << strv[i] << endl;


  //  ListNode ptr1(1.0,num);
  //  ListNode ptr2('+',op);
  //  ListNode ptr3(&ptr1,brace_in);
  //  ListNode ptr4(&ptr2,brace_out);
  
  //  std::cout << ptr1.num_element << std::endl;
  //  std::cout << ptr2.op_element << std::endl;
  //  std::cout << ptr3.brace_in_element->num_element << std::endl;
  //  std::cout << ptr4->rightnum_element() << std::endl;
}
