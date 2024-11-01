#include <stdio.h>
#include <string.h>

int main(){
    int s, t, w;
    scanf("%d %d %d", &s, &t, &w);
    char input[27];
    scanf("%s", input);
    int n = t - s +1;
    char letters[27];
    for(int i=0;i<n;i++) letters[i] = 'a' + s -1 + i;
    int pos[w];
    // Map input to pos
    for(int i=0;i<w;i++){
        for(int j=0;j<n;j++) if(input[i]==letters[j]) { pos[i]=j; break;}
    }
    // Find next combinations
    int count=0;
    while(count<5){
        // Find the rightmost position that can be incremented
        int i = w-1;
        while(i >=0 && pos[i] == n - w + i) i--;
        if(i <0) break;
        pos[i]++;
        for(int j=i+1; j<w; j++) pos[j] = pos[j-1]+1;
        // Print the combination
        char comb[27];
        for(int j=0; j<w; j++) comb[j] = letters[pos[j]];
        comb[w] = '\0';
        printf("%s\n", comb);
        count++;
    }
    return 0;
}