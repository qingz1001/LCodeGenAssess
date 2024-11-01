#include <stdio.h>
#include <string.h>

void preorder(char *inorder, char *postorder, int inStart, int inEnd, int postStart, int postEnd, char *preorder) {
    if (inStart > inEnd || postStart > postEnd) return;
    
    // The last element in postorder traversal is the root
    char root = postorder[postEnd];
    preorder[0] = root;
    
    // Find the index of the root in inorder traversal
    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; inIndex++) {
        if (inorder[inIndex] == root) break;
    }
    
    // Calculate the number of elements in the left subtree
    int leftSize = inIndex - inStart;
    
    // Recursively construct the left and right subtrees
    preorder[1] = '\0';
    preorder(leftorder, postorder, inStart, inIndex - 1, postStart, postStart + leftSize - 1, preorder + 1);
    preorder(rightorder, postorder, inIndex + 1, inEnd, postStart + leftSize, postEnd - 1, preorder + 1);
}

int main() {
    char inorder[10], postorder[10], preorder[10];
    
    // Read inorder and postorder traversals
    scanf("%s %s", inorder, postorder);
    
    // Calculate the size of the tree
    int size = strlen(inorder);
    
    // Generate preorder traversal
    preorder(inorder, postorder, 0, size - 1, 0, size - 1, preorder);
    
    // Print the preorder traversal
    printf("%s\n", preorder);
    
    return 0;
}