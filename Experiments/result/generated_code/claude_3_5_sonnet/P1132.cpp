#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DIGITS 6
#define MAX_QUEUE 1000000

typedef struct {
    int num;
    int steps;
} State;

State queue[MAX_QUEUE];
int front = 0, rear = 0;
bool visited[100000] = {false};

void enqueue(int num, int steps) {
    queue[rear].num = num;
    queue[rear].steps = steps;
    rear = (rear + 1) % MAX_QUEUE;
}

State dequeue() {
    State s = queue[front];
    front = (front + 1) % MAX_QUEUE;
    return s;
}

bool is_empty() {
    return front == rear;
}

int digits[MAX_DIGITS];
int digit_count;

void num_to_digits(int num) {
    digit_count = 0;
    while (num > 0) {
        digits[digit_count++] = num % 10;
        num /= 10;
    }
}

int digits_to_num() {
    int num = 0;
    for (int i = digit_count - 1; i >= 0; i--) {
        num = num * 10 + digits[i];
    }
    return num;
}

int bfs(int start, int target, int max_digits) {
    front = rear = 0;
    memset(visited, 0, sizeof(visited));
    
    enqueue(start, 0);
    visited[start] = true;
    
    while (!is_empty()) {
        State current = dequeue();
        
        if (current.num == target) {
            return current.steps;
        }
        
        num_to_digits(current.num);
        
        // Rule 1: Swap any two digits
        for (int i = 0; i < digit_count; i++) {
            for (int j = i + 1; j < digit_count; j++) {
                int temp = digits[i];
                digits[i] = digits[j];
                digits[j] = temp;
                
                int new_num = digits_to_num();
                if (!visited[new_num]) {
                    enqueue(new_num, current.steps + 1);
                    visited[new_num] = true;
                }
                
                digits[j] = digits[i];
                digits[i] = temp;
            }
        }
        
        // Rule 2: Delete any digit
        for (int i = 0; i < digit_count; i++) {
            int temp = digits[i];
            for (int j = i; j < digit_count - 1; j++) {
                digits[j] = digits[j + 1];
            }
            digit_count--;
            
            int new_num = digits_to_num();
            if (!visited[new_num]) {
                enqueue(new_num, current.steps + 1);
                visited[new_num] = true;
            }
            
            digit_count++;
            for (int j = digit_count - 1; j > i; j--) {
                digits[j] = digits[j - 1];
            }
            digits[i] = temp;
        }
        
        // Rule 3: Insert a digit between two adjacent digits
        if (digit_count < max_digits) {
            for (int i = 0; i < digit_count - 1; i++) {
                for (int x = digits[i] + 1; x < digits[i + 1]; x++) {
                    for (int j = digit_count; j > i + 1; j--) {
                        digits[j] = digits[j - 1];
                    }
                    digits[i + 1] = x;
                    digit_count++;
                    
                    int new_num = digits_to_num();
                    if (!visited[new_num]) {
                        enqueue(new_num, current.steps + 1);
                        visited[new_num] = true;
                    }
                    
                    digit_count--;
                    for (int j = i + 1; j < digit_count; j++) {
                        digits[j] = digits[j + 1];
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