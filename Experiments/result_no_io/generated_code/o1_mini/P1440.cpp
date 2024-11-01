#include <stdio.h>
#include <stdlib.h>

#define MAX 2000001
#define BUFFER_SIZE 24000000

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *a = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    
    int *deque = (int*)malloc((n+1) * sizeof(int));
    int front =0, tail=0;
    
    char *buffer = (char*)malloc(BUFFER_SIZE);
    int buf_pos =0;
    for(int i=1;i<=n;i++){
        if(i-1 >=1){
            while(front < tail && a[deque[tail-1]] >= a[i-1]){
                tail--;
            }
            deque[tail++] = i-1;
        }
        while(front < tail && deque[front] < i - m){
            front++;
        }
        if(i ==1){
            buffer[buf_pos++] = '0';
            buffer[buf_pos++] = '\n';
        }
        else{
            int min_val = (front < tail) ? a[deque[front]] : 0;
            // Convert min_val to string
            int start = buf_pos;
            if(min_val ==0){
                buffer[buf_pos++] = '0';
                buffer[buf_pos++] = '\n';
            }
            else{
                char num[12];
                int len =0;
                int tmp = min_val;
                while(tmp >0){
                    num[len++] = (tmp %10) + '0';
                    tmp /=10;
                }
                for(int j=len-1;j>=0;j--){
                    buffer[buf_pos++] = num[j];
                }
                buffer[buf_pos++] = '\n';
            }
        }
    }
    fwrite(buffer, sizeof(char), buf_pos, stdout);
    free(a);
    free(deque);
    free(buffer);
    return 0;
}