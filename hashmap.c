#include "hashmap.h"

/*
djb33_hash
*/
uint32_t djb33_hash(const char* str) {
  uint32_t hash = 5381;
  int c;
  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

/* generic C-string hashing function */
uint32_t str_hash(const char *s)
{
  uint32_t h = 0;

  while (*s) {
    h = h * 31 + *s;
    s++;
  }
  return h;
}

void *get_hash_function(int n) {
  if (n == DJB33) {
    void* hash_function = (void*)&djb33_hash;
    return hash_function;
  }

  return NULL;
}

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

struct hashmap* init_map(struct node* head, int bucket_size, int total_elements, float max_load_factor) {
  struct hashmap* map = (struct hashmap*)malloc(sizeof(struct hashmap));
  map->list = head;
  map->bucket_size = bucket_size;
  map->total_elements = total_elements;
  map->max_load_factor = max_load_factor;

  return map;
}

struct node* find(uint32_t key, struct hashmap* map) {
  struct node *iter, *first;
  first = map->list;
  for (iter = first; iter != NULL; iter = iter->next) {
    if(iter->data.first == key) return iter;
  }
  return iter;
}

uint32_t hash(const char* key, int hash_strategy) {
  void *func_ptr = get_hash_function(hash_strategy);
  uint32_t (*hash_function)(const char*) = (uint32_t (*)(const char*))func_ptr;
  uint32_t hashed_key = hash_function(key);
  return hashed_key;
}

void delete(uint32_t key, struct hashmap* map) {
  struct node* it = find(key, map);
  if(it != NULL) {
    delete_node(&map->list, key);
    return;
  }
}

void rehash(struct hashmap* map) {
  if (map->total_elements / map->bucket_size > map->max_load_factor) {
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

void insert(const char* val, struct hashmap* map, int hash_strategy) {
  struct node* it = find(hash(val, hash_strategy), map);
  //value is found, modify the value
  if(it != NULL) {
    it->data.second = val;
    return;
  }
  //does not exist, push to list
  push_node(&map->list, hash(val, hash_strategy), val);
  map->total_elements++;
  //rehash if load factor is greater than max load factor
  rehash(map);
}

void teardown(struct hashmap *map) {
  free(map->list);
  free(map);
}

