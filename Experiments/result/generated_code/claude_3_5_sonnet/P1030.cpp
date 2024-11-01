#include <stdio.h>
#include <string.h>

#define MAX_SIZE 9

void findPreorder(char inorder[], char postorder[], int inStart, int inEnd, int postStart, int postEnd) {
    if (inStart > inEnd) return;
    
    char root = postorder[postEnd];
    printf("%c", root);
    
    if (inStart == inEnd) return;
    
    int rootIndex;
    for (rootIndex = inStart; rootIndex <= inEnd; rootIndex++) {
        if (inorder[rootIndex] == root) break;
    }
    
    int leftSize = rootIndex - inStart;
    
    findPreorder(inorder, postorder, inStart, rootIndex - 1, postStart, postStart + leftSize - 1);
    findPreorder(inorder, postorder, rootIndex + 1, inEnd, postStart + leftSize, postEnd - 1);
}

int main() {
    char inorder[MAX_SIZE], postorder[MAX_SIZE];
    
    scanf("%s", inorder);
    scanf("%s", postorder);
    
    int length = strlen(inorder);
    
    findPreorder(inorder, postorder, 0, length - 1, 0, length - 1);
    
    return 0;
}