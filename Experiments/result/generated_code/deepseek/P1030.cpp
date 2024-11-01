#include <stdio.h>
#include <string.h>

void preorder(char *inorder, char *postorder, int length) {
    if (length <= 0) return;
    char root = postorder[length - 1];
    printf("%c", root);
    int i;
    for (i = 0; i < length; i++) {
        if (inorder[i] == root) break;
    }
    preorder(inorder, postorder, i);
    preorder(inorder + i + 1, postorder + i, length - i - 1);
}

int main() {
    char inorder[9], postorder[9];
    scanf("%s", inorder);
    scanf("%s", postorder);
    int length = strlen(inorder);
    preorder(inorder, postorder, length);
    return 0;
}