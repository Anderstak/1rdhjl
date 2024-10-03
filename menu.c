#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

int main() {
    int array[100];
    int N = 0, mode = 0;
    char c;
    scanf("%d%c", &mode, &c);
    do
    {
        scanf("%d%c", &array[N++], &c);
    } while (c != '\n');
    switch (mode)
    {
    case 0:
        printf("%d\n", index_first_zero(array));
        break;
    case 1:
        printf("%d\n", index_last_zero(array, N));
        break;
    case 2:
        printf("%d\n", sum_between(array, N));
        break;
    case 3:
        printf("%d\n", sum_before_and_after(array, N));
        break;
    default:
        puts("Данные некорректны");
    }
    return 0;
}

