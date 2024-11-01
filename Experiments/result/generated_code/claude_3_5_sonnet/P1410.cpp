#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 2000

int arr[MAX_N];
int n;

bool can_split() {
    int count1 = 0, count2 = 0;
    int last1 = -1, last2 = -1;
    
    for (int i = 0; i < n; i++) {
        if (count1 < n/2 && arr[i] > last1) {
            last1 = arr[i];
            count1++;
        } else if (count2 < n/2 && arr[i] > last2) {
            last2 = arr[i];
            count2++;
        } else {
            return false;
        }
    }
    
    return true;
}

int main() {
    char line[10000];
    while (fgets(line, sizeof(line), stdin)) {
        n = 0;
        char *token = strtok(line, " \n");
        if (token == NULL) break;
        n = atoi(token);
        
        for (int i = 0; i < n; i++) {
            token = strtok(NULL, " \n");
            if (token == NULL) break;
            arr[i] = atoi(token);
        }
        
        if (can_split()) {
            printf("Yes!\n");
        } else {
            printf("No!\n");
        }
    }
    
    return 0;
}