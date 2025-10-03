#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    int value; // mapped value (frequency or any data)
    struct Node *next;
};

struct HashMap {
    int size;
    struct Node **table;
};

struct Node *createNode(int key, int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode)
        return NULL;

    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// ✅ Create hash map
struct HashMap *createHashMap(int size) {
    struct HashMap *hm = (struct HashMap *)malloc(sizeof(struct HashMap));
    if (!hm)
        return NULL;

    hm->size = size;
    hm->table = (struct Node **)malloc(sizeof(struct Node *) * size);
    if (!hm->table) {
        free(hm);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        hm->table[i] = NULL;
    }

    return hm;
}

// ✅ Hash function
int hashFunction(int key, int size) {
    return (key % size + size) % size; // safe for negatives
}

// ✅ Insert (update if exists)
void insert(struct HashMap *hm, int key, int value) {
    int index = hashFunction(key, hm->size);
    struct Node *temp = hm->table[index];

    if (temp == NULL) {
        hm->table[index] = createNode(key, value);
        return;
    }

    while (temp != NULL) {
        if (temp->key == key) {
            temp->value = value; // update existing key
            return;
        }
        if (temp->next == NULL) {
            temp->next = createNode(key, value); // insert at end
            return;
        }
        temp = temp->next;
    }
}

// ✅ Get value
int get(struct HashMap *hm, int key, int *outValue) {
    int index = hashFunction(key, hm->size);
    struct Node *temp = hm->table[index];

    while (temp != NULL) {
        if (temp->key == key) {
            *outValue = temp->value;
            return 1; // true
        }
        temp = temp->next;
    }
    return 0; // false
}

// ✅ Remove key
int removeKey(struct HashMap *hm, int key) {
    int index = hashFunction(key, hm->size);
    struct Node *temp = hm->table[index];
    struct Node *prev = NULL;

    while (temp != NULL) {
        if (temp->key == key) {
            if (prev == NULL) {
                hm->table[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            return 1; // true
        }
        prev = temp;
        temp = temp->next;
    }
    return 0; // false
}

// ✅ Display hash table
void display(struct HashMap *hm) {
    for (int i = 0; i < hm->size; i++) {
        printf("%d -> ", i);
        struct Node *temp = hm->table[i];
        while (temp != NULL) {
            printf("(%d,%d) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// ✅ Free memory
void freeHashMap(struct HashMap *hm) {
    for (int i = 0; i < hm->size; i++) {
        struct Node *temp = hm->table[i];
        while (temp != NULL) {
            struct Node *nextNode = temp->next;
            free(temp);
            temp = nextNode;
        }
    }
    free(hm->table);
    free(hm);
}

int main() {
    struct HashMap *hm = createHashMap(9);

    insert(hm, 2, 1);
    insert(hm, 5, 2);
    insert(hm, 16, 3);
    insert(hm, 28, 4);
    insert(hm, 139, 5);
    insert(hm, 38, 6);
    insert(hm, 48, 7);
    insert(hm, 28, 8); // updates value for 28
    insert(hm, 18, 9);

    display(hm);

    int key, value;
    printf("Enter key to search: ");
    scanf("%d", &key);
    if (get(hm, key, &value)) {
        printf("Value for key %d is: %d\n", key, value);
    } else {
        printf("Key %d not found!\n", key);
    }

    printf("Enter key to remove: ");
    scanf("%d", &key);
    if (removeKey(hm, key)) {
        printf("Key %d removed successfully!\n", key);
    } else {
        printf("Key %d not found!\n", key);
    }

    display(hm);
    freeHashMap(hm);
    return 0;
}