#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

typedef struct {
    int id;
    long long d_v;
    long long p_v;
    long long q_v;
    long long l_v;
} Node;

typedef struct {
    long long m;
    long long c;
    long long d_a;
} Line;

typedef struct {
    Line lines[MAXN];
    int head;
    int tail;
} LineDeque;

int cmp_nodes(const void *a, const void *b){
    Node *na = (Node*)a;
    Node *nb = (Node*)b;
    if(na->d_v < nb->d_v) return -1;
    if(na->d_v > nb->d_v) return 1;
    return na->id - nb->id;
}

int main(){
    int n, t;
    scanf("%d %d", &n, &t);
    
    Node *nodes = (Node*)malloc(sizeof(Node)*(n+1));
    // Initialize node 1
    nodes[1].id =1;
    nodes[1].d_v =0;
    nodes[1].p_v =0;
    nodes[1].q_v =0;
    nodes[1].l_v =0;
    
    for(int v=2; v<=n; v++){
        int f_v;
        long long s_v, p_v, q_v, l_v;
        scanf("%d %lld %lld %lld %lld", &f_v, &s_v, &p_v, &q_v, &l_v);
        nodes[v].id =v;
        nodes[v].d_v = nodes[f_v].d_v + s_v;
        nodes[v].p_v = p_v;
        nodes[v].q_v = q_v;
        nodes[v].l_v = l_v;
    }
    
    // Create sorted_nodes array
    Node *sorted = (Node*)malloc(sizeof(Node)*(n));
    for(int i=0; i<n; i++) {
        sorted[i] = nodes[i+1];
    }
    qsort(sorted, n, sizeof(Node), cmp_nodes);
    
    // Initialize min_cost
    long long *min_cost = (long long*)malloc(sizeof(long long)*(n+1));
    for(int i=1; i<=n; i++) min_cost[i] = 0;
    
    // Initialize CHT
    LineDeque deque;
    deque.head =0;
    deque.tail =0;
    
    // Insert node1's line
    // Find node1 in sorted
    for(int i=0; i<n; i++) {
        if(sorted[i].id ==1){
            // min_cost[1] =0
            Line first_line;
            first_line.m =0;
            first_line.c =0;
            first_line.d_a =0;
            deque.lines[deque.tail++] = first_line;
            break;
        }
    }
    
    // Process nodes
    for(int i=0; i<n; i++){
        Node current = sorted[i];
        if(current.id ==1){
            continue;
        }
        // Remove lines from front if d_a < d_v - l_v
        long long threshold = sorted[i].d_v - current.l_v;
        while(deque.head < deque.tail && deque.lines[deque.head].d_a < threshold){
            deque.head++;
        }
        if(deque.head == deque.tail){
            // No eligible a, which shouldn't happen
            // But to prevent undefined behavior, set min_cost to a large value
            min_cost[current.id] = 1e18;
        }
        else{
            // Query the deque for min_cost[a] - p_v * d_a
            // Since deque is sorted for min, the front has the minimal value
            // But need to ensure it's minimal
            // Implement a pointer for query
            while(deque.head +1 < deque.tail){
                Line *line1 = &deque.lines[deque.head];
                Line *line2 = &deque.lines[deque.head+1];
                // Compare y at p_v for line1 and line2
                // y1 = m1*p_v + c1
                // y2 = m2*p_v + c2
                // If y2 <= y1, move the head
                if(line2->m * current.p_v + line2->c <= line1->m * current.p_v + line1->c){
                    deque.head++;
                }
                else{
                    break;
                }
            }
            Line *best = &deque.lines[deque.head];
            min_cost[current.id] = best->m * current.p_v + best->c + current.p_v * sorted[i].d_v + current.q_v;
        }
        // Insert current node's line: m = -d_v, c = min_cost[v]
        Line new_line;
        new_line.m = -sorted[i].d_v;
        new_line.c = min_cost[current.id];
        new_line.d_a = sorted[i].d_v;
        // Remove lines from back if the new line makes them obsolete
        while(deque.tail - deque.head >=2){
            Line *last = &deque.lines[deque.tail-1];
            Line *second_last = &deque.lines[deque.tail-2];
            // Check if (second_last to last) is obsolete with the new line
            // (c2 - c1)/(m1 - m2) >= (c3 - c1)/(m1 - m3)
            // To avoid floating point, cross multiply:
            // (c2 - c1)*(m1 - m3) >= (c3 - c1)*(m1 - m2)
            __int128 lhs = (__int128)(last->c - second_last->c) * (second_last->m - new_line.m);
            __int128 rhs = (__int128)(new_line.c - second_last->c) * (second_last->m - last->m);
            if(lhs >= rhs){
                deque.tail--;
            }
            else{
                break;
            }
        }
        deque.lines[deque.tail++] = new_line;
    }
    
    // Prepare to output in node order from 2 to n
    // Create an array to map node ids to min_cost
    // Already stored in min_cost array
    for(int v=2; v<=n; v++){
        printf("%lld\n", min_cost[v]);
    }
    
    // Free allocated memory
    free(nodes);
    free(sorted);
    free(min_cost);
    
    return 0;
}