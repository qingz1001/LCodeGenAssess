#include <stdio.h>
#include <string.h>

#define MAX_N 10
#define MAX_LEN (1 << MAX_N)

void buildFBI(char* tree, char* str, int start, int end) {
    if (start == end) {
        tree[start] = str[start];
    } else {
        int mid = (start + end) / 2;
        buildFBI(tree, str, start, mid);
        buildFBI(tree, str, mid + 1, end);
        
        if (tree[mid] == 'B' && tree[mid + 1] == 'B') {
            tree[mid] = 'B';
        } else if (tree[mid] == 'I' && tree[mid + 1] == 'I') {
            tree[mid] = 'I';
        } else {
            tree[mid] = 'F';
        }
    }
}

void postOrder(char* tree, int start, int end, char* result, int* index) {
    if (start > end) {
        return;
    }
    if (start == end) {
        result[(*index)++] = tree[start];
    } else {
        int mid = (start + end) / 2;
        postOrder(tree, start, mid, result, index);
        postOrder(tree, mid + 1, end, result, index);
        result[(*index)++] = tree[mid];
    }
}

int main() {
    int N;
    scanf("%d", &N);
    char str[MAX_LEN + 1];
    scanf("%s", str);
    
    char tree[MAX_LEN + 1];
    buildFBI(tree, str, 0, (1 << N) - 1);
    
    char result[MAX_LEN * 2 + 1];
    int index = 0;
    postOrder(tree, 0, (1 << N) - 1, result, &index);
    result[index] = '\0';
    
    printf("%s\n", result);
    
    return 0;
}