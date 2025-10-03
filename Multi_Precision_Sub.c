#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Number
{
    int digit;
    struct Number *next;
};

struct Number *head1 = NULL, *tail1 = NULL;
struct Number *head2 = NULL, *tail2 = NULL;
struct Number *head3 = NULL, *tail3 = NULL;

struct Number *newnode(int data)
{
    struct Number *new_node = (struct Number *)malloc(sizeof(struct Number));
    if (!new_node)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    new_node->digit = data;
    new_node->next = NULL;
    return new_node;
}

void insert_term(int data, struct Number **head, struct Number **tail)
{
    struct Number *new_term = newnode(data);
    if (!(*head))
    {
        *head = *tail = new_term;
    }
    else
    {
        new_term->next = *head;
        *head = new_term;
    }
}

struct Number *reverse_list(struct Number *head)
{
    struct Number *prev = NULL;
    while (head)
    {
        struct Number *next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

struct Number *trim_leading_zeros(struct Number *head)
{
    while (head && head->digit == 0)
    {
        struct Number *temp = head;
        head = head->next;
        free(temp);
    }
    return head ? head : newnode(0);
}

void append_zero(int n1, int n2)
{
    int diff = abs(n1 - n2);
    for (int i = 0; i < diff; ++i)
    {
        if (n1 > n2)
            insert_term(0, &head2, &tail2);
        else
            insert_term(0, &head1, &tail1);
    }
}

void subtract_numbers()
{
    int borrow = 0;
    struct Number *temp1 = head1, *temp2 = head2;

    while (temp1 && temp2)
    {
        int diff = (temp1->digit - borrow) - temp2->digit;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        insert_term(diff, &head3, &tail3);
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
}

void display()
{
    struct Number *result = reverse_list(head3);
    result = trim_leading_zeros(result);
    while (result)
    {
        printf("%d", result->digit);
        result = result->next;
    }
    printf("\n");
}

void take_input()
{
    int num1[] = {4, 5};
    int num2[] = {3};
    int n1 = sizeof(num1) / sizeof(num1[0]);
    int n2 = sizeof(num2) / sizeof(num2[0]);

    for (int i = n1 - 1; i >= 0; --i)
        insert_term(num1[i], &head1, &tail1);
    for (int i = n2 - 1; i >= 0; --i)
        insert_term(num2[i], &head2, &tail2);

    if (n1 != n2)
        append_zero(n1, n2);
}

int main()
{
    take_input();
    subtract_numbers();
    display();
    return 0;
}