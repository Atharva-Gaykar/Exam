#include <stdio.h>
#include <stdlib.h>

typedef struct Number {
    int digit;
    struct Number* next;
} Number;

Number *head1 = NULL;
Number *head2 = NULL;
Number *head3 = NULL;

Number* newnode(int data) {
    Number* new_node = (Number*)malloc(sizeof(Number));
    new_node->digit = data;
    new_node->next = NULL;
    return new_node;
}

void insert_head(int data, Number** head) {
    Number* new_term = newnode(data);
    new_term->next = *head;
    *head = new_term;
}

int get_length(Number* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

void pad_zeros(Number** head, int count) {
    for (int i = 0; i < count; i++) {
        insert_head(0, head);
    }
}

// now insert digits from RIGHT to LEFT (so list is stored correctly)
void take_input() {
    int num1[] = {4, 0}; // 40
    int num2[] = {3};    // 9

    int n1 = sizeof(num1) / sizeof(num1[0]);
    int n2 = sizeof(num2) / sizeof(num2[0]);

    // insert from last digit to first digit
    for (int i = n1 - 1; i >= 0; --i)
        insert_head(num1[i], &head1);

    for (int i = n2 - 1; i >= 0; --i)
        insert_head(num2[i], &head2);

    if (n1 > n2)
        pad_zeros(&head2, n1 - n2);
    else if (n2 > n1)
        pad_zeros(&head1, n2 - n1);
}

void do_sum() {
    Number *temp1 = head1, *temp2 = head2;
    int carry = 0;

    while (temp1 && temp2) {
        int sum = temp1->digit + temp2->digit + carry;
        carry = sum / 10;
        insert_head(sum % 10, &head3);
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    if (carry)
        insert_head(carry, &head3);
}

void display_reverse(Number* head) {

    if (head == NULL)
        return;
    display_reverse(head->next);
    printf("%d", head->digit);
    
}

int main() {
    take_input();
    do_sum();
    printf("Sum: ");
    display_reverse(head3);
    return 0;
}
