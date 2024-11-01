#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_M 10
#define MAX_NODES (1 << MAX_M)
#define MAX_ROW 20
#define MAX_COL 2000

typedef struct Node {
    int level;
    int index;
    int deleted;
    struct Node* left;
    struct Node* right;
} Node;

char grid[MAX_ROW][MAX_COL];

int m, n;
int del_levels[11];
int del_indices[11];

Node* create_node(int level, int index) {
    if (level > m) return NULL;
    Node* node = (Node*)malloc(sizeof(Node));
    node->level = level;
    node->index = index;
    node->deleted = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* build_tree(int level, int index) {
    if (level > m) return NULL;
    // Check if this node is to be deleted
    for(int i=0;i<n;i++) {
        if(del_levels[i]==level && del_indices[i]==index){
            return NULL;
        }
    }
    Node* node = create_node(level, index);
    node->left = build_tree(level+1, index*2-1);
    node->right = build_tree(level+1, index*2);
    return node;
}

int col_start[MAX_M+1];
int step;

void init_positions(int level, int index, int row, int* col) {
    if(level > m) return;
    init_positions(level+1, index*2-1, row+2, col);
    grid[row][(*col)] = 'o';
    if(level < m){
        grid[row+1][(*col)-1] = '/';
        grid[row+1][(*col)+1] = '\\';
        init_positions(level+1, index*2-1, row+2, col);
        init_positions(level+1, index*2, row+2, col);
    }
}

int main(){
    scanf("%d %d", &m, &n);
    for(int i=0;i<n;i++) {
        scanf("%d %d", &del_levels[i], &del_indices[i]);
    }
    // Initialize grid with spaces
    for(int i=0;i<2*m-1;i++) {
        for(int j=0;j<MAX_COL;j++) grid[i][j] = ' ';
    }
    // Build tree
    Node* root = build_tree(1,1);
    // Assign positions
    int total_cols = 1;
    for(int i=1;i<=m;i++) total_cols = total_cols * 2 +1;
    total_cols = (1 << m) * 4;
    // Reset grid
    for(int i=0;i<2*m-1;i++) {
        for(int j=0;j<MAX_COL;j++) grid[i][j] = ' ';
    }
    // Function to place nodes
    int center = (1 << (m)) ;
    // Recursive function to place nodes
    void place(Node* node, int row, int left, int right){
        if(node == NULL) return;
        int mid = (left + right) /2;
        grid[row][mid] = 'o';
        if(row < 2*m-2){
            if(node->left){
                grid[row+1][mid-1] = '/';
                place(node->left, row+2, left, mid-1);
            }
            if(node->right){
                grid[row+1][mid+1] = '\\';
                place(node->right, row+2, mid+1, right);
            }
        }
    }
    place(root, 0, 0, (1<<m)*4);
    // Print grid
    int max_row = 2*m-1;
    int max_col = (1<<m)*4;
    for(int i=0;i<max_row;i++){
        for(int j=0;j<max_col;j++) putchar(grid[i][j]);
        putchar('\n');
    }
    return 0;
}