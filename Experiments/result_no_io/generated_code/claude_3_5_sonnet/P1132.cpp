#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 6
#define MAX_QUEUE 1000000

typedef struct {
    int num;
    int steps;
} State;

State queue[MAX_QUEUE];
int front = 0, rear = 0;
bool visited[100000] = {false};

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int bfs(int start, int target, int max_digits) {
    front = rear = 0;
    memset(visited, false, sizeof(visited));
    
    queue[rear++] = (State){start, 0};
    visited[start] = true;
    
    while (front < rear) {
        State current = queue[front++];
        
        if (current.num == target) {
            return current.steps;
        }
        
        char num_str[MAX_LEN];
        sprintf(num_str, "%d", current.num);
        int len = strlen(num_str);
        
        // Rule 1: Swap digits
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                swap(&num_str[i], &num_str[j]);
                int new_num = atoi(num_str);
                if (!visited[new_num]) {
                    queue[rear++] = (State){new_num, current.steps + 1};
                    visited[new_num] = true;
                }
                swap(&num_str[i], &num_str[j]);
            }
        }
        
        // Rule 2: Delete a digit
        for (int i = 0; i < len; i++) {
            char temp[MAX_LEN];
            int idx = 0;
            for (int j = 0; j < len; j++) {
                if (j != i) {
                    temp[idx++] = num_str[j];
                }
            }
            temp[idx] = '\0';
            int new_num = atoi(temp);
            if (!visited[new_num]) {
                queue[rear++] = (State){new_num, current.steps + 1};
                visited[new_num] = true;
            }
        }
        
        // Rule 3: Insert a digit
        if (len < max_digits) {
            for (int i = 0; i <= len; i++) {
                for (int d = 1; d <= 9; d++) {
                    if ((i == 0 || d > num_str[i-1] - '0') && (i == len || d < num_str[i] - '0')) {
                        char temp[MAX_LEN];
                        strncpy(temp, num_str, i);
                        temp[i] = d + '0';
                        strcpy(temp + i + 1, num_str + i);
                        int new_num = atoi(temp);
                        if (!visited[new_num]) {
                            queue[rear++] = (State){new_num, current.steps + 1};
                            visited[new_num] = true;
                        }
                    }
                }
            }
        }
    }
    
    return -1;
}

int main() {
    int s, m;
    scanf("%d", &s);
    scanf("%d", &m);
    
    int max_digits = 0;
    int temp = s;
    while (temp > 0) {
        max_digits++;
        temp /= 10;
    }
    
    for (int i = 0; i < m; i++) {
        int t;
        scanf("%d", &t);
        printf("%d\n", bfs(s, t, max_digits));
    }
    
    return 0;
}