#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    // Allocate memory
    int *x1 = (int*)malloc((n+1)*sizeof(int));
    int *x2 = (int*)malloc((n+1)*sizeof(int));
    int *x3 = (int*)malloc((n+1)*sizeof(int));
    
    int total_nodes = 3*n +1;
    // Allocate depend_count
    int *depend_count = (int*)calloc((total_nodes+2), sizeof(int));
    
    // Read cell connections and count dependents
    for(int i=1;i<=n;i++){
        scanf("%d %d %d", &x1[i], &x2[i], &x3[i]);
        depend_count[x1[i]]++;
        depend_count[x2[i]]++;
        depend_count[x3[i]]++;
    }
    
    // Compute start indices
    int *start = (int*)malloc((total_nodes+2)*sizeof(int));
    start[1] = 0;
    long long sum =0;
    for(int x=1; x<=total_nodes; x++){
        start[x] = sum;
        sum += depend_count[x];
    }
    
    // Allocate depend_list
    int *depend_list = (int*)malloc((3*n)*sizeof(int));
    
    // Temporary position array
    int *current_pos = (int*)malloc((total_nodes+2)*sizeof(int));
    for(int x=1; x<=total_nodes; x++) current_pos[x] = start[x];
    
    // Fill depend_list
    for(int i=1;i<=n;i++){
        int inputs[3] = {x1[i], x2[i], x3[i]};
        for(int k=0; k<3; k++){
            int x = inputs[k];
            depend_list[current_pos[x]++] = i;
        }
    }
    
    free(current_pos);
    
    // Read external inputs
    int external_inputs = 2*n +1;
    // Allocate value array
    int *value_all = (int*)malloc((total_nodes+2)*sizeof(int));
    for(int x=n+1; x<=3*n+1; x++){
        scanf("%d", &value_all[x]);
    }
    
    // Initialize cells
    int *cnt1s = (int*)calloc((n+1), sizeof(int));
    int *processed = (int*)calloc((n+1), sizeof(int));
    // Allocate queue
    int queue_size = 3*n +1;
    int *queue = (int*)malloc((queue_size)*sizeof(int));
    int front =0, back =0;
    // Enqueue external inputs
    for(int x=n+1; x<=3*n+1; x++) {
        queue[back++] = x;
    }
    // Process initial queue
    while(front < back){
        int node = queue[front++];
        int start_p = start[node];
        int end_p;
        if(node < total_nodes)
            end_p = start[node+1];
        else
            end_p = start[node] + depend_count[node];
        for(int p = start_p; p < end_p; p++){
            int cell = depend_list[p];
            if(value_all[node] ==1){
                cnt1s[cell]++;
            }
            processed[cell]++;
            if(processed[cell] ==3){
                int new_val = cnt1s[cell] >=2 ? 1 : 0;
                if(value_all[cell] != new_val){
                    value_all[cell] = new_val;
                    queue[back++] = cell;
                }
            }
        }
    }
    
    free(processed);
    
    // Read q
    int q;
    scanf("%d", &q);
    
    // Reset queue
    front =0;
    back =0;
    
    while(q--){
        int x;
        scanf("%d", &x);
        // Flip x's value
        int new_val = 1 - value_all[x];
        if(new_val != value_all[x]){
            value_all[x] = new_val;
            // Enqueue affected cells
            int start_p = start[x];
            int end_p;
            if(x < total_nodes)
                end_p = start[x+1];
            else
                end_p = start[x] + depend_count[x];
            for(int p = start_p; p < end_p; p++){
                int cell = depend_list[p];
                if(new_val ==1){
                    cnt1s[cell]++;
                }
                else{
                    cnt1s[cell]--;
                }
                int new_output = cnt1s[cell] >=2 ?1 :0;
                if(new_output != value_all[cell]){
                    value_all[cell] = new_output;
                    queue[back++] = cell;
                }
            }
            // Process the queue
            while(front < back){
                int cell = queue[front++];
                int start_p2 = start[cell];
                int end_p2;
                if(cell < total_nodes)
                    end_p2 = start[cell+1];
                else
                    end_p2 = start[cell] + depend_count[cell];
                for(int p2 = start_p2; p2 < end_p2; p2++){
                    int cell2 = depend_list[p2];
                    if(value_all[cell] ==1){
                        cnt1s[cell2]++;
                    }
                    else{
                        cnt1s[cell2]--;
                    }
                    int new_output2 = cnt1s[cell2] >=2 ?1 :0;
                    if(new_output2 != value_all[cell2]){
                        value_all[cell2] = new_output2;
                        queue[back++] = cell2;
                    }
                }
            }
            // Reset queue
            front =0;
            back =0;
        }
        // Print root's value
        printf("%d\n", value_all[1]);
    }
    
    // Free memory
    free(x1);
    free(x2);
    free(x3);
    free(depend_count);
    free(start);
    free(depend_list);
    free(value_all);
    free(cnt1s);
    free(queue);
    
    return 0;
}