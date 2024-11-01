#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 1000000
#define TARGET "123804765"

typedef struct {
    char board[9];
    int zero_pos;
    int depth;
} State;

typedef struct {
    State data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void init_queue(Queue *queue) {
    queue->front = 0;
    queue->rear = 0;
}

int is_empty(Queue *queue) {
    return queue->front == queue->rear;
}

int is_full(Queue *queue) {
    return (queue->rear + 1) % MAX_QUEUE_SIZE == queue->front;
}

void enqueue(Queue *queue, State state) {
    if (is_full(queue)) {
        printf("Queue is full\n");
        exit(1);
    }
    queue->data[queue->rear] = state;
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
}

State dequeue(Queue *queue) {
    if (is_empty(queue)) {
        printf("Queue is empty\n");
        exit(1);
    }
    State state = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    return state;
}

int is_target(State state) {
    return strcmp(state.board, TARGET) == 0;
}

void move(Queue *queue, State state, int dir) {
    State new_state = state;
    int zero_pos = state.zero_pos;
    int new_pos = zero_pos + dir;
    char temp = new_state.board[zero_pos];
    new_state.board[zero_pos] = new_state.board[new_pos];
    new_state.board[new_pos] = temp;
    new_state.zero_pos = new_pos;
    new_state.depth = state.depth + 1;
    enqueue(queue, new_state);
}

int main() {
    char initial[9];
    scanf("%s", initial);

    Queue queue;
    init_queue(&queue);

    State initial_state;
    strncpy(initial_state.board, initial, 9);
    initial_state.zero_pos = strchr(initial_state.board, '0') - initial_state.board;
    initial_state.depth = 0;
    enqueue(&queue, initial_state);

    while (!is_empty(&queue)) {
        State current_state = dequeue(&queue);
        if (is_target(current_state)) {
            printf("%d\n", current_state.depth);
            return 0;
        }

        int zero_pos = current_state.zero_pos;
        if (zero_pos % 3 != 0) { // Can move left
            move(&queue, current_state, -1);
        }
        if (zero_pos % 3 != 2) { // Can move right
            move(&queue, current_state, 1);
        }
        if (zero_pos / 3 != 0) { // Can move up
            move(&queue, current_state, -3);
        }
        if (zero_pos / 3 != 2) { // Can move down
            move(&queue, current_state, 3);
        }
    }

    printf("No solution found\n");
    return 0;
}