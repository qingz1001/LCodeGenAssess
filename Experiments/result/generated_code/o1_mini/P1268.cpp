#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_NODES 60
#define INF 1e9

typedef struct {
    int from;
    int to;
    double length;
} Edge;

typedef struct {
    int size;
    Edge edges[MAX_NODES];
} EdgeList;

int main(){
    int n;
    scanf("%d", &n);
    // Initialize distance matrix
    double D[MAX_NODES][MAX_NODES];
    memset(D, 0, sizeof(D));
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            int val;
            scanf("%d", &val);
            D[i][j] = D[j][i] = (double)val;
        }
    }
    EdgeList el;
    el.size =0;
    int current_nodes = n;
    int active[MAX_NODES];
    for(int i=0;i<MAX_NODES;i++) active[i]=1;
    while(current_nodes >2){
        // Compute total distances
        double total[MAX_NODES];
        for(int i=0;i<current_nodes;i++) {
            total[i] =0.0;
            for(int j=0;j<current_nodes;j++) if(i!=j) total[i] += D[i][j];
        }
        // Compute Q matrix and find minimum
        double Q[MAX_NODES][MAX_NODES];
        double minQ = INF;
        int min_i = -1, min_j=-1;
        for(int i=0;i<current_nodes;i++){
            for(int j=i+1;j<current_nodes;j++){
                Q[i][j] = (current_nodes-2)*D[i][j] - total[i] - total[j];
                if(Q[i][j] < minQ){
                    minQ = Q[i][j];
                    min_i = i;
                    min_j = j;
                }
            }
        }
        // Compute limb lengths
        double delta = (total[min_i] - total[min_j]) / (double)(current_nodes -2);
        double limb_i = (D[min_i][min_j] + delta)/2.0;
        double limb_j = (D[min_i][min_j] - delta)/2.0;
        // Add edges
        el.edges[el.size].from = min_i;
        el.edges[el.size].to = current_nodes;
        el.edges[el.size].length = limb_i;
        el.size++;
        el.edges[el.size].from = min_j;
        el.edges[el.size].to = current_nodes;
        el.edges[el.size].length = limb_j;
        el.size++;
        // Compute distances for new node
        for(int k=0;k<current_nodes;k++){
            if(k == min_i || k == min_j) continue;
            D[current_nodes][k] = D[k][current_nodes] = (D[min_i][k] + D[min_j][k] - D[min_i][min_j])/2.0;
        }
        // Remove min_i and min_j by swapping with last nodes
        // Replace min_i with last node
        if(min_i != current_nodes-1){
            for(int j=0;j<current_nodes;j++) {
                D[min_i][j] = D[current_nodes-1][j];
                D[j][min_i] = D[j][current_nodes-1];
            }
        }
        // Replace min_j with last node
        if(min_j != current_nodes-1 && min_j != min_i){
            for(int j=0;j<current_nodes;j++) {
                D[min_j][j] = D[current_nodes-1][j];
                D[j][min_j] = D[j][current_nodes-1];
            }
        }
        current_nodes--;
        // Increase current_nodes for new node
        D[current_nodes][current_nodes] =0.0;
        current_nodes++;
    }
    // Connect the last two nodes
    double last_dist = D[0][1];
    el.edges[el.size].from =0;
    el.edges[el.size].to =1;
    el.edges[el.size].length = last_dist;
    el.size++;
    // Now sum all edge lengths, but need to ensure each edge is counted once
    // Since edges were added twice in NJ, divide by 2
    double total_weight =0.0;
    for(int i=0;i<el.size;i++) total_weight += el.edges[i].length;
    // Since the problem expects integer weights
    printf("%d\n", (int)(total_weight + 1e-6));
    return 0;
}