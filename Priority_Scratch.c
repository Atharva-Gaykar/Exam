#include <stdio.h>
#include <stdlib.h>

typedef struct Priority_que {
    int priority;
    int data;
    struct Priority_que *next;
} node;

node *front = NULL;
node *rear = NULL;

node *newnode(int data, int priority) {
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
        return NULL;

    new_node->data = data;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

void enqueue(int data, int priority) {
    node *new_node = newnode(data, priority);
    if (!new_node)
        return;

    if (front == NULL || priority < front->priority) {
        new_node->next = front;
        front = new_node;
        if (rear == NULL)
            rear = new_node;
        return;
    }

    node *temp = front;
    node *prev = NULL;

    while (temp != NULL && temp->priority <= priority) {
        prev = temp;
        temp = temp->next;
    }

    new_node->next = temp;
    prev->next = new_node;

    if (new_node->next == NULL) {
        rear = new_node;
    }
}

void dequeue() {
    if (front == NULL)
        return;

    node *temp = front;
    front = front->next;
    free(temp);

    if (front == NULL)
        rear = NULL;
}

void display() {
    node *temp = front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    enqueue(40, 4);
    enqueue(50, 6);
    enqueue(60, 2);
    enqueue(30, 1);
    enqueue(20, 3);
    enqueue(10, 5);

    printf("Queue after enqueues: ");
    display();

    dequeue();

    printf("Queue after one dequeue: ");
    display();

    return 0;
}