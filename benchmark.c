#include <time.h>
#include "hashmap.h"

#define NUM_INSERTIONS 69420

void test_insertion(struct hashmap* mp, int num_insertions, int hash_strategy) {
  for (int i = 0; i < num_insertions; i++) {
    char temp[10];
    sprintf(temp,"%d", i);
    insert(temp, mp, hash_strategy);
  }
}

int main() {
  struct node* n = create_node(-1,"foo");
  struct hashmap *map = init_map(n, 1, 1, 1);
  
  /* test insertion */
  clock_t begin = clock();
  test_insertion(map, NUM_INSERTIONS, 0);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time Spent: %f\n", time_spent);

  /* test rehash */
}
