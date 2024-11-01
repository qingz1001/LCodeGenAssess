#include <stdio.h>

int main() {
    int task;
    scanf("%d", &task);
    
    if(task == 1) {
        printf("I\n");  // 1
        printf("I\n");  // 2
        printf("+ 1 2\n");  // 3
        printf("< 3 1\n");  // 4
        printf("- 4\n");  // 5
        printf("O 5\n");  // 6
    }
    
    return 0;
}