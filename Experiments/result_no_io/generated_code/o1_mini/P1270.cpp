#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIME 6001
#define MAX_NODES 200
#define MAX_CHILDREN 2

typedef struct Node {
    int corridor_time;
    int paintings;
    struct Node* children[MAX_CHILDREN];
} Node;

// Buffer to store input
int input_buffer[2000];
int input_size = 0;
int input_ptr = 0;

// Read all integers from input line 2
void read_input_line() {
    while(scanf("%d", &input_buffer[input_size]) != EOF){
        input_size++;
    }
}

// Recursive parser to build the tree
Node* parse_tree() {
    if(input_ptr +1 >= input_size) return NULL;
    Node* node = (Node*)malloc(sizeof(Node));
    node->corridor_time = input_buffer[input_ptr++];
    node->paintings = input_buffer[input_ptr++];
    for(int i=0;i<MAX_CHILDREN;i++) node->children[i]=NULL;
    if(node->paintings == 0){
        node->children[0] = parse_tree();
        node->children[1] = parse_tree();
    }
    return node;
}

// Allocate memory for dp arrays
int dp_map[MAX_NODES][MAX_TIME];
int node_count = 0;

// Initialize dp_map with -1
void init_dp_map() {
    for(int i=0;i<MAX_NODES;i++) {
        for(int t=0;t<MAX_TIME;t++) {
            dp_map[i][t] = -1;
        }
    }
}

// Combine two dp arrays into parent dp
void combine_dp(int parent, int child1, int child2, Node* node) {
    for(int t=0;t<MAX_TIME;t++) dp_map[parent][t] = 0;
    // Include neither
    dp_map[parent][0] = 0;
    // Include child1
    for(int t=0;t<MAX_TIME;t++) {
        if(dp_map[child1][t] != -1){
            if(t <= MAX_TIME-1){
                if(dp_map[parent][t] < dp_map[child1][t]){
                    dp_map[parent][t] = dp_map[child1][t];
                }
            }
        }
    }
    // Include child2
    for(int t=0;t<MAX_TIME;t++) {
        if(dp_map[child2][t] != -1){
            if(t <= MAX_TIME-1){
                if(dp_map[parent][t] < dp_map[child2][t]){
                    dp_map[parent][t] = dp_map[child2][t];
                }
            }
        }
    }
    // Include both
    for(int t1=0;t1<MAX_TIME;t1++) {
        if(dp_map[child1][t1] == -1) continue;
        for(int t2=0;t2<MAX_TIME-t1;t2++) {
            if(dp_map[child2][t2] == -1) continue;
            if(t1 + t2 <= MAX_TIME-1){
                if(dp_map[parent][t1 + t2] < dp_map[child1][t1] + dp_map[child2][t2]){
                    dp_map[parent][t1 + t2] = dp_map[child1][t1] + dp_map[child2][t2];
                }
            }
        }
    }
}

// Process the tree and fill dp_map
int process(Node* node) {
    int current = node_count++;
    for(int t=0;t<MAX_TIME;t++) dp_map[current][t] = -1;
    if(node->paintings >0){
        int cost = node->corridor_time *2 + node->paintings *5;
        if(cost < MAX_TIME){
            dp_map[current][cost] = node->paintings;
        }
        dp_map[current][0] = 0;
    }
    else{
        int child1 = process(node->children[0]);
        int child2 = process(node->children[1]);
        combine_dp(current, child1, child2, node);
    }
    return current;
}

int main(){
    int T;
    scanf("%d", &T);
    read_input_line();
    Node* root = parse_tree();
    init_dp_map();
    int root_node = process(root);
    int max_paintings =0;
    for(int t=0;t<=T-1 && t<MAX_TIME;t++) {
        if(dp_map[root_node][t] > max_paintings){
            max_paintings = dp_map[root_node][t];
        }
    }
    printf("%d\n", max_paintings);
    return 0;
}