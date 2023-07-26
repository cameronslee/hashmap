#include "hashes.h"
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
