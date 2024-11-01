#include <stdio.h>

int compute_mod(char *s) {
    int res = 1;
    for(int i = 0; s[i] != '\0'; i++) {
        res = (res * (s[i] - 'A' + 1)) % 47;
    }
    return res;
}

int main(){
    char comet[10], group[10];
    scanf("%s", comet);
    scanf("%s", group);
    int comet_mod = compute_mod(comet);
    int group_mod = compute_mod(group);
    if(comet_mod == group_mod)
        printf("GO\n");
    else
        printf("STAY\n");
    return 0;
}