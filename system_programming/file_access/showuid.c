// showuid.c
#include <stdio.h>

int main(void) {
    printf("Real UID = %d, Eff UID = %d\n", getuid(), geteuid());
    return 0;
}