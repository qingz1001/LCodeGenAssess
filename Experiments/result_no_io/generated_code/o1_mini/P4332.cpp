#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005
#define MAXX (3 * MAXN + 5)

int parent_cell[MAXN];
int inputs[ MAXN ][3];
int head_children[MAXN];
int child_cells[3 * MAXN];
int next_child[3 * MAXN];
int external_to_cell_map[MAXX];
int external_values_arr[MAXX];
int count1_arr_val[MAXN];
int output_val_arr[MAXN];
int queue_cells[MAXN];
int front_q, rear_q;

int main(){
    int n;
    scanf("%d", &n);
    
    // Initialize children lists
    for(int i=1;i<=n;i++) head_children[i]=-1;
    
    // Initialize external_to_cell_map
    for(int i=1;i<=3*n+1;i++) external_to_cell_map[i]=0;
    
    // Read inputs and set parent and external mappings
    for(int j=1; j<=n; j++){
        int x1, x2, x3;
        scanf("%d %d %d", &x1, &x2, &x3);
        inputs[j][0] = x1;
        inputs[j][1] = x2;
        inputs[j][2] = x3;
        // Find parent
        int parent = 0;
        for(int k=0; k<3; k++){
            if(inputs[j][k] <= n){
                parent = inputs[j][k];
                break;
            }
        }
        parent_cell[j] = parent;
        // Add child to parent's children list
        if(parent != 0){
            next_child[rear_q] = head_children[parent];
            child_cells[rear_q] = j;
            head_children[parent] = rear_q++;
        }
        // Map external inputs
        for(int k=0; k<3; k++){
            if(inputs[j][k] > n){
                external_to_cell_map[inputs[j][k]] = j;
            }
        }
    }
    
    // Read external input values
    for(int x = n+1; x <= 3*n+1; x++){
        scanf("%d", &external_values_arr[x]);
    }
    
    // Initialize in-degree
    int in_degree[MAXN] = {0};
    for(int j=2; j<=n; j++) in_degree[j] =1;
    // Initialize queue with root
    front_q = 0;
    rear_q = 0;
    queue_cells[rear_q++] =1;
    
    // BFS to compute initial outputs
    while(front_q < rear_q){
        int j = queue_cells[front_q++];
        // Compute count1[j]
        int cnt =0;
        for(int k=0; k<3; k++){
            int x = inputs[j][k];
            if(x <=n){
                cnt += output_val_arr[x];
            }
            else{
                cnt += external_values_arr[x];
            }
        }
        count1_arr_val[j] = cnt;
        output_val_arr[j] = (cnt >1) ?1:0;
        // Enqueue children
        for(int ptr = head_children[j]; ptr != -1 && ptr >=0; ptr = next_child[ptr]){
            int child = child_cells[ptr];
            if(--in_degree[child] ==0){
                queue_cells[rear_q++] = child;
            }
        }
    }
    
    // Read number of queries
    int q;
    scanf("%d", &q);
    
    while(q--){
        int x;
        scanf("%d", &x);
        // Toggle external input
        external_values_arr[x] ^=1;
        // Find the cell affected
        int j = external_to_cell_map[x];
        if(j ==0){
            // No cell connected to this external input
            // Output root's output
            printf("%d\n", output_val_arr[1]);
            continue;
        }
        // Update count1[j]
        if(external_values_arr[x]){
            count1_arr_val[j]++;
        }
        else{
            count1_arr_val[j]--;
        }
        // Check if output[j] changes
        int new_output = (count1_arr_val[j] >1) ?1:0;
        if(new_output == output_val_arr[j]){
            // No change in output
            printf("%d\n", output_val_arr[1]);
            continue;
        }
        // Output changed, propagate
        int old_output = output_val_arr[j];
        output_val_arr[j] = new_output;
        int delta = new_output - old_output;
        int p = parent_cell[j];
        while(p !=0){
            count1_arr_val[p] += delta;
            int new_out_p = (count1_arr_val[p] >1) ?1:0;
            if(new_out_p == output_val_arr[p]){
                break;
            }
            int old_out_p = output_val_arr[p];
            output_val_arr[p] = new_out_p;
            delta = new_out_p - old_out_p;
            p = parent_cell[p];
        }
        // Print root's output
        printf("%d\n", output_val_arr[1]);
    }
    
    return 0;
}