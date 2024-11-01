#include <stdio.h>
#include <string.h>

void preOrder(char *inOrder, char *postOrder, int length) {
    if (length <= 0) return;

    // 后序遍历的最后一个元素是根节点
    char root = postOrder[length - 1];
    printf("%c", root);

    // 在中序遍历中找到根节点的位置
    int rootIndex = 0;
    while (inOrder[rootIndex] != root) rootIndex++;

    // 递归处理左子树
    preOrder(inOrder, postOrder, rootIndex);

    // 递归处理右子树
    preOrder(inOrder + rootIndex + 1, postOrder + rootIndex, length - rootIndex - 1);
}

int main() {
    char inOrder[9], postOrder[9];
    scanf("%s", inOrder);
    scanf("%s", postOrder);

    int length = strlen(inOrder);
    preOrder(inOrder, postOrder, length);

    return 0;
}