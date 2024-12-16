#ifndef STRING_MAP_H
#define STRING_MAP_H

typedef struct {
    char **keys;
    int keysCount;
    int capacity;
    int maxKeySize;
} StringMap;

StringMap *StringMap_create(int initialCapacity, const int maxKeySize);

int StringMap_insert(StringMap *map, char key[]);

int StringMap_getIndex(const StringMap *map, char key[]);

void StringMap_destroy(StringMap *map);


#endif //STRING_MAP_H
