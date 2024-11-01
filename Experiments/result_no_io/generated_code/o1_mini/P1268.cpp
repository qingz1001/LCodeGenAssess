#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 60
#define INF 1e18

int main(){
    int n;
    scanf("%d", &n);
    double M[MAX_NODES][MAX_NODES];
    for(int i=0;i<MAX_NODES;i++) {
        for(int j=0;j<MAX_NODES;j++) {
            if(i == j) M[i][j] = 0.0;
            else M[i][j] = INF;
        }
    }
    // Read upper triangle
    for(int i=0;i<n-1;i++) {
        for(int j=i+1;j<n;j++) {
            int val;
            scanf("%d", &val);
            M[i][j] = (double)val;
            M[j][i] = (double)val;
        }
    }
    // Initialize active nodes
    int current_nodes[MAX_NODES];
    int num_current = n;
    for(int i=0;i<n;i++) current_nodes[i] = i;
    int next_node = n;
    double total_sum = 0.0;
    while(num_current >2){
        // Compute r[i]
        double r[MAX_NODES];
        for(int i=0;i<num_current;i++){
            r[i] =0.0;
            for(int j=0;j<num_current;j++) if(i!=j){
                r[i] += M[current_nodes[i]][current_nodes[j]];
            }
        }
        // Compute Q matrix and find minimum
        double min_Q = INF;
        int min_i = -1, min_j = -1;
        for(int i=0;i<num_current;i++) {
            for(int j=i+1;j<num_current;j++) {
                double Q = (num_current -2)*M[current_nodes[i]][current_nodes[j]] - r[i] - r[j];
                if(Q < min_Q){
                    min_Q = Q;
                    min_i = i;
                    min_j = j;
                }
            }
        }
        // Get indices
        int idx_i = current_nodes[min_i];
        int idx_j = current_nodes[min_j];
        // Compute delta
        double delta = (r[min_i] - r[min_j]) / (double)(num_current -2);
        // Compute limb lengths
        double limb_i = (M[idx_i][idx_j] + delta)/2.0;
        double limb_j = (M[idx_i][idx_j] - delta)/2.0;
        total_sum += limb_i + limb_j;
        // Create new node
        int new_node = next_node++;
        // Compute distances to new node
        for(int k=0;k<num_current;k++) {
            if(k == min_i || k == min_j) continue;
            double dik = M[idx_i][current_nodes[k]];
            double djk = M[idx_j][current_nodes[k]];
            M[new_node][current_nodes[k]] = (dik + djk - M[idx_i][idx_j])/2.0;
            M[current_nodes[k]][new_node] = M[new_node][current_nodes[k]];
        }
        M[new_node][new_node] = 0.0;
        // Replace min_i and min_j with new_node
        current_nodes[min_i] = new_node;
        // Shift the array to remove min_j
        for(int k=min_j; k < num_current-1; k++) {
            current_nodes[k] = current_nodes[k+1];
        }
        num_current--;
    }
    // Add the distance between the last two nodes
    double last_distance = M[current_nodes[0]][current_nodes[1]];
    total_sum += last_distance;
    // Round to nearest integer
    long long result = llround(total_sum);
    printf("%lld\n", result);
    return 0;
}