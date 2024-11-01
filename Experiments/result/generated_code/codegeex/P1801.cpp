#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int length;
} Queue;

Queue *createQueue() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->head = queue->tail = NULL;
    queue->length = 0;
    return queue;
}

void enqueue(Queue *queue, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    if (queue->tail == NULL) {
        queue->head = queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    queue->length++;
}

int dequeue(Queue *queue) {
    if (queue->head == NULL) {
        return -1;
    }
    Node *temp = queue->head;
    int value = temp->value;
    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    free(temp);
    queue->length--;
    return value;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int a[m];
    int u[n];
    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &u[i]);
    }

    Queue *queue = createQueue();
    int i = 0;
    int get_count = 0;
    int get_index = u[get_count];

    while (i < m) {
        enqueue(queue, a[i]);
        i++;
        if (i == get_index) {
            int value = dequeue(queue);
            printf("%d\n", value);
            get_count++;
            if (get_count < n) {
                get_index = u[get_count];
            }
        }
    }

    return 0;
}