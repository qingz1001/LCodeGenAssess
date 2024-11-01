#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10005
#define MAX_M 100005
#define INF 1000000000000000000LL

typedef long long ll;

typedef struct {
    int to;
    ll c;
} Edge;

Edge edges[MAX_M];
int head_nodes[MAX_N];
int next_edges[MAX_M];
int edge_count = 0;

int n, m;
ll b;
int f_fee[MAX_N];

// Heap structure
typedef struct {
    int node;
    ll dist;
} HeapNode;

HeapNode heap_arr[MAX_N];
int heap_size;

ll distance_arr[MAX_N];

// Function to add edge to adjacency list
void add_edge(int a, int b_node, ll c_cost){
    edges[edge_count].to = b_node;
    edges[edge_count].c = c_cost;
    next_edges[edge_count] = head_nodes[a];
    head_nodes[a] = edge_count++;
}

// Heap functions
void swap_heap(int i, int j){
    HeapNode temp = heap_arr[i];
    heap_arr[i] = heap_arr[j];
    heap_arr[j] = temp;
}

void heap_push(int node, ll dist){
    heap_size++;
    heap_arr[heap_size].node = node;
    heap_arr[heap_size].dist = dist;
    int current = heap_size;
    while(current > 1){
        int parent = current / 2;
        if(heap_arr[parent].dist <= heap_arr[current].dist)
            break;
        swap_heap(parent, current);
        current = parent;
    }
}

HeapNode heap_pop(){
    HeapNode top = heap_arr[1];
    heap_arr[1] = heap_arr[heap_size];
    heap_size--;
    int current = 1;
    while(1){
        int left = current * 2;
        int right = current * 2 + 1;
        int smallest = current;
        if(left <= heap_size && heap_arr[left].dist < heap_arr[smallest].dist){
            smallest = left;
        }
        if(right <= heap_size && heap_arr[right].dist < heap_arr[smallest].dist){
            smallest = right;
        }
        if(smallest != current){
            swap_heap(current, smallest);
            current = smallest;
        }
        else{
            break;
        }
    }
    return top;
}

// Dijkstra function
ll dijkstra(int f_limit){
    // Initialize distance array
    for(int i=1;i<=n;i++) distance_arr[i] = INF;
    if(f_fee[1] > f_limit) return INF;
    if(f_fee[n] > f_limit) return INF;
    distance_arr[1] = 0;
    
    // Initialize heap
    heap_size = 0;
    heap_push(1, 0);
    
    while(heap_size > 0){
        HeapNode current = heap_pop();
        int u = current.node;
        ll dist_u = current.dist;
        if(u == n){
            return dist_u;
        }
        if(dist_u > distance_arr[u]){
            continue;
        }
        for(int e = head_nodes[u]; e != -1; e = next_edges[e]){
            int v = edges[e].to;
            ll c = edges[e].c;
            if(f_fee[v] > f_limit){
                continue;
            }
            if(distance_arr[v] > distance_arr[u] + c){
                distance_arr[v] = distance_arr[u] + c;
                heap_push(v, distance_arr[v]);
            }
        }
    }
    return distance_arr[n];
}

int main(){
    // Initialize head_nodes
    for(int i=1;i<=MAX_N;i++) head_nodes[i] = -1;
    
    // Read n, m, b
    if(scanf("%d %d %lld", &n, &m, &b)!=3){
        return 0;
    }
    
    // Read f_i
    for(int i=1;i<=n;i++) {
        if(scanf("%d", &f_fee[i])!=1){
            return 0;
        }
    }
    
    // Read edges
    for(int i=0;i<m;i++){
        int a, b_node;
        ll c_cost;
        if(scanf("%d %d %lld", &a, &b_node, &c_cost)!=3){
            return 0;
        }
        add_edge(a, b_node, c_cost);
        add_edge(b_node, a, c_cost);
    }
    
    // Binary search for the minimal maximum f_i
    // Set low as the max of f[1] and f[n]
    int low = (f_fee[1] > f_fee[n]) ? f_fee[1] : f_fee[n];
    
    // Find the maximum f_i
    int high = f_fee[1];
    for(int i=2;i<=n;i++) if(f_fee[i] > high) high = f_fee[i];
    
    int answer = -1;
    
    while(low <= high){
        int mid = low + (high - low) / 2;
        ll total_loss = dijkstra(mid);
        if(total_loss <= b){
            answer = mid;
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    
    if(answer != -1){
        printf("%d\n", answer);
    }
    else{
        printf("AFK\n");
    }
    
    return 0;
}