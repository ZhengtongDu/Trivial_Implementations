#include"Node.h"

int main()
{
  num_node p;
  base_node *ptr = &p;
  std::cout << ptr->retval() << std::endl;
}
