#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAINTINGS 2001
#define INF 1000000000

typedef struct Node {
    int corridor_time;
    int paintings;
    struct Node *left;
    struct Node *right;
} Node;

int data_list[300];
int data_count = 0;

// Function to parse the tree
Node* parse_tree() {
    if (data_count >= 300) return NULL;
    Node* node = (Node*)malloc(sizeof(Node));
    node->corridor_time = data_list[data_count++];
    node->paintings = data_list[data_count++];
    node->left = NULL;
    node->right = NULL;
    if (node->paintings == 0) {
        node->left = parse_tree();
        node->right = parse_tree();
    }
    return node;
}

// Function to merge two min_time arrays
void merge_arrays(int *a, int size_a, int *b, int size_b, int *result, int *result_size) {
    for(int i=0;i<size_a;i++) {
        for(int j=0;j<size_b;j++) {
            if(a[i] + b[j] < result[i+j]) {
                result[i+j] = a[i] + b[j];
            }
        }
    }
    *result_size = size_a + size_b;
}

// Recursive function to process the tree
int* process(Node* node, int *max_paintings) {
    int* min_time = (int*)malloc(sizeof(int) * MAX_PAINTINGS);
    for(int i=0;i<MAX_PAINTINGS;i++) min_time[i] = INF;

    if(node->paintings > 0){
        // Leaf node
        for(int k=0; k<=node->paintings; k++){
            if(2 * node->corridor_time + 5 * k < MAX_PAINTINGS){
                if(2 * node->corridor_time + 5 * k < min_time[k]){
                    min_time[k] = 2 * node->corridor_time + 5 * k;
                }
            }
        }
    }
    else{
        // Internal node
        int* left = process(node->left, max_paintings);
        int* right = process(node->right, max_paintings);

        // Initialize with 0 paintings and 0 time
        int temp[MAX_PAINTINGS];
        for(int i=0;i<MAX_PAINTINGS;i++) temp[i] = INF;
        temp[0] = 0;

        // Take nothing
        // Already initialized

        // Take left only
        for(int p=0; p<MAX_PAINTINGS; p++){
            if(left[p] != INF && (2 * node->corridor_time + left[p]) < temp[p]){
                temp[p] = 2 * node->corridor_time + left[p];
            }
        }

        // Take right only
        for(int p=0; p<MAX_PAINTINGS; p++){
            if(right[p] != INF && (2 * node->corridor_time + right[p]) < temp[p]){
                temp[p] = 2 * node->corridor_time + right[p];
            }
        }

        // Take both
        for(int p1=0; p1<MAX_PAINTINGS; p1++){
            if(left[p1] == INF) continue;
            for(int p2=0; p2<MAX_PAINTINGS; p2++){
                if(right[p2] == INF) continue;
                if(p1 + p2 >= MAX_PAINTINGS) continue;
                if(left[p1] + right[p2] + 2 * node->corridor_time < temp[p1 + p2]){
                    temp[p1 + p2] = left[p1] + right[p2] + 2 * node->corridor_time;
                }
            }
        }

        // Update min_time
        for(int p=0; p<MAX_PAINTINGS; p++){
            min_time[p] = temp[p];
        }

        free(left);
        free(right);
    }

    return min_time;
}

int main(){
    int T;
    scanf("%d", &T);
    // Read the rest of the numbers
    int num;
    while(scanf("%d", &num) != EOF){
        data_list[data_count++] = num;
    }

    Node* root = parse_tree();
    int max_paintings = 0;
    int* result = process(root, &max_paintings);

    int answer = 0;
    for(int p=0; p<MAX_PAINTINGS; p++){
        if(result[p] <= T-1){
            if(p > answer){
                answer = p;
            }
        }
    }
    printf("%d\n", answer);

    free(result);
    return 0;
}