#ifndef TREE_H
#define TREE_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

enum element_type {num, op, paren};

class TreeNode
{
public:  
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
  TreeNode *next;
  element_type node_type;
  double num_element;
  char op_element;
  TreeNode *paren_in;
  TreeNode *paren_out;
  int parenlock = 0;
  
  //Constructors
  TreeNode() = delete; // Disable default constructor

  TreeNode(const double& _num, const element_type& _e_type): num_element(_num), node_type(_e_type) // Generate number node
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
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    parenlock = 0;
  }

  TreeNode(const char& _op, const element_type& _e_type): op_element(_op), node_type(_e_type) // Generate operator node
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
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    parenlock = 0;
  }
  
  TreeNode(const element_type& _e_type): node_type(_e_type) //Generate parenthese node
  {
    if(node_type != paren)
      {
        std::cout << "wrong input!" << std::endl;
        return;
      }
    num_element = 0;
    op_element = 0;
    next = nullptr;
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


// Convert function
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
/*
//Convert vector of strings into a data structure like linked list.
TreeNode* generate_list(vector<string> str)
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
  TreeNode *head = nullptr; // Use it to record the head of list;
  TreeNode *ptr = nullptr;
  TreeNode *nextptr = nullptr;
  int i = 0;
  while((i < n) && (str[i] != ")"))// The latter condition is always true!
    {
      // generating node
      int parenlen = 0; 
      if(is_num(str[i][0]) == true)
        nextptr = new TreeNode(stod(str[i]), num);
      else if (is_op(str[i][0]) == true)
        nextptr = new TreeNode(str[i][0], op);
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
          nextptr = new TreeNode(paren);
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
      parenlen = 0;
    }
  return head;
}

void print_list(TreeNode* head)
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
*/
////////////////////////////////////////////////////////
// End of functions to generate list and binary tree. //
////////////////////////////////////////////////////////

////////////////////////////////////////////////////
// New version of binary notation tree generation //
////////////////////////////////////////////////////

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
          int parenflag = 1;
          while(parenflag != 0)
            {
              parenlen++;
              if(str[i + parenlen] == "(")
                parenflag++;
              if(str[i + parenlen] == ")")
                parenflag--;
            }
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
      int parenflag = 1;
      parenlen = 0;
      while(parenflag != 0)
        {
          parenlen++;
          if(str[0 + parenlen] == "(")
            parenflag++;
          if(str[0 + parenlen] == ")")
            parenflag--;
        }
      subroot = generate_subtree(vector<string>(str.begin()+1, str.begin() + parenlen));
      lock_on(subroot);
    }
  int i = parenlen + 1;
  TreeNode *ptr = subroot;
  TreeNode *op_ptr = nullptr;
  TreeNode *right_op_ptr = nullptr;
  /*
  if(i < n)
    {
      parenlen = 0;
      op_ptr = new TreeNode(str[i][0], op);
      op_ptr->left = ptr;
      ptr->parent = op_ptr;
      subroot = op_ptr;
      i++;
      if(is_num(str[i][0]) == true)
        ptr = new TreeNode(stod(str[i]), num);
      else
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
          ptr = generate_subtree(vector<string>(str.begin() + i + 1, str.begin() + i + parenlen));
          lock_on(ptr);
        }
      op_ptr->right = ptr;
      ptr->parent = op_ptr;
      right_op_ptr = op_ptr;
      i += parenlen + 1;
    }
*/
  while(i < n)
    {
      parenlen = 0;
      op_ptr = new TreeNode(str[i][0], op);
      while((right_op_ptr != nullptr) && ((right_op_ptr->parenlock == 1)||(compare_priority(right_op_ptr->op_element, op_ptr->op_element) == true)))
        right_op_ptr = right_op_ptr->parent;
      //      cout << "right_op_ptr->op_element is " << right_op_ptr->op_element << endl;
      //      cout << "op_ptr->op_element is " << op_ptr->op_element << endl;
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
          int parenflag = 1;
          while(parenflag != 0)
            {
              parenlen++;
              if(str[i + parenlen] == "(")
                parenflag++;
              if(str[i + parenlen] == ")")
                parenflag--;
            }
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
  cout << "left:" << endl;
  print_subtree(subroot->left);
  if(subroot->node_type == num)
    cout << subroot->num_element << " ";
  else
    cout << subroot->op_element << " "; 
  cout << "right:" << endl;
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
