#include <stdio.h>
#include <string.h>

char inorder[10], postorder[10];
char preorder[10];
int preIndex = 0;

typedef struct Node {
    char val;
    struct Node* left;
    struct Node* right;
} Node;

Node* buildTree(char in[], char post[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = post[*postIndex];
    node->left = node->right = NULL;
    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; inIndex++) {
        if (in[inIndex] == post[*postIndex])
            break;
    }
    (*postIndex)--;
    node->right = buildTree(in, post, inIndex + 1, inEnd, postIndex);
    node->left = buildTree(in, post, inStart, inIndex - 1, postIndex);
    return node;
}

void preorderTraversal(Node* root) {
    if (root == NULL)
        return;
    preorder[preIndex++] = root->val;
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

int main(){
    scanf("%s", inorder);
    scanf("%s", postorder);
    int len = strlen(inorder);
    int postIndex = len -1;
    Node* root = buildTree(inorder, postorder, 0, len-1, &postIndex);
    preorderTraversal(root);
    preorder[preIndex] = '\0';
    printf("%s", preorder);
    return 0;
}