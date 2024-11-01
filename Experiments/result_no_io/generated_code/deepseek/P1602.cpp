#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_M 1000

typedef struct {
    int num;
    int remainder;
} State;

int sramoc(int k, int m) {
    bool visited[MAX_M] = {false};
    State queue[MAX_M * 10];
    int front = 0, rear = 0;

    for (int i = 1; i < k; i++) {
        int remainder = i % m;
        if (!visited[remainder]) {
            visited[remainder] = true;
            queue[rear].num = i;
            queue[rear].remainder = remainder;
            rear++;
        }
    }

    while (front < rear) {
        State current = queue[front++];
        if (current.remainder == 0) {
            return current.num;
        }

        for (int i = 0; i < k; i++) {
            int new_num = current.num * 10 + i;
            int new_remainder = (current.remainder * 10 + i) % m;
            if (!visited[new_remainder]) {
                visited[new_remainder] = true;
                queue[rear].num = new_num;
                queue[rear].remainder = new_remainder;
                rear++;
            }
        }
    }

    return -1; // This should never happen with valid input
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);
    printf("%d\n", sramoc(k, m));
    return 0;
}