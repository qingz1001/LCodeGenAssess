#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int cantor(int *arr, int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        int smaller = 0;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[i]) {
                smaller++;
            }
        }
        result += smaller * factorial(n - i - 1);
    }
    return result + 1;
}

void decantor(int *arr, int n, int k) {
    int used[10001] = {0};
    k--;
    for (int i = 0; i < n; i++) {
        int factorial_value = factorial(n - i - 1);
        int index = k / factorial_value;
        k %= factorial_value;
        
        int count = 0;
        for (int j = 1; j <= n; j++) {
            if (!used[j]) {
                if (count == index) {
                    arr[i] = j;
                    used[j] = 1;
                    break;
                }
                count++;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    
    int arr[10000];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int current = cantor(arr, n);
    int next = current + m;
    
    decantor(arr, n, next);
    
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    
    return 0;
}