#include "string_map.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool expandMap(StringMap *map) {
    printf("Expanding from: %d to: %d\n", map->capacity, map->capacity * 2);
    map->capacity *= 2;
    char **newKeys = realloc(map->keys, map->capacity * sizeof(char *));
    if (!newKeys) return false;
    map->keys = newKeys;
    return true;
}

StringMap *StringMap_create(const int initialCapacity, const int maxKeySize) {
    StringMap *map = malloc(sizeof(StringMap));
    if (!map) {
        perror("Failed to allocate StringMap");
        return NULL;
    }
    map->keys = malloc(initialCapacity * sizeof(char *));
    if (!map->keys) {
        perror("Failed to allocate StringMap.keys");
        free(map);
        return NULL;
    }

    map->capacity = initialCapacity;
    map->keysCount = 0;
    map->maxKeySize = maxKeySize;
    return map;
}

int StringMap_insert(StringMap *map, char key[]) {
    const int currentIndex = map->keysCount;
    if (currentIndex >= map->capacity) {
        expandMap(map);
    }
    char *newEntry = map->keys[currentIndex] = malloc(sizeof(char) * map->maxKeySize);
    if (!newEntry) {
        return -1;
    }
    strcpy(newEntry, key);
    map->keysCount++;
    return currentIndex;
}

int StringMap_getIndex(const StringMap *map, char key[]) {
    for (int i = 0; i < map->keysCount; i++) {
        if (strcmp(map->keys[i], key) == 0) {
            return i;
        }
    }
    return -1;
}

void StringMap_destroy(StringMap *map) {
    for (int i = 0; i < map->keysCount; i++) {
        free(map->keys[i]);
    }
    free(map->keys);
    free(map);
}
