#ifndef NODE_H
#define NODE_H

#include<iostream>

class base_node
{
public:  
  base_node* next;
  virtual ~base_node(){};
  virtual double retval() = 0;
};

class num_node: public base_node
{
public:
  double element = 0;
  double retval(){return element;}
};

class char_node: public base_node
{
public:
  char element = 'a';
  double retval(){return 0;}
  //char retval(){return element;}
};


#endif // NODE_H
