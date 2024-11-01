#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TARGET "123804765"
#define SIZE 3

typedef struct {
    char state[9];
    int depth;
} Node;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int bfs(char *start) {
    Node queue[100000];
    int front = 0, rear = 0;
    char visited[362880] = {0}; // 9! = 362880

    strcpy(queue[rear].state, start);
    queue[rear].depth = 0;
    rear++;

    while (front < rear) {
        Node current = queue[front++];
        if (strcmp(current.state, TARGET) == 0) {
            return current.depth;
        }

        int zeroPos = -1;
        for (int i = 0; i < 9; i++) {
            if (current.state[i] == '0') {
                zeroPos = i;
                break;
            }
        }

        int x = zeroPos / SIZE;
        int y = zeroPos % SIZE;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                int newPos = nx * SIZE + ny;
                Node next = current;
                next.state[zeroPos] = next.state[newPos];
                next.state[newPos] = '0';
                next.depth++;

                int hash = 0;
                for (int j = 0; j < 9; j++) {
                    hash = hash * 10 + (next.state[j] - '0');
                }

                if (!visited[hash]) {
                    visited[hash] = 1;
                    queue[rear++] = next;
                }
            }
        }
    }

    return -1; // Should never reach here
}

int main() {
    char start[10];
    scanf("%s", start);
    int result = bfs(start);
    printf("%d\n", result);
    return 0;
}