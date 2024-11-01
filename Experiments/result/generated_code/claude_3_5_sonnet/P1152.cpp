#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 1000

bool isJolly(int arr[], int n) {
    bool diff[MAX_N] = {false};
    
    for (int i = 1; i < n; i++) {
        int d = abs(arr[i] - arr[i-1]);
        if (d == 0 || d >= n || diff[d]) {
            return false;
        }
        diff[d] = true;
    }
    
    for (int i = 1; i < n; i++) {
        if (!diff[i]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int n;
    int arr[MAX_N];
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    if (isJolly(arr, n)) {
        printf("Jolly\n");
    } else {
        printf("Not jolly\n");
    }
    
    return 0;
}