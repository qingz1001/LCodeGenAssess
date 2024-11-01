#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    
    char children[105][21];
    for (int i = 0; i < n; i++) {
        scanf("%s", children[i]);
    }
    
    int count = 0;
    int taken_by_child[105] = {0};
    int total_taken = 0;
    
    for (int i = 0; i < n; i++) {
        taken_by_child[i]++;
        total_taken++;
        
        int current_child_taken = taken_by_child[i] - 1;
        int other_children_taken = total_taken - taken_by_child[i];
        
        if (current_child_taken > other_children_taken) {
            count++;
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}