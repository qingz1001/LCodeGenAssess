#include <stdio.h>
#include <string.h>

int main(){
    int s, t, w;
    scanf("%d %d %d", &s, &t, &w);
    char str[27];
    scanf("%s", str);
    int C[26];
    for(int i=0;i<w;i++) {
        C[i] = str[i] - 'a' +1;
    }
    int count =0;
    while(count <5){
        // Find the rightmost element that can be incremented
        int i;
        for(i=w-1;i>=0;i--){
            if(C[i] < t - (w-1 -i)){
                C[i]++;
                for(int j=i+1;j<w;j++) {
                    C[j] = C[j-1]+1;
                }
                break;
            }
        }
        if(i <0){
            break;
        }
        // Convert C to string and print
        char out[27];
        for(int j=0;j<w;j++){
            out[j] = 'a' + C[j] -1;
        }
        out[w] = '\0';
        printf("%s\n", out);
        count++;
    }
    return 0;
}