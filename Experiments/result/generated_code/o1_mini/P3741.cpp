#include <stdio.h>
#include <string.h>

int count_vks(char s[], int n)
{
    int count = 0;
    for(int i=0; i < n-1; i++) {
        if(s[i] == 'V' && s[i+1] == 'K')
            count++;
    }
    return count;
}

int main()
{
    int n;
    scanf("%d", &n);
    char s[101];
    scanf("%s", s);
    int max_count = count_vks(s, n);

    for(int i=0; i < n; i++) {
        char temp = s[i];
        if(s[i] == 'V')
            s[i] = 'K';
        else
            s[i] = 'V';
        int current_count = count_vks(s, n);
        if(current_count > max_count)
            max_count = current_count;
        s[i] = temp;
    }

    printf("%d\n", max_count);
    return 0;
}