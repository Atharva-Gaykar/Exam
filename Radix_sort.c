#include <stdio.h>

void count_sort(int *arr, int n, int pos)
{
    int count[10] = {0};

    
    for (int i = 0; i < n; i++)
    {
        count[(arr[i] / pos) % 10]++;
    }

    int temp[n];

    
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

   
    for (int i = n - 1; i >= 0; i--)
    {
        temp[--count[(arr[i] / pos) % 10]] = arr[i];
    }

    // Copy back
    for (int i = 0; i < n; i++)
    {
        arr[i] = temp[i];
    }
}

int get_max(int *arr, int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

void radix_sort(int *arr, int n)
{
    int max = get_max(arr, n);

    for (int pos = 1; max / pos > 0; pos *= 10)
    {
        count_sort(arr, n, pos);
    }
}

int main()
{
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    radix_sort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}