#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    while(n--){
        long long len = 0;
        // Allocate initial buffer
        size_t buf_size = 1048576;
        char *s = malloc(buf_size);
        if(!s){
            return 1;
        }
        int c;
        // Read until newline or EOF
        while((c = getchar()) != '\n' && c != EOF){
            if(len + 1 >= buf_size){
                buf_size *= 2;
                char *temp = realloc(s, buf_size);
                if(!temp){
                    free(s);
                    return 1;
                }
                s = temp;
            }
            s[len++] = c;
        }
        s[len] = '\0';
        // Preprocess the string for Manacher's algorithm
        long long t_len = 2 * len + 3;
        char *t = malloc(t_len);
        if(!t){
            free(s);
            return 1;
        }
        t[0] = '^';
        t[1] = '#';
        for(long long i = 0; i < len; i++){
            t[2 + 2*i] = s[i];
            t[3 + 2*i] = '#';
        }
        t[2 + 2*len] = '$';
        // Allocate p array
        int *p = malloc(t_len * sizeof(int));
        if(!p){
            free(s);
            free(t);
            return 1;
        }
        int center = 0, right = 0, max_len = 0;
        for(long long i = 1; i < t_len -1; i++){
            int mirror = 2*center - i;
            if(i < right){
                if(p[mirror] < right - i){
                    p[i] = p[mirror];
                }
                else{
                    p[i] = right - i;
                }
            }
            // Expand palindrome centered at i
            while(t[i + p[i] +1] == t[i - p[i] -1]){
                p[i]++;
            }
            if(i + p[i] > right){
                center = i;
                right = i + p[i];
            }
            if(p[i] > max_len){
                max_len = p[i];
            }
        }
        printf("%d\n", max_len);
        free(s);
        free(t);
        free(p);
    }
    return 0;
}