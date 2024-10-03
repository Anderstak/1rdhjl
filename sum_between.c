#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_between(int array[], int N) {
    int index_first = index_first_zero(array);
    int index_last = index_last_zero(array, N);
    int sum_a = 0;
    while (index_first < index_last) {
        sum_a += abs(array[index_first++]);
    }
    return sum_a;
}