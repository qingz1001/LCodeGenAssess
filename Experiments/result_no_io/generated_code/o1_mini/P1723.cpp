#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_string(size_t max_len) {
    char *s = (char*)malloc(max_len + 2);
    if (!s) return NULL;
    size_t idx = 0;
    int c;
    // Skip any leading newlines
    while ((c = getchar()) != EOF && (c == '\n' || c == '\r'));
    if (c != EOF) {
        s[idx++] = c;
    }
    while ((c = getchar()) != EOF && c != '\n' && c != '\r') {
        if (idx < max_len) {
            s[idx++] = c;
        }
    }
    s[idx] = '\0';
    return s;
}

int main(){
    int n;
    if(scanf("%d\n", &n)!=1){
        return 1;
    }
    while(n--){
        char *s = read_string(10000000);
        if(!s){
            return 1;
        }
        int len = strlen(s);
        // Transform the string
        size_t T_len = 2 * len + 3;
        char *T = (char*)malloc(T_len);
        if(!T){
            free(s);
            return 1;
        }
        T[0] = '^';
        for(int i=0;i<len;i++){
            T[2*i+1] = '#';
            T[2*i+2] = s[i];
        }
        T[2*len+1] = '#';
        T[2*len+2] = '$';
        T[2*len+3] = '\0';
        // Manacher's algorithm
        int *P = (int*)malloc(sizeof(int)*(2*len+3));
        if(!P){
            free(s);
            free(T);
            return 1;
        }
        int C=0, R=0, max=0;
        for(int i=1;i<2*len+2;i++){
            int mirr = 2*C - i;
            if(i < R){
                P[i] = (P[mirr] < R - i) ? P[mirr] : R - i;
            }
            // Expand around center i
            while(T[i + (1 + P[i])] == T[i - (1 + P[i])]){
                P[i]++;
            }
            if(i + P[i] > R){
                C = i;
                R = i + P[i];
            }
            if(P[i] > max){
                max = P[i];
            }
        }
        printf("%d\n", max);
        free(s);
        free(T);
        free(P);
    }
    return 0;
}