#include <stdio.h>
#include <string.h>

int main(){
    int map[256];
    memset(map, -1, sizeof(map));
    // left little: 0
    char left_little[] = "1QAZ";
    for(int i=0;i<strlen(left_little);i++) map[left_little[i]]=0;
    // left ring:1
    char left_ring[] = "2WSX";
    for(int i=0;i<strlen(left_ring);i++) map[left_ring[i]]=1;
    // left middle:2
    char left_middle[] = "3EDC";
    for(int i=0;i<strlen(left_middle);i++) map[left_middle[i]]=2;
    // left index:3
    char left_index[] = "45RTFGVB";
    for(int i=0;i<strlen(left_index);i++) map[left_index[i]]=3;
    // right index:4
    char right_index[] = "67YUHJNM";
    for(int i=0;i<strlen(right_index);i++) map[right_index[i]]=4;
    // right middle:5
    char right_middle[] = "8IK,";
    for(int i=0;i<strlen(right_middle);i++) map[right_middle[i]]=5;
    // right ring:6
    char right_ring[] = "9OL.";
    for(int i=0;i<strlen(right_ring);i++) map[right_ring[i]]=6;
    // right little:7
    char right_little[] = "0P;/-=[]\\'";
    for(int i=0;i<strlen(right_little);i++) map[right_little[i]]=7;

    // Read input
    char s[55];
    scanf("%s",s);

    int counts[8] = {0};

    for(int i=0; s[i]!=0;i++){
        char c = s[i];
        if(map[c]!=-1){
            counts[map[c]]++;
        }
    }

    for(int i=0;i<8;i++) printf("%d\n", counts[i]);

    return 0;
}