#include <stdio.h>
#include <stdlib.h>

// Maximum number of nodes
#define MAXN 100005
// Maximum possible s[x] values range from -100000 to 100000
#define OFFSET 100000
#define S_RANGE 200001

typedef struct Edge {
    int to;
    int type;
    struct Edge* next;
} Edge;

// Adjacency list
Edge* adj[MAXN];

// Function to add edge to adjacency list
void add_edge(int from, int to, int type) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = to;
    edge->type = type;
    edge->next = adj[from];
    adj[from] = edge;
}

// List structure to hold in-times for each s[x]
typedef struct {
    int* arr;
    int size;
    int capacity;
} List;

// Initialize a list
void init_list(List* list) {
    list->capacity = 4;
    list->size = 0;
    list->arr = (int*)malloc(list->capacity * sizeof(int));
}

// Add element to list
void add_to_list(List* list, int val) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->arr = (int*)realloc(list->arr, list->capacity * sizeof(int));
    }
    list->arr[list->size++] = val;
}

// Arrays to store traversal info
int in_time[MAXN];
int out_time[MAXN];
int s_val[MAXN];
int time_counter = 0;

// DFS to assign in and out times and compute s[x]
void dfs(int u, int parent, int current_s, List s_lists[]) {
    in_time[u] = time_counter;
    s_val[u] = current_s;
    add_to_list(&s_lists[current_s + OFFSET], time_counter);
    time_counter++;

    Edge* edge = adj[u];
    while (edge != NULL) {
        int v = edge->to;
        if (v != parent) {
            int new_s = current_s + (edge->type == 0 ? 1 : -1);
            dfs(v, u, new_s, s_lists);
        }
        edge = edge->next;
    }
    out_time[u] = time_counter;
}

// Binary search lower bound
int lower_bound_func(int* arr, int size, int target) {
    int left = 0, right = size;
    while (left < right) {
        int mid = left + (right - left)/2;
        if (arr[mid] < target)
            left = mid +1;
        else
            right = mid;
    }
    return left;
}

// Binary search upper bound
int upper_bound_func(int* arr, int size, int target) {
    int left = 0, right = size;
    while (left < right) {
        int mid = left + (right - left)/2;
        if (arr[mid] <= target)
            left = mid +1;
        else
            right = mid;
    }
    return left;
}

int main(){
    int N;
    scanf("%d", &N);

    // Read edges and build adjacency list
    for(int i=0;i<N-1;i++){
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        add_edge(a, b, t);
        add_edge(b, a, t);
    }

    // Initialize lists
    List s_lists[S_RANGE];
    for(int i=0;i<S_RANGE;i++){
        init_list(&s_lists[i]);
    }

    // Start DFS from node 1 with s=0
    dfs(1, -1, 0, s_lists);

    long long total_paths = 0;

    // For each node, count number of nodes in its subtree with s[u] = s[x]
    for(int u=1; u<=N; u++){
        int s = s_val[u] + OFFSET;
        List current_list = s_lists[s];
        if(current_list.size ==0){
            continue;
        }
        // Find number of in_times in [in[u], out[u])
        int lb = lower_bound_func(current_list.arr, current_list.size, in_time[u]);
        int ub = upper_bound_func(current_list.arr, current_list.size, out_time[u]-1);
        int count = ub - lb -1; // exclude the node itself
        if(count >=2){
            total_paths += ((long long)count * (count -1)) /2;
        }
    }

    printf("%lld\n", total_paths);
    return 0;
}