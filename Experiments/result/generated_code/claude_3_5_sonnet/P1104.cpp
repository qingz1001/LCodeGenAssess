#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_NAME 20

typedef struct {
    char name[MAX_NAME];
    int year;
    int month;
    int day;
} Person;

int compare(const void *a, const void *b) {
    Person *p1 = (Person *)a;
    Person *p2 = (Person *)b;
    
    if (p1->year != p2->year)
        return p1->year - p2->year;
    if (p1->month != p2->month)
        return p1->month - p2->month;
    if (p1->day != p2->day)
        return p1->day - p2->day;
    return 1;  // 如果生日相同，保持输入的顺序
}

int main() {
    int n;
    scanf("%d", &n);
    
    Person people[MAX_N];
    
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", people[i].name, &people[i].year, &people[i].month, &people[i].day);
    }
    
    qsort(people, n, sizeof(Person), compare);
    
    for (int i = n - 1; i >= 0; i--) {
        printf("%s\n", people[i].name);
    }
    
    return 0;
}