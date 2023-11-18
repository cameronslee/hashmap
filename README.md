# Simple Hashmap

## Usage
```
// your_file.c
include "hashmap.h"

int main() {
    // create a node
    struct node* n = create_node(-1,"foo"); 

    //create map
    struct unordered_map *map = init_map(n, 1, 1, 1); 

    ...
}

```

## Example
```
$ bash build.sh
```
