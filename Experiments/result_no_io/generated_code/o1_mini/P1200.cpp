#include<stdio.h>
#include<string.h>

int compute_mod(const char *s) {
    int res = 1;
    for(int i=0;i<strlen(s);i++) {
        res = (res * (s[i]-'A'+1)) % 47;
    }
    return res;
}

int main(){
    char comet[7], team[7];
    scanf("%s %s", comet, team);
    int a = compute_mod(comet);
    int b = compute_mod(team);
    if(a == b) printf("GO\n");
    else printf("STAY\n");
}