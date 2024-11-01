#include <stdio.h>
#include <string.h>

#define MAX_PLACE 20
#define MAX_LINE 101

int main(){
    int n, m;
    if(scanf("%d %d", &n, &m)!=2){
        return 1;
    }
    // Consume the newline after m
    getchar();
    char places[MAX_PLACE][MAX_LINE];
    int place_len[MAX_PLACE];
    for(int i=0;i<n;i++){
        if(fgets(places[i], MAX_LINE, stdin)==NULL){
            places[i][0]='\0';
        }
        // Remove trailing newline
        int len = strlen(places[i]);
        if(len >0 && places[i][len-1]=='\n'){
            places[i][len-1]='\0';
            len--;
        }
        place_len[i]=len;
    }
    char line[MAX_LINE];
    long long count=0;
    for(int i=0;i<m;i++){
        if(fgets(line, MAX_LINE, stdin)==NULL){
            break;
        }
        // Remove trailing newline
        int len = strlen(line);
        if(len >0 && line[len-1]=='\n'){
            line[len-1]='\0';
            len--;
        }
        for(int j=0;j<n;j++){
            if(len == place_len[j] && strcmp(line, places[j])==0){
                count++;
                break;
            }
        }
    }
    printf("%lld\n", count);
    return 0;
}