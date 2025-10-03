#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
    float coeff;
    int expo;
    struct node *next;
} node;

node *create_node(float coeff, int expo)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    new_node->coeff = coeff;
    new_node->expo = expo;
    new_node->next = NULL;
    return new_node;
}

void insert_term(node **head, float coeff, int expo)
{
    node *new_term = create_node(coeff, expo);

    if (*head == NULL || (*head)->expo < expo)
    {
        new_term->next = *head;
        *head = new_term;
        return;
    }

    node *current = *head;
    node *prev = NULL;

    while (current != NULL && current->expo > expo)
    {
        prev = current;
        current = current->next;
    }

    if (current != NULL && current->expo == expo)
    {
        current->coeff += coeff;
        free(new_term);
        return;
    }

    new_term->next = current;
    prev->next = new_term;
}

void take_input(node **head)
{
    int num_terms;
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &num_terms);

    for (int i = 0; i < num_terms; ++i)
    {
        float coeff;
        int expo;
        printf("Enter coefficient for term %d: ", i + 1);
        scanf("%f", &coeff);
        printf("Enter exponent for term %d: ", i + 1);
        scanf("%d", &expo);
        insert_term(head, coeff, expo);
    }
}

void display(node *head)
{
    if (head == NULL)
    {
        printf("0\n");
        return;
    }

    node *temp = head;
    int first = 1;
    while (temp != NULL)
    {
        if (temp->coeff != 0)
        {
            if (!first)
            {
                if (temp->coeff > 0)
                    printf(" + ");
                else
                    printf(" ");
            }

            if (fabs(temp->coeff) != 1 || temp->expo == 0)
            {
                printf("%g", temp->coeff);
            }
            else if (temp->coeff == -1)
            {
                printf("-");
            }

            if (temp->expo > 0)
            {
                printf("x");
                if (temp->expo > 1)
                {
                    printf("^%d", temp->expo);
                }
            }
            first = 0;
        }
        temp = temp->next;
    }

    if (first)
    {
        printf("0");
    }
    printf("\n");
}

void free_list(node *head)
{
    while (head != NULL)
    {
        node *temp = head;
        head = head->next;
        free(temp);
    }
}

void add_polynomial(node *head1, node *head2, node **head3)
{
    node *temp1 = head1;
    node *temp2 = head2;

    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->expo == temp2->expo)
        {
            insert_term(head3, temp1->coeff + temp2->coeff, temp1->expo);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if (temp1->expo > temp2->expo)
        {
            insert_term(head3, temp1->coeff, temp1->expo);
            temp1 = temp1->next;
        }
        else
        {
            insert_term(head3, temp2->coeff, temp2->expo);
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL)
    {
        insert_term(head3, temp1->coeff, temp1->expo);
        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        insert_term(head3, temp2->coeff, temp2->expo);
        temp2 = temp2->next;
    }
}

void multiply_polynomial(node *head1, node *head2, node **head4)
{
    if (head1 == NULL || head2 == NULL)
        return;

    node *temp1 = head1;

    while (temp1 != NULL)
    {
        node *temp2 = head2;

        while (temp2 != NULL)
        {
            insert_term(head4, temp1->coeff * temp2->coeff,
                        temp1->expo + temp2->expo);
            temp2 = temp2->next;
        }

        temp1 = temp1->next;
    }
}

int main()
{
    node *head1 = NULL, *head2 = NULL;
    node *result = NULL;

    int choice;

    printf("Polynomial Operations:\n");
    printf("1. Add two polynomials\n");
    printf("2. Multiply two polynomials\n");
    printf("3. Exit\n");

    do
    {
        printf("\nEnter your choice (1/2/3): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nEnter first polynomial:\n");
            take_input(&head1);
            printf("\nEnter second polynomial:\n");
            take_input(&head2);
            add_polynomial(head1, head2, &result);
            printf("\nResultant Polynomial after Addition: ");
            display(result);
            break;

        case 2:
            printf("\nEnter first polynomial:\n");
            take_input(&head1);
            printf("\nEnter second polynomial:\n");
            take_input(&head2);
            multiply_polynomial(head1, head2, &result);
            printf("\nResultant Polynomial after Multiplication: ");
            display(result);
            break;

        case 3:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }

        free_list(head1);
        free_list(head2);
        free_list(result);
        head1 = head2 = result = NULL;

    } while (choice != 3);

    return 0;
}