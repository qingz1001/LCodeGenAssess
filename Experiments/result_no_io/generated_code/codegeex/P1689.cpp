#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char equation[1000001];
    fgets(equation, sizeof(equation), stdin);
    int length = strlen(equation);
    
    int x, y, z;
    int question_mark_index;
    char operation;
    
    // Find the position of '?' and the operation
    for (int i = 0; i < length; i++) {
        if (equation[i] == '?') {
            question_mark_index = i;
            break;
        }
    }
    
    if (equation[question_mark_index - 1] == '+') {
        operation = '+';
    } else {
        operation = '-';
    }
    
    // Remove spaces
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (equation[i] != ' ') {
            equation[j++] = equation[i];
        }
    }
    equation[j] = '\0';
    length = j;
    
    // Parse numbers
    int num;
    char *ptr = equation;
    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            num = atoi(ptr);
        } else if (i == 1) {
            ptr = strchr(ptr, operation);
            ptr++;
            num = atoi(ptr);
        } else if (i == 2) {
            ptr = strchr(ptr, operation);
            ptr++;
            num = atoi(ptr);
        }
        if (i == question_mark_index / 2 - 1) {
            if (operation == '+') {
                z = num - x;
            } else {
                z = x - num;
            }
            printf("%d\n", z);
            return 0;
        } else if (i == (question_mark_index + 1) / 2 - 1) {
            if (operation == '+') {
                x = num - z;
            } else {
                x = z - num;
            }
        } else if (i == (question_mark_index + 2) / 2 - 1) {
            if (operation == '+') {
                y = z - x;
            } else {
                y = x - z;
            }
        }
    }
    return 0;
}