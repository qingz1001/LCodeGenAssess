#include <stdio.h>
#include <string.h>

void findPreOrder(char *inorder, char *postorder, int length) {
    if (length <= 0) return;
    
    char root = postorder[length - 1];
    printf("%c", root);
    
    int rootIndex;
    for (rootIndex = 0; rootIndex < length; rootIndex++) {
        if (inorder[rootIndex] == root) break;
    }
    
    findPreOrder(inorder, postorder, rootIndex);
    findPreOrder(inorder + rootIndex + 1, postorder + rootIndex, length - rootIndex - 1);
}

int main() {
    char inorder[9], postorder[9];
    scanf("%s", inorder);
    scanf("%s", postorder);
    
    int length = strlen(inorder);
    
    findPreOrder(inorder, postorder, length);
    printf("\n");
    
    return 0;
}