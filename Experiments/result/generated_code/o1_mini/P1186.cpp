#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001
#define MAXM 500000
#define MAXA 1000000
#define INF 1000000000

int A_arr[MAXM];
int B_arr[MAXM];
int V_arr[MAXM];
int degrees[MAXN];
int starts_arr[MAXN+1];
int next_cnt_arr[MAXN];
int graph_to[MAXA];
int graph_weight[MAXA];
int graph_id[MAXA];
char on_shortest_path_flag[MAXM];
int E_shortest_path[MAXA];
int E_cnt = 0;

// Heap structures
int heap_nodes[MAXN];
int heap_dists[MAXN];
int heap_size;

// Distance and visited arrays
int dist_arr[MAXN];
char visited_arr[MAXN];

// Dijkstra function
int Dijkstra(int source, int target, int blocked_eid, int N_nodes) {
    for(int i = 1; i <= N_nodes; i++) {
        dist_arr[i] = INF;
        visited_arr[i] = 0;
    }
    dist_arr[source] = 0;
    heap_size = 1;
    heap_nodes[0] = source;
    heap_dists[0] = 0;

    while(heap_size > 0){
        // Pop the top of the heap
        int u = heap_nodes[0];
        int d = heap_dists[0];
        
        // Replace top with last element
        heap_size--;
        if(heap_size > 0){
            heap_nodes[0] = heap_nodes[heap_size];
            heap_dists[0] = heap_dists[heap_size];
            
            // Sift down
            int pos = 0;
            while(1){
                int left = 2*pos +1;
                int right = 2*pos +2;
                int smallest = pos;
                if(left < heap_size && heap_dists[left] < heap_dists[smallest]){
                    smallest = left;
                }
                if(right < heap_size && heap_dists[right] < heap_dists[smallest]){
                    smallest = right;
                }
                if(smallest == pos){
                    break;
                }
                // Swap
                int temp_node = heap_nodes[pos];
                int temp_dist = heap_dists[pos];
                heap_nodes[pos] = heap_nodes[smallest];
                heap_dists[pos] = heap_dists[smallest];
                heap_nodes[smallest] = temp_node;
                heap_dists[smallest] = temp_dist;
                pos = smallest;
            }
        }

        if(visited_arr[u]){
            continue;
        }
        visited_arr[u] = 1;
        if(u == target){
            return d;
        }
        for(int k = starts_arr[u]; k < starts_arr[u+1]; k++){
            int v = graph_to[k];
            int w = graph_weight[k];
            int eid = graph_id[k];
            if(eid == blocked_eid){
                continue;
            }
            if(d + w < dist_arr[v]){
                dist_arr[v] = d + w;
                // Push to heap
                int pos = heap_size;
                heap_nodes[pos] = v;
                heap_dists[pos] = dist_arr[v];
                heap_size++;
                // Sift up
                while(pos > 0){
                    int parent = (pos -1)/2;
                    if(heap_dists[parent] <= heap_dists[pos]){
                        break;
                    }
                    // Swap
                    int temp_node = heap_nodes[parent];
                    int temp_dist = heap_dists[parent];
                    heap_nodes[parent] = heap_nodes[pos];
                    heap_dists[parent] = heap_dists[pos];
                    heap_nodes[pos] = temp_node;
                    heap_dists[pos] = temp_dist;
                    pos = parent;
                }
            }
        }
    }
    return dist_arr[target];
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    for(int e = 0; e < M; e++){
        scanf("%d %d %d", &A_arr[e], &B_arr[e], &V_arr[e]);
        degrees[A_arr[e]]++;
        degrees[B_arr[e]]++;
    }
    starts_arr[1] = 0;
    for(int i = 2; i <= N; i++){
        starts_arr[i] = starts_arr[i-1] + degrees[i-1];
    }
    starts_arr[N+1] = starts_arr[N] + degrees[N];
    memset(next_cnt_arr, 0, sizeof(next_cnt_arr));
    for(int e = 0; e < M; e++){
        int u = A_arr[e];
        int v = B_arr[e];
        int w = V_arr[e];
        int pos = starts_arr[u] + next_cnt_arr[u]++;
        graph_to[pos] = v;
        graph_weight[pos] = w;
        graph_id[pos] = e;
        pos = starts_arr[v] + next_cnt_arr[v]++;
        graph_to[pos] = u;
        graph_weight[pos] = w;
        graph_id[pos] = e;
    }
    // Dijkstra from N
    int dist_N[MAXN];
    for(int i = 1; i <= N; i++) dist_arr[i] = INF;
    // Temporarily block no edge
    int D = Dijkstra(N, 1, -1, N);
    // Dijkstra from 1
    // To get dist_1, we need to run Dijkstra from 1
    // Temporarily modify the adjacency to run Dijkstra from 1
    // Swap source and target
    for(int i = 1; i <= N; i++) dist_arr[i] = INF;
    // Reset heap
    heap_size = 1;
    heap_nodes[0] = 1;
    heap_dists[0] = 0;
    dist_arr[1] = 0;
    while(heap_size > 0){
        int u = heap_nodes[0];
        int d = heap_dists[0];
        heap_size--;
        if(heap_size > 0){
            heap_nodes[0] = heap_nodes[heap_size];
            heap_dists[0] = heap_dists[heap_size];
            // Sift down
            int pos = 0;
            while(1){
                int left = 2*pos +1;
                int right = 2*pos +2;
                int smallest = pos;
                if(left < heap_size && heap_dists[left] < heap_dists[smallest]){
                    smallest = left;
                }
                if(right < heap_size && heap_dists[right] < heap_dists[smallest]){
                    smallest = right;
                }
                if(smallest == pos){
                    break;
                }
                // Swap
                int temp_node = heap_nodes[pos];
                int temp_dist = heap_dists[pos];
                heap_nodes[pos] = heap_nodes[smallest];
                heap_dists[pos] = heap_dists[smallest];
                heap_nodes[smallest] = temp_node;
                heap_dists[smallest] = temp_dist;
                pos = smallest;
            }
        }
        if(visited_arr[u]){
            continue;
        }
        visited_arr[u] = 1;
        for(int k = starts_arr[u]; k < starts_arr[u+1]; k++){
            int v = graph_to[k];
            int w = graph_weight[k];
            if(d + w < dist_arr[v]){
                dist_arr[v] = d + w;
                // Push to heap
                int pos = heap_size;
                heap_nodes[pos] = v;
                heap_dists[pos] = dist_arr[v];
                heap_size++;
                // Sift up
                while(pos > 0){
                    int parent = (pos -1)/2;
                    if(heap_dists[parent] <= heap_dists[pos]){
                        break;
                    }
                    // Swap
                    int temp_node = heap_nodes[parent];
                    int temp_dist = heap_dists[parent];
                    heap_nodes[parent] = heap_nodes[pos];
                    heap_dists[parent] = heap_dists[pos];
                    heap_nodes[pos] = temp_node;
                    heap_dists[pos] = temp_dist;
                    pos = parent;
                }
            }
        }
    }
    int dist_1[MAXN];
    for(int i = 1; i <= N; i++) dist_1[i] = dist_arr[i];
    // Now, identify edges on some shortest path
    for(int e = 0; e < M; e++){
        int u = A_arr[e];
        int v = B_arr[e];
        int w = V_arr[e];
        if(dist_N[u] + w + dist_1[v] == D || dist_N[v] + w + dist_1[u] == D){
            on_shortest_path_flag[e] = 1;
            E_shortest_path[E_cnt++] = e;
        }
        else{
            on_shortest_path_flag[e] = 0;
        }
    }
    // Now, iterate over E_shortest_path and find max D_e
    int max_D_e = 0;
    for(int i = 0; i < E_cnt; i++){
        int e = E_shortest_path[i];
        int new_D = Dijkstra(N, 1, e, N);
        if(new_D > max_D_e){
            max_D_e = new_D;
        }
    }
    printf("%d\n", max_D_e);
    return 0;
}