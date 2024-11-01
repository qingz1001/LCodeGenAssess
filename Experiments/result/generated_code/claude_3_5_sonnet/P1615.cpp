#include <stdio.h>
#include <string.h>

int timeToSeconds(char *time) {
    int h, m, s;
    sscanf(time, "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

int main() {
    char startTime[9], endTime[9];
    int n;
    
    scanf("%s", startTime);
    scanf("%s", endTime);
    scanf("%d", &n);
    
    int startSeconds = timeToSeconds(startTime);
    int endSeconds = timeToSeconds(endTime);
    
    int duration = endSeconds - startSeconds;
    int notebooks = duration * n;
    
    printf("%d\n", notebooks);
    
    return 0;
}