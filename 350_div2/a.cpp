#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    printf("%d %d", n/7*2+n%7/6, (n+5)/7*2+(n+5)%7/6);
    return 0;
}
