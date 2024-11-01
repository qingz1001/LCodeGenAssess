#include <stdio.h>
#include <string.h>

int main() {
    char matrix[201][201];
    int n;
    scanf("%s", matrix[0]);
    n = strlen(matrix[0]);
    
    int count = 0;
    int prevChar = matrix[0][0] - '0';
    int compressCode[n*n + 1];
    
    compressCode[count++] = n; // 第一个数是 N
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int currentChar = matrix[i][j] - '0';
            if (currentChar != prevChar) {
                compressCode[count++] = count - 1;
                prevChar = currentChar;
            }
        }
    }
    compressCode[count++] = n; // 最后一个数是 N
    
    for (int i = 1; i < count; i++) {
        printf("%d ", compressCode[i]);
    }
    
    return 0;
}