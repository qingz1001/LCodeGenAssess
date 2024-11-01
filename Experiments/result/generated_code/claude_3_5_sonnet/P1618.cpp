#include <stdio.h>
#include <stdbool.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool is_valid(int a, int b, int c, int A, int B, int C) {
    return (b * A == a * B) && (c * A == a * C);
}

void generate_permutations(int arr[], int start, int end, int A, int B, int C, bool *found) {
    if (start == end) {
        int num1 = arr[0] * 100 + arr[1] * 10 + arr[2];
        int num2 = arr[3] * 100 + arr[4] * 10 + arr[5];
        int num3 = arr[6] * 100 + arr[7] * 10 + arr[8];
        
        if (is_valid(num1, num2, num3, A, B, C)) {
            printf("%d %d %d\n", num1, num2, num3);
            *found = true;
        }
        return;
    }
    
    for (int i = start; i <= end; i++) {
        swap(&arr[start], &arr[i]);
        generate_permutations(arr, start + 1, end, A, B, C, found);
        swap(&arr[start], &arr[i]);
    }
}

int main() {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);
    
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    bool found = false;
    
    generate_permutations(numbers, 0, 8, A, B, C, &found);
    
    if (!found) {
        printf("No!!!\n");
    }
    
    return 0;
}