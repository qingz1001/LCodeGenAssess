#include <stdio.h>
#include <string.h>

typedef struct Node {
    char val;
    int left;
    int right;
} Node;

Node nodes[26];

void preorder(int index) {
    if(index == -1) return;
    printf("%c", nodes[index].val);
    preorder(nodes[index].left);
    preorder(nodes[index].right);
}

int main(){
    int n;
    scanf("%d", &n);
    // Initialize all nodes
    for(int i=0;i<26;i++) {
        nodes[i].val = 'a' + i;
        nodes[i].left = -1;
        nodes[i].right = -1;
    }
    char line[4];
    int root = -1;
    for(int i=0;i<n;i++) {
        scanf("%s", line);
        char parent = line[0];
        char left = line[1];
        char right = line[2];
        int p = parent - 'a';
        if(i == 0) root = p;
        if(left != '*') nodes[p].left = left - 'a';
        if(right != '*') nodes[p].right = right - 'a';
    }
    preorder(root);
    return 0;
}