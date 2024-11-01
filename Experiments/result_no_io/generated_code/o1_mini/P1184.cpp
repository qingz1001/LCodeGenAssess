#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_LEN 101

int main(){
    int n, m;
    if(scanf("%d %d", &n, &m)!=2) return 0;
    getchar(); // consume the newline after the numbers

    char convenient[MAX_N][MAX_LEN];
    for(int i=0;i<n;i++){
        if(!fgets(convenient[i], MAX_LEN, stdin)) return 0;
        int len = strlen(convenient[i]);
        if(len >0 && convenient[i][len-1] == '\n') convenient[i][len-1] = '\0';
    }

    int count =0;
    char place[MAX_LEN];
    for(int i=0;i<m;i++){
        if(!fgets(place, MAX_LEN, stdin)) break;
        int len = strlen(place);
        if(len >0 && place[len-1] == '\n') place[len-1] = '\0';
        for(int j=0;j<n;j++) {
            if(strcmp(place, convenient[j]) ==0){
                count++;
                break;
            }
        }
    }
    printf("%d", count);
}