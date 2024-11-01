#include <stdio.h>
#include <stdlib.h>

typedef struct SegmentNode {
    int left, right;
    int value;
    struct SegmentNode* left_child;
    struct SegmentNode* right_child;
} SegmentNode;

typedef struct {
    int a;
    int b;
} Poster;

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int binary_search_unique(int* arr, int size, int key) {
    int left = 0, right = size -1;
    while(left <= right){
        int mid = left + (right - left)/2;
        if(arr[mid] == key) return mid;
        if(arr[mid] < key) left = mid +1;
        else right = mid -1;
    }
    return -1;
}

SegmentNode* create_node(int l, int r){
    SegmentNode* node = (SegmentNode*)malloc(sizeof(SegmentNode));
    node->left = l;
    node->right = r;
    node->value = 0;
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}

void update(SegmentNode* node, int l, int r, int val){
    if(node->left > r || node->right < l){
        return;
    }
    if(l <= node->left && node->right <= r){
        node->value = val;
        if(node->left_child){
            free(node->left_child);
            node->left_child = NULL;
        }
        if(node->right_child){
            free(node->right_child);
            node->right_child = NULL;
        }
        return;
    }
    if(node->value != 0){
        if(!node->left_child && node->left != node->right){
            int mid = (node->left + node->right) / 2;
            node->left_child = create_node(node->left, mid);
            node->right_child = create_node(mid+1, node->right);
            node->left_child->value = node->value;
            node->right_child->value = node->value;
        }
        node->value = 0;
    }
    if(node->left_child && node->right_child){
        update(node->left_child, l, r, val);
        update(node->right_child, l, r, val);
    }
}

void collect(SegmentNode* node, int* visible){
    if(node->value != 0){
        visible[node->value] = 1;
        return;
    }
    if(node->left_child && node->right_child){
        collect(node->left_child, visible);
        collect(node->right_child, visible);
    }
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Poster posters[M];
    int coords[2*M];
    for(int i =0; i<M; i++){
        scanf("%d %d", &posters[i].a, &posters[i].b);
        coords[2*i] = posters[i].a;
        coords[2*i+1] = posters[i].b;
    }
    // Sort and remove duplicates
    qsort(coords, 2*M, sizeof(int), compare);
    int unique[2*M];
    int unique_size =0;
    unique[unique_size++] = coords[0];
    for(int i=1; i<2*M; i++){
        if(coords[i] != coords[i-1]){
            unique[unique_size++] = coords[i];
        }
    }
    // Create segment tree
    SegmentNode* root = create_node(0, unique_size-1);
    for(int i=0; i<M; i++){
        int l = binary_search_unique(unique, unique_size, posters[i].a);
        int r = binary_search_unique(unique, unique_size, posters[i].b);
        update(root, l, r, i+1);
    }
    // Collect visible posters
    int visible[M+1];
    for(int i=0; i<=M; i++) visible[i] =0;
    collect(root, visible);
    // Count
    int count =0;
    for(int i=1; i<=M; i++) if(visible[i]) count++;
    printf("%d\n", count);
    return 0;
}