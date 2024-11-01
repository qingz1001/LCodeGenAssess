#include <stdio.h>
#include <string.h>

#define MAX_N 2000
#define MAX_M 2000
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

int N, M;
int board[MAX_N][MAX_M];
int left[MAX_N][MAX_M], up[MAX_N][MAX_M];
int h[MAX_M], s[MAX_M];

int max_square() {
    int result = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j]) {
                left[i][j] = (j == 0) ? 1 : left[i][j-1] + 1;
                up[i][j] = (i == 0) ? 1 : up[i-1][j] + 1;
                int size = min(left[i][j], up[i][j]);
                while (size > result) {
                    if (left[i-size+1][j] >= size && up[i][j-size+1] >= size) {
                        result = size;
                        break;
                    }
                    size--;
                }
            }
        }
    }
    return result * result;
}

int max_rectangle() {
    int result = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j]) {
                h[j] = (i == 0) ? 1 : h[j] + 1;
            } else {
                h[j] = 0;
            }
        }
        
        int top = 0;
        for (int j = 0; j <= M; j++) {
            int height = (j == M) ? 0 : h[j];
            while (top > 0 && height < h[s[top-1]]) {
                int H = h[s[--top]];
                int W = (top == 0) ? j : j - s[top-1] - 1;
                if (W % 2 == 0) W--;
                result = max(result, H * W);
            }
            s[top++] = j;
        }
    }
    return result;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    
    printf("%d\n", max_square());
    printf("%d\n", max_rectangle());
    
    return 0;
}