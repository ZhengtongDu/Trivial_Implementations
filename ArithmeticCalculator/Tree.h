#ifndef TREE_H
#define TREE_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

enum element_type {num, op};

class TreeNode
{
public:  
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
  element_type node_type;
  double num_element;
  char op_element;
  int parenlock;

  //Constructors
  TreeNode() = delete; // Disable default constructor

  // Generate number node
  TreeNode(const double& _num, const element_type& _e_type): num_element(_num), node_type(_e_type)
  {
    if(node_type != num)
      {
        std::cout << "Error happens when generating node because node type is not num!" << std::endl;
        return;
      }
    op_element = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    parenlock = 0;
  }

  // Generate operator node
  TreeNode(const char& _op, const element_type& _e_type): op_element(_op), node_type(_e_type)
  {
    if(node_type != op)
      {
        std::cout << "Error happens when generating node because node type is not op!" << std::endl;
        return;
      }
    num_element = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    parenlock = 0;
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

// Convert function into vector of strings
vector<string> split_string(const string& str)
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
          cout << "Error happens when spliting string because an unexpected point appears!" << endl;
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
                      cout << "Error happens when spliting string because an unexpected point appears!" << endl;
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
          cout << "Error happens when generating string vector because of invalid char!" << endl;
          return strvector;
        }
    }
  return strvector;
}

////////////////////////////////////////////////////////////////////////
// End of functions to convert a string expression into string vector //
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////
// Functions to generate binary tree. //
////////////////////////////////////////

//To check if the number of left parentheses is equal to that of right parenthese.
bool check_parenthese(const vector<string>& str)
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

///////////////////////////////////////////////
// End of functions to generate binary tree. //
///////////////////////////////////////////////

////////////////////////////////////////////////////
// New version of binary notation tree generation //
////////////////////////////////////////////////////

int count_paren(const vector<string>& str, int idx)
{
      int parenflag = 1;
      int parenlen = 0;
      while(parenflag != 0)
        {
          parenlen++;
          if(str[idx + parenlen] == "(")
            parenflag++;
          if(str[idx + parenlen] == ")")
            parenflag--;
        }
      return parenlen;
}

bool check_substr_logic(const vector<string>& str)
{
  int n = str.size();
  int i = 0;
  int parenlen = 0; 
  bool numflag = true;
  while(i < n)
    {
      if(is_num(str[i][0]) && numflag);
      else if(is_op(str[i][0]) && !numflag);
      else if((str[i] == "(") && numflag)
        {
          parenlen = count_paren(str, i);
          if(check_substr_logic(vector<string>(str.begin()+i+1, str.begin()+i+parenlen)) == false)
            return false;
        }
      else return false;
      numflag = !numflag;
      i += parenlen + 1;
      parenlen = 0;
    }
  return true;
}

int rank_operator(const char& c)
{
  if(c == '+' || c == '-')
    return 1;
  else if(c == '*' || c == '/')
    return 2;
  else if(c == '^')
    return 3;
  cout << c << endl;
  cout << "Error happens when ranking operator!" << endl;
  return -1;
}

void lock_on(TreeNode *subroot)
{
  if(subroot == nullptr) return;
  lock_on(subroot->left);
  subroot->parenlock = 1;
  lock_on(subroot->right);
}

bool compare_priority(const char& c1, const char& c2)
{
  if(rank_operator(c1) >= rank_operator(c2))
  return true;
  else return false;
}


TreeNode* generate_subtree(const vector<string>& str)
{
  // Check if parentheses in expression match
  if(check_parenthese(str) == false) 
    {
      cout << "Error happens when generating list because of wrong parentheses matching!" << endl;
      return nullptr;
    }
  // Check if the logic of expression is right.
  if(check_substr_logic(str) == false)
    {
      cout << "Error happens when generating subtree because the logic of expression is wrong!" << endl;
      return nullptr;
    }
  int n = str.size();
  if(n == 0)
    return nullptr;
  TreeNode *subroot;
  int parenlen = 0; 
  if(is_num(str[0][0]) == true)
    subroot = new TreeNode(stod(str[0]), num);
  else
    {
      parenlen = count_paren(str, 0);
      subroot = generate_subtree(vector<string>(str.begin()+1, str.begin() + parenlen));
      lock_on(subroot);
    }
  int i = parenlen + 1;
  TreeNode *ptr = subroot;
  TreeNode *op_ptr = nullptr;
  TreeNode *right_op_ptr = nullptr;
  while(i < n)
    {
      parenlen = 0;
      op_ptr = new TreeNode(str[i][0], op);
      while((right_op_ptr != nullptr) && ((right_op_ptr->parenlock == 1)||(compare_priority(right_op_ptr->op_element, op_ptr->op_element) == true)))
        right_op_ptr = right_op_ptr->parent;
      if(right_op_ptr == nullptr)
        {
          op_ptr->left = subroot;
          subroot = op_ptr;
        }
      else
        {
          op_ptr->left = right_op_ptr->right;
          right_op_ptr->right = op_ptr;
          op_ptr->parent = right_op_ptr;
        }
      op_ptr->left->parent = op_ptr;
      i++;
      
      if(is_num(str[i][0]) == true)
        ptr = new TreeNode(stod(str[i]), num);
      else
        {
          parenlen = count_paren(str, i);
          ptr = generate_subtree(vector<string>(str.begin() + i + 1, str.begin() + i + parenlen));
          lock_on(ptr);
        }
      op_ptr->right = ptr;
      ptr->parent = op_ptr;
      i += parenlen + 1;
      right_op_ptr = subroot;
      while(right_op_ptr->right->node_type == op)
        right_op_ptr = right_op_ptr->right;
    }
  return subroot;
}    

void print_subtree(TreeNode *subroot)
{
  if(subroot == nullptr)
    return;
  print_subtree(subroot->left);
  if(subroot->node_type == num)
    cout << subroot->num_element << " ";
  else
    cout << subroot->op_element << " "; 
  print_subtree(subroot->right);
}

double compute(double num1, double num2, char op)
{
  if(op == '+') return num1 + num2;
  else if(op == '-') return num1 - num2;
  else if(op == '*') return num1 * num2;
  else if(op == '/')
    {
      if(num2 == 0)
        {
          cout << "Error happens when computing because dividend is 0!" << endl;
          return 0;
        }
      return num1 / num2;
    }
  else if(op == '^') return pow(num1, num2);
  cout << "Error happens when computing because invalid operator!" << endl;
  return 0;
}

double compute_subtree(TreeNode *subroot)
{
  if(subroot->node_type == num)
    return subroot->num_element;
  return compute(compute_subtree(subroot->left), compute_subtree(subroot->right), subroot->op_element);
}

///////////////////////////////////////////////////////
// End of version of binary notation tree generation //
///////////////////////////////////////////////////////

#endif // TREE_H
