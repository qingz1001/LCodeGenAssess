#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TARGET "123804765"
#define SIZE 3

typedef struct {
    char state[9];
    int zero_pos;
    int steps;
} Node;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int bfs(char *start) {
    Node queue[100000];
    int front = 0, rear = 0;
    Node initial;
    strcpy(initial.state, start);
    initial.zero_pos = strchr(start, '0') - start;
    initial.steps = 0;
    queue[rear++] = initial;

    char visited[1000000] = {0};
    int start_hash = atoi(start);
    visited[start_hash] = 1;

    while (front < rear) {
        Node current = queue[front++];
        if (strcmp(current.state, TARGET) == 0) {
            return current.steps;
        }

        int x = current.zero_pos / SIZE;
        int y = current.zero_pos % SIZE;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                int new_zero_pos = nx * SIZE + ny;
                Node next = current;
                next.state[current.zero_pos] = next.state[new_zero_pos];
                next.state[new_zero_pos] = '0';
                next.zero_pos = new_zero_pos;
                next.steps++;

                int next_hash = atoi(next.state);
                if (!visited[next_hash]) {
                    visited[next_hash] = 1;
                    queue[rear++] = next;
                }
            }
        }
    }
    return -1;
}

int main() {
    char start[10];
    scanf("%s", start);
    int result = bfs(start);
    printf("%d\n", result);
    return 0;
}