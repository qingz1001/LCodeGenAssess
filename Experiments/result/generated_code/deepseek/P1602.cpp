#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100000

typedef struct {
    int num;
    int mod;
} Node;

Node queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

void enqueue(int num, int mod) {
    queue[rear].num = num;
    queue[rear].mod = mod;
    rear = (rear + 1) % MAX_QUEUE_SIZE;
}

Node dequeue() {
    Node node = queue[front];
    front = (front + 1) % MAX_QUEUE_SIZE;
    return node;
}

int is_empty() {
    return front == rear;
}

int sramoc(int k, int m) {
    int visited[m];
    memset(visited, 0, sizeof(visited));

    for (int i = 1; i < k; i++) {
        int mod = i % m;
        if (mod == 0) return i;
        enqueue(i, mod);
        visited[mod] = 1;
    }

    while (!is_empty()) {
        Node current = dequeue();
        for (int i = 0; i < k; i++) {
            int new_num = current.num * 10 + i;
            int new_mod = (current.mod * 10 + i) % m;
            if (new_mod == 0) return new_num;
            if (!visited[new_mod]) {
                enqueue(new_num, new_mod);
                visited[new_mod] = 1;
            }
        }
    }

    return -1; // Should never reach here
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);
    printf("%d\n", sramoc(k, m));
    return 0;
}