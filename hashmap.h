#include <stdio.h>
#include <stdlib.h>

#define DJB33 0
#define GENERIC 1

/*
djb33_hash
*/
uint32_t djb33_hash(const char* str);

uint32_t str_hash(const char *s);

struct pair {
  uint32_t first;
  const char * second;
};

struct node {
  struct pair data;
  struct node* next;
};

struct hashmap {
  struct node* list;
  int bucket_size;
  int total_elements;
  float max_load_factor; //default 1
};

void *get_hash_function(int n);

struct node* create_node(uint32_t first, const char* second);

void push_node(struct node** head, uint32_t key, const char* value);

void delete_node(struct node** head, uint32_t key);

void print_list(struct node* head);

struct hashmap* init_map(struct node* head, int bucket_size, int total_elements, float max_load_factor);

struct node* find(uint32_t key, struct hashmap* map);

uint32_t hash(const char* key, int hash_strategy); 

void delete(uint32_t key, struct hashmap* map);

void rehash(struct hashmap* map);

void insert(const char* val, struct hashmap* map, int hash_strategy);

void teardown(struct hashmap *map);
