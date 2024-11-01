#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5001
#define MAXK 1000
#define MAXH 500
#define MAXEDGE 10000

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[2 * MAXEDGE];
int head_nodes[MAXN];
int edge_count = 0;

void add_edge(int a, int b){
    edges[edge_count].to = b;
    edges[edge_count].next = head_nodes[a];
    head_nodes[a] = edge_count++;
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<2*n;i++) head_nodes[i] = -1;
    for(int i=0;i<n-1;i++){
        int a,b;
        scanf("%d %d", &a, &b);
        add_edge(a,b);
        add_edge(b,a);
    }
    int k;
    scanf("%d", &k);
    int pos[MAXK];
    for(int i=0;i<k;i++) scanf("%d", &pos[i]);
    int h;
    scanf("%d", &h);
    int food[MAXH];
    for(int i=0;i<h;i++) scanf("%d", &food[i]);
    int count_eat[MAXK];
    memset(count_eat, 0, sizeof(count_eat));
    
    // Temporary arrays for BFS
    int distance_arr[MAXN];
    int parent[MAXN];
    int queue[MAXN];
    
    for(int fi=0; fi<h; fi++){
        int t = food[fi];
        // BFS from t
        for(int i=1;i<=n;i++) {
            distance_arr[i] = -1;
            parent[i] = -1;
        }
        int front =0, back=0;
        queue[back++] = t;
        distance_arr[t] = 0;
        while(front < back){
            int u = queue[front++];
            for(int e = head_nodes[u]; e != -1; e = edges[e].next){
                int v = edges[e].to;
                if(distance_arr[v]==-1){
                    distance_arr[v] = distance_arr[u] +1;
                    parent[v] = u;
                    queue[back++] = v;
                }
            }
        }
        // Check if any worm is already at t
        int eater = -1;
        for(int i=0;i<k;i++) {
            if(pos[i] == t){
                if(eater == -1 || i < eater){
                    eater = i;
                }
            }
        }
        if(eater != -1){
            count_eat[eater]++;
            // No movement, other worms stay
            continue;
        }
        // Initialize occupied
        char occupied[MAXN];
        memset(occupied, 0, sizeof(occupied));
        for(int i=0;i<k;i++) occupied[pos[i]] = 1;
        // Initialize moving worms
        char moving[MAXK];
        memset(moving, 0, sizeof(moving));
        for(int i=0;i<k;i++) if(pos[i] != t) moving[i] = 1;
        while(1){
            // Intended moves
            int intended_node[MAXK];
            memset(intended_node, -1, sizeof(intended_node));
            for(int i=0;i<k;i++) {
                if(moving[i]){
                    if(parent[pos[i]] != -1){
                        intended_node[i] = parent[pos[i]];
                    }
                }
            }
            // Check blocked moves
            // Prepare min_worm for each node
            int min_worm[MAXN];
            for(int i=1;i<=n;i++) min_worm[i] = -1;
            for(int i=0;i<k;i++) {
                if(moving[i] && intended_node[i]!=-1){
                    int node = intended_node[i];
                    if(!occupied[node]){
                        if(min_worm[node]==-1 || i < min_worm[node]){
                            min_worm[node] = i;
                        }
                    }
                }
            }
            // Collect worms that can move
            int can_move[MAXK];
            memset(can_move, 0, sizeof(can_move));
            for(int i=0;i<k;i++) {
                if(moving[i] && intended_node[i]!=-1){
                    int node = intended_node[i];
                    if(!occupied[node] && min_worm[node]==i){
                        can_move[i] =1;
                    }
                }
            }
            // If no worm can move, break
            int any_move =0;
            for(int i=0;i<k;i++) if(can_move[i]) {any_move=1; break;}
            if(!any_move) break;
            // Move worms
            // First, mark old positions as not occupied
            for(int i=0;i<k;i++) {
                if(can_move[i]){
                    occupied[pos[i]] = 0;
                }
            }
            // Now, move and mark new positions
            // Collect eaters
            int eaters[MAXK];
            int eater_count =0;
            for(int i=0;i<k;i++) {
                if(can_move[i]){
                    pos[i] = intended_node[i];
                    if(pos[i] == t){
                        eaters[eater_count++] = i;
                    }
                    occupied[pos[i]] =1;
                }
            }
            // If any eater, find smallest index
            if(eater_count >0){
                int selected_eater = eaters[0];
                for(int i=1;i<eater_count;i++) if(eaters[i] < selected_eater) selected_eater = eaters[i];
                count_eat[selected_eater]++;
                // Eater stays at t
                moving[selected_eater] =0;
                break;
            }
        }
    }
    for(int i=0;i<k;i++) printf("%d %d\n", pos[i], count_eat[i]);
    return 0;
}