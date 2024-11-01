#include <stdio.h>
#include <string.h>

#define MAXN 1024

int n;
char s[MAXN];

void construct_fbi_tree(int left, int right, char *tree, int *index) {
    if (left == right) {
        tree[(*index)++] = s[left];
        return;
    }
    
    int mid = (left + right) / 2;
    int left_index = *index;
    construct_fbi_tree(left, mid, tree, index);
    int right_index = *index;
    construct_fbi_tree(mid + 1, right, tree, index);
    
    int is_F = 0;
    for (int i = left_index; i < right_index; ++i) {
        if (tree[i] == '0') {
            tree[(*index)++] = 'B';
            return;
        } else if (tree[i] == '1') {
            is_F = 1;
        }
    }
    if (is_F) {
        tree[(*index)++] = 'I';
    } else {
        tree[(*index)++] = 'B';
    }
}

void postorder_traversal(char *tree, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%c", tree[i]);
    }
    printf("\n");
}

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    
    int tree_size = 1 << (n + 1);
    char tree[tree_size];
    int index = 0;
    
    construct_fbi_tree(0, (1 << n) - 1, tree, &index);
    
    postorder_traversal(tree, index);
    
    return 0;
}