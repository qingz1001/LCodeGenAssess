#include <stdio.h>
#include <string.h>

void preOrder(char* inOrder, char* postOrder, int inStart, int inEnd, int postStart, int postEnd, char* result, int* resIndex) {
    if (inStart > inEnd || postStart > postEnd) {
        return;
    }
    
    result[(*resIndex)++] = postOrder[postEnd];
    int rootIndex = -1;
    for (int i = inStart; i <= inEnd; i++) {
        if (inOrder[i] == postOrder[postEnd]) {
            rootIndex = i;
            break;
        }
    }
    
    preOrder(inOrder, postOrder, inStart, rootIndex - 1, postStart, postStart + rootIndex - inStart - 1, result, resIndex);
    preOrder(inOrder, postOrder, rootIndex + 1, inEnd, postStart + rootIndex - inStart, postEnd - 1, result, resIndex);
}

int main() {
    char inOrder[10], postOrder[10];
    scanf("%s%s", inOrder, postOrder);
    
    int inLen = strlen(inOrder);
    int postLen = strlen(postOrder);
    
    char result[10];
    int resIndex = 0;
    
    preOrder(inOrder, postOrder, 0, inLen - 1, 0, postLen - 1, result, &resIndex);
    
    result[resIndex] = '\0';
    printf("%s\n", result);
    
    return 0;
}