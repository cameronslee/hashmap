// Driver
#include "hashmap.h"
int main()
{
  struct node* n = create_node(-1,"foo");
  struct hashmap *map = init_map(n, 1, 1, 1);
  insert("foobar",map);
  insert("foobar",map);
  insert("barfoo",map);
  print_list(map->list);
  return 0;
}
