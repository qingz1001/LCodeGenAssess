#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int A;
    int B;
    int C;
} Recipe;

typedef struct {
    int *recipes;
    int size;
    int capacity;
} RecipeList;

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

void add_recipe_list(RecipeList *list, int recipe_idx) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity ? list->capacity * 2 : 4;
        list->recipes = realloc(list->recipes, list->capacity * sizeof(int));
        if (!list->recipes) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }
    list->recipes[list->size++] = recipe_idx;
}

Queue create_queue(int initial_capacity) {
    Queue q;
    q.data = (int *)malloc(initial_capacity * sizeof(int));
    if (!q.data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    q.front = 0;
    q.rear = 0;
    q.size = 0;
    q.capacity = initial_capacity;
    return q;
}

void enqueue(Queue *q, int x) {
    if (q->size == q->capacity) {
        q->capacity *= 2;
        q->data = realloc(q->data, q->capacity * sizeof(int));
        if (!q->data) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }
    q->data[q->rear++] = x;
    if (q->rear == q->capacity) {
        q->rear = 0;
    }
    q->size++;
}

int dequeue(Queue *q) {
    int x = q->data[q->front++];
    if (q->front == q->capacity) {
        q->front = 0;
    }
    q->size--;
    return x;
}

int is_empty(Queue *q) {
    return q->size == 0;
}

int main(){
    int N;
    if(scanf("%d", &N)!=1){
        return 0;
    }
    int *prices = (int *)malloc(N * sizeof(int));
    for(int i=0;i<N;i++){
        if(scanf("%d", &prices[i])!=1){
            return 0;
        }
    }
    // Initialize recipes
    int max_recipes = 1000000;
    Recipe *recipes = (Recipe *)malloc(max_recipes * sizeof(Recipe));
    int M = 0;
    // Initialize recipes_of
    RecipeList *recipes_of = (RecipeList *)calloc(N, sizeof(RecipeList));
    // Read remaining lines
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin); // consume the newline after prices
    while(fgets(buffer, sizeof(buffer), stdin)){
        if(buffer[0] == '\n') break;
        int A, B, C;
        if(sscanf(buffer, "%d %d %d", &A, &B, &C)!=3){
            continue;
        }
        if(M >= max_recipes){
            max_recipes *=2;
            recipes = realloc(recipes, max_recipes * sizeof(Recipe));
            if(!recipes){
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
        }
        recipes[M].A = A;
        recipes[M].B = B;
        recipes[M].C = C;
        add_recipe_list(&recipes_of[A], M);
        add_recipe_list(&recipes_of[B], M);
        M++;
    }
    // Initialize cost and ways
    unsigned long long *cost = (unsigned long long *)malloc(N * sizeof(unsigned long long));
    unsigned long long *ways = (unsigned long long *)malloc(N * sizeof(unsigned long long));
    for(int i=0;i<N;i++){
        cost[i] = (unsigned long long)prices[i];
        ways[i] = 1;
    }
    // Initialize queue with all potions
    Queue q = create_queue(N);
    for(int i=0;i<N;i++){
        enqueue(&q, i);
    }
    while(!is_empty(&q)){
        int P = dequeue(&q);
        for(int i=0;i<recipes_of[P].size;i++){
            int recipe_idx = recipes_of[P].recipes[i];
            int A = recipes[recipe_idx].A;
            int B = recipes[recipe_idx].B;
            int C = recipes[recipe_idx].C;
            unsigned long long new_cost = cost[A] + cost[B];
            if(new_cost < cost[C]){
                cost[C] = new_cost;
                ways[C] = ways[A] * ways[B];
                enqueue(&q, C);
            }
            else if(new_cost == cost[C]){
                ways[C] += ways[A] * ways[B];
            }
        }
    }
    printf("%llu %llu\n", cost[0], ways[0]);
    // Free memory
    free(prices);
    free(recipes);
    for(int i=0;i<N;i++){
        free(recipes_of[i].recipes);
    }
    free(recipes_of);
    free(cost);
    free(ways);
    free(q.data);
    return 0;
}