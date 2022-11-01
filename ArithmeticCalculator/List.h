#ifndef LIST_H
#define LIST_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

enum element_type {num, op, brace_in, brace_out};

class ListNode
{
public:  
  ListNode *next;
  element_type node_type;
  double num_element;
  char op_element;
  ListNode *brace_in_element;
  ListNode *brace_out_element;
  ListNode()
  {
    std::cout << "generate empty node" << std::endl;
    num_element = 0;
    op_element = 0;
    brace_in_element = nullptr;
    brace_out_element = nullptr;
    next = nullptr;
    node_type = num;
  }
  ListNode(double _num, element_type _e_type): num_element(_num), node_type(_e_type){
    if(node_type != num)
      {
        std::cout << "wrong ndoe type!" << std::endl;
        return;
      }
    op_element = 0;
    brace_in_element = nullptr;
    brace_out_element = nullptr;
    next = nullptr;
  }
  ListNode(char _op, element_type _e_type): op_element(_op), node_type(_e_type){
    if(node_type != op)
      {
        std::cout << "wrong node type!" << std::endl;
        return;
      }
    num_element = 0;
    brace_in_element = nullptr;
    brace_out_element = nullptr;
    next = nullptr;
  }
  ListNode(ListNode *_brace, element_type _e_type): node_type(_e_type)
  {
    if(node_type == brace_in)
      {
        brace_in_element = _brace;
        brace_out_element = nullptr;
      }
    else if(node_type == brace_out)
      {
        brace_in_element = nullptr;
        brace_out_element = _brace;
      }
    else
      {
        std::cout << "wrong input!" << std::endl;
        return;
      }
    num_element = 0;
    op_element = 0;
    next = nullptr;
  }
};

ListNode* string_to_list(string str)
{
  int n = str.size();
  int idx = 0;
  int brace_flag = 0;
  bool point_flag = false;
  while(idx < n)
    {

    }
  if(brace_flag != 0)
    {
      std::cout << "wrong brace matching!" << std::endl;
      return nullptr;
    }
  return nullptr;
}

/////////////////////////////////////////////////////////////////
// Functions to convert a string expression into string vector //
/////////////////////////////////////////////////////////////////

// Supporting functions to identify single char
bool is_num(char c) 
{ return (c>='0' && c<= '9');}

bool is_op(char c)
{ return (c == '+' || c == '-' || c == '*' || c == '/');}

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
      if (is_point(c))
        {
          cout << "wrong input: point without number!" << endl;
          return strvector;
        }
      if (is_num(c))
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
          cout << "start is " << start << endl;
          cout << "idx is " << idx << endl;
          strvector.push_back(str.substr(start, strlen));
          idx = start + strlen;
        }
    }
  return strvector;
}

////////////////////////////////////////////////////////////////////////
// End of functions to convert a string expression into string vector //
////////////////////////////////////////////////////////////////////////




#endif // LIST_H
