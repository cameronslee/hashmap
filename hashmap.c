#include <stdio.h>
#include <stdlib.h>
#include "hashes.h"

struct pair {
  uint32_t first;
  const char * second;
};

struct node {
  struct pair data;
  struct node* next;
};

struct node* create_node(uint32_t first, const char* second) {
  struct node* n = (struct node*)malloc(sizeof(struct node));
  n->data.first = first;
  n->data.second = second;
  n->next = NULL;
  return n;
}

void push_node(struct node** head, uint32_t key, const char* value) {
  struct node* new_node = create_node(key, value);
  new_node->next = *head;
  *head = new_node;
  *head = new_node;
}

void delete_node(struct node** head, uint32_t key) {
  struct node* curr = *head;
  struct node* prev = NULL;
  while (curr != NULL) {
    if (curr->data.first == key) {
      if (prev == NULL) {
        *head = curr->next;
      } else {
        prev->next = curr->next;
      }
      free(curr);
      return;
    }
    prev = curr;
    curr = curr->next;
  }
}

void print_list(struct node* head) {
  struct node* curr = head;
  while (curr != NULL) {
    printf("(%d, %s) ", curr->data.first, curr->data.second);
    curr = curr->next;
  }
  printf("\n");
}

struct unordered_map {
  struct node* list;
  int bucket_size;
  int total_elements;
  float max_load_factor; //default 1
};

struct unordered_map* init_map(struct node* head, int bucket_size, int total_elements, float max_load_factor) {
  struct unordered_map* map = (struct unordered_map*)malloc(sizeof(struct unordered_map));
  map->list = head;
  map->bucket_size = bucket_size;
  map->total_elements = total_elements;
  map->max_load_factor = max_load_factor;

  return map;
}

struct node* find(uint32_t key, struct unordered_map* map) {
  struct node *iter, *first;
  first = map->list;
  for (iter = first; iter != NULL; iter = iter->next) {
    if(iter->data.first == key) return iter;
  }
  return iter;
}

uint32_t hash(const char* key) {
  uint32_t hashed_key = djb33_hash(key);
  return hashed_key;
}

void delete(uint32_t key, struct unordered_map* map) {
  struct node* it = find(key, map);
  if(it != NULL) {
    delete_node(&map->list, key);
    return;
  }
}

void rehash(struct unordered_map* map) {
  if(map->total_elements / map->bucket_size > map->max_load_factor) {
    return;
  }
  map->bucket_size *= 2;
  struct node* new_list = NULL;
  struct node* curr = map->list;
  while(curr != NULL) {
    push_node(&new_list, curr->data.first, curr->data.second);
    curr = curr->next;
  }
  free(map->list);
  map->list = new_list;
}

void insert(const char* val, struct unordered_map* map) {
  struct node* it = find(hash(val), map);
  //value is found, modify the value
  if(it != NULL) {
    it->data.second = val;
    return;
  }
  //does not exist, push to list
  push_node(&map->list, hash(val), val);
  map->total_elements++;
  //rehash if load factor is greater than max load factor
  rehash(map);
}

int main()
{
  struct node* n = create_node(-1,"foo");
  struct unordered_map *map = init_map(n, 1, 1, 1);
  insert("foobar",map);
  insert("foobar",map);
  insert("barfoo",map);
  print_list(map->list);
  return 0;
}
