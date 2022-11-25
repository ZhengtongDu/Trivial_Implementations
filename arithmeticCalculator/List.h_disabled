#ifndef LIST_H
#define LIST_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

enum element_type {num, op, paren};

class ListNode
{
public:  
  ListNode *next;
  element_type node_type;
  double num_element;
  char op_element;
  ListNode *paren_in;
  ListNode *paren_out;

  //Constructors
  ListNode() = delete; // Disable default constructor

  ListNode(const double& _num, const element_type& _e_type): num_element(_num), node_type(_e_type) // Generate number node
  {
    if(node_type != num)
      {
        std::cout << "wrong ndoe type!" << std::endl;
        return;
      }
    op_element = 0;
    paren_in = nullptr;
    paren_out = nullptr;
    next = nullptr;
  }

  ListNode(const char& _op, const element_type& _e_type): op_element(_op), node_type(_e_type) // Generate operator node
  {
    if(node_type != op)
      {
        std::cout << "wrong node type!" << std::endl;
        return;
      }
    num_element = 0;
    paren_in = nullptr;
    paren_out = nullptr;
    next = nullptr;
  }
  
  ListNode(const element_type& _e_type): node_type(_e_type) //Generate parenthese node
  {
    if(node_type != paren)
      {
        std::cout << "wrong input!" << std::endl;
        return;
      }
    num_element = 0;
    op_element = 0;
    next = nullptr;
  }

};

//////////////////////////////////////////////////////////////////
// Functions to convert a string expression into string vector  //
// Example: "(1+2.3)*4" -> {"(", "1", "+", "2.3", ")", "*", "4"}//
//////////////////////////////////////////////////////////////////

// Supporting functions to identify single char
bool is_num(char c) 
{ return (c>='0' && c<= '9');}

bool is_op(char c)
{ return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');}

bool is_point(char c)
{ return (c == '.');}

bool is_left_parenthese(char c)
{ return (c == '(');}

bool is_right_parenthese(char c)
{ return (c == ')');}


// Convert function
vector<string> split_string(string str)
{
  int idx = 0;
  int n = str.size();
  vector<string> strvector;
  while(idx < n)
    {
      char c = str[idx];
      if (is_op(c) || is_left_parenthese(c) || is_right_parenthese(c))
        {
          strvector.push_back(string(1, c));
          idx++;
        }
      else if (is_point(c))
        {
          cout << "wrong input: point without number!" << endl;
          return strvector;
        }
      else if (is_num(c))
        {
          int start = idx;
          int strlen = 1;
          bool pointflag = false;
          if(start + strlen < n)
          while(is_num(str[start + strlen]) || is_point(str[start + strlen]))
            {
              strlen++;
              if(is_point(str[start + strlen]))
                {
                  if(pointflag)
                    {
                      cout << "wrong input: more than one point!" << endl;
                      return strvector;}
                  else
                    pointflag = true;
                }
              if(start + strlen == n)
                break;
            }
          strvector.push_back(str.substr(start, strlen));
          idx = start + strlen;
        }
      else
        {
          cout << "Error when generating string vector because of invalid char!" << endl;
          return strvector;
        }
    }
  return strvector;
}

////////////////////////////////////////////////////////////////////////
// End of functions to convert a string expression into string vector //
////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////
// Functions to generate list and binary tree. //
/////////////////////////////////////////////////

//To check if the number of left parentheses is equal to that of right parenthese.
bool check_parenthese(vector<string> str)
{
  int parenthese = 0;
  int n = str.size();
  int i = 0;
  while(i < n)
    {
      if(str[i] == "(")
        parenthese++;
      if(str[i] == ")")
        parenthese--;
      i++;
    }
  return (parenthese == 0);
}

//Convert vector of strings into a data structure like linked list.
ListNode* generate_list(vector<string> str)
{
  int n = str.size();
  if(n == 0) //empty vector
    {
      cout << "Error when generating list because the vector is empty!" << endl;
      return nullptr;
    }
  if(check_parenthese(str) == false) // wrong parentheses matching
    {
      cout << "Error when generating list because of wrong parentheses matching!" << endl;
      return nullptr;
    }
  ListNode *head = nullptr; // Use it to record the head of list;
  ListNode *ptr = nullptr;
  ListNode *nextptr = nullptr;
  int i = 0;
  while((i < n) && (str[i] != ")"))// The latter condition is always true!
    {
      // generating node
      int parenlen = 0; 
      if(is_num(str[i][0]) == true)
        nextptr = new ListNode(stod(str[i]), num);
      else if (is_op(str[i][0]) == true)
        nextptr = new ListNode(str[i][0], op);
      else if (str[i] == "(")
        {
          int parenflag = 1;
          while(parenflag != 0)
            {
              parenlen++;
              if(str[i + parenlen] == "(")
                parenflag++;
              if(str[i + parenlen] == ")")
                parenflag--;
            }
          nextptr = new ListNode(paren);
          nextptr->paren_in = generate_list(vector<string>(str.begin()+i+1, str.begin()+i+parenlen));
          nextptr->paren_in->paren_out = nextptr;
        }
      // dealing with linking
      if(i == 0)
        {
          head = nextptr;
          ptr = head;
        }
      else
        {
          ptr->next = nextptr;
          ptr = ptr->next;
        }
      i += parenlen + 1;
    }
  return head;
}

void print_list(ListNode* head)
{
  if(head == nullptr)return;
  while(head != nullptr)
    {
      if(head->node_type == paren)
        {
          cout << endl << "paren in: ";
          print_list(head->paren_in);
          cout << "paren out" << endl;
        }
      else if(head->node_type == num)
        cout << head->num_element << " ";
      else if(head->node_type == op)
        cout << head->op_element << " ";
      head = head->next;
    }
}
//
bool check_logic(ListNode* head)
{
  return true;
}


////////////////////////////////////////////////////////
// End of functions to generate list and binary tree. //
////////////////////////////////////////////////////////


#endif // LIST_H
