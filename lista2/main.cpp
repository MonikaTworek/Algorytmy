#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <sys/types.h>
#include <time.h>


int COMPARE = 0;
int SWITCH = 0;

void swap(int *i, int *j);
int partition(int* array, int start, int end);
void merge(int *array, int start, int middle, int end);

int *generate_array(int n, boolean random);
int* copy_array(int *array, int n);
void print_array(int *array, int n);
void freeArray(int * array, int size);

void insertion_sort(int *array, int start, int endd);
void merge_sort(int *array, int startIndex, int endIndex);
void quick_sort(int* array, int start, int end);
void dual_pivot_quicksort(int* array, int start, int endd);

void insert_merge(int* array, int startIndex, int endIndex);
void insert_quick(int* array, int start, int end);

void insertion_test();
void merge_sort_test();
void quick_sort_test();

void insert_quick_sort_test();
void insert_merge_sort_test();
void double_pivot_sort_test();


int main()
{
    printf("Wybierz: \n"
                   " [i] - insertionTry, \n"
                   " [m] - mergeTry, \n"
                   " [q] - quickTry\n"
                   " [a] - insertMergeTry, \n"
                   " [b] - insertQuickTry \n"
                   " [c] - merge,quick,insert test (csv export) \n"
                   " [k] - insertQuick, insertMerge (csv export) \n"
                   " [h] - dualPivotTry, \n"
                   " [f] - doublePivot test (csv export)\n");
    char choose;
    scanf("%c", &choose);

    if (choose == 'c' || choose == 'k' || choose == 'f') {
        switch (choose) {
            case 'c':
                insertion_test();
                merge_sort_test();
                quick_sort_test();
                break;
            case 'k':
                insert_merge_sort_test();
                insert_quick_sort_test();
                break;
            case 'f':
                double_pivot_sort_test();
            default:break;
        }
    }
    else {
        printf("Wybierz \n"
                       "[1] - randomo list \n"
                       "[0] - desc list \n");
        int arrayType;
        scanf("%d", &arrayType);

        printf("Wybierz [N] \n");
        int N;
        scanf("%d", &N);
        int* array;
        array = generate_array(N, TRUE);
        int* array1 = copy_array(array, N);

        clock_t start;
        clock_t end;
        float seconds;
        clock_t start1;
        clock_t end1;
        float seconds1;

        switch (choose) {
            case 'i':
                insertion_sort(array, 0, N);
                print_array(array, N);
                break;
            case 'm':
                merge_sort(array, 0, N - 1);
                print_array(array, N);
                break;
            case 'q':
                quick_sort(array, 0, N - 1);
                print_array(array, N);
                break;
            case 'h':
                dual_pivot_quicksort(array, 0, N - 1);
                print_array(array, N);
                break;
            case 'a':
                start = clock();
                merge_sort(array, 0, N - 1);
                end = clock();
                seconds = (float)(end - start) / CLOCKS_PER_SEC;
                printf("tylko merge: %f\n", seconds);
                //print_array(array1,N);
                start1 = clock();
                insert_merge(array1, 0, N - 1);
                end1 = clock();
                seconds1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
                printf("merge z insert: %f\n", seconds1);
                //print_array(array1,N);
                break;
            case 'b':
                start = clock();
                quick_sort(array, 0, N - 1);
                end = clock();
                seconds = (float)(end - start) / CLOCKS_PER_SEC;
                printf("tylko quick: %f\n", seconds);

                //print_array(array1,N);
                start1 = clock();
                insert_quick(array1, 0, N - 1);
                end1 = clock();
                seconds1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
                printf("quick z insert: %f\n", seconds1);
                //print_array(array1,N);
                break;
            default:break;
        }
    }

    system("PAUSE");
    return 0;
}

void swap(int *i, int *j) {
    int t = *i;
    *i = *j;
    *j = t;
}

int partition(int* array, int start, int end) {
    int piwot = array[start];
    SWITCH++;
    int i = start, j = start + 1;
    for (j; j <= end; j++) {
        if (piwot > array[j]) {
            COMPARE++;
            i++;
            swap(&array[i], &array[j]);
            SWITCH += 3;
        }
    }
    swap(&array[i], &array[start]);
    SWITCH++;
    return i;
}

void quick_sort(int* array, int start, int end) {//z piwotem, mniejsze przed, większe za, piwot na miejscu
    if (start >= end)
        return;
    int pivot_idx = partition(array, start, end);
    quick_sort(array, start, pivot_idx - 1);
    quick_sort(array, pivot_idx + 1, end);
}

void merge(int *array, int start, int middle, int end) {
    int* pom = (int*)malloc(sizeof(int)*(end - start + 1));
    int start_iterator = start, middle_iterator = middle + 1, pom_index = 0;
    while (start_iterator <= middle && middle_iterator <= end) {
        if (array[start_iterator] > array[middle_iterator]){
            pom[pom_index] = array[middle_iterator];
            middle_iterator++;
            pom_index++;
        }
        else {
            pom[pom_index] = array[start_iterator];
            start_iterator++;
            pom_index++;
        }
        COMPARE++;
        SWITCH++;
    }
    while (start_iterator <= middle) {
        pom[pom_index] = array[start_iterator];
        start_iterator++;
        pom_index++;
        COMPARE++;
        SWITCH++;
    }
    while (middle_iterator <= end) {
        pom[pom_index] = array[middle_iterator];
        middle_iterator++;
        pom_index++;
        COMPARE++;
        SWITCH++;
    }
    int k = 0;
    for (int i = start; i <= end; i++) {
        array[i] = pom[k];
        k++;
        SWITCH++;
    }
    freeArray(pom, end - start);
}

void merge_sort(int *array, int startIndex, int endIndex) {//sortowanie przez scalanie
    if (endIndex - startIndex > 0) {
        int mid = (startIndex + endIndex + 1) / 2;
        merge_sort(array, startIndex, mid - 1);
        merge_sort(array, mid, endIndex);
        merge(array, startIndex, mid - 1, endIndex);
    }
}

void insertion_sort(int *array, int start, int endd) {//jak karty
    int current_compared, j;
    for (int i = endd - 2; i >= start; i--) {
        current_compared = array[i]; // pierwszy elt przed listą uporządkowaną
        j = i + 1; // index pierwszego el. listy uporzadkowanej - puste miejsce
        while (current_compared > array[j] && j < endd) {
            array[j - 1] = array[j];
            j++;
            SWITCH++;
            COMPARE++;
        }
        array[j - 1] = current_compared;
        SWITCH++;
    }
}

void dual_pivot_quicksort(int* array, int start, int endd) {//dwa piwoty
    if (endd > start) {
        if (array[start] > array[endd]) swap(&array[start], &array[endd]);
        COMPARE++;
        int p = array[start], q = array[endd];
        SWITCH += 5;
        int piwot1 = start + 1, piwot2 = endd - 1, index = piwot1;
        while (index <= piwot2) {
            if (array[index] < p) {
                swap(&array[index], &array[piwot1]);
                ++piwot1;
            }
            else if (array[index] >= q) {
                while (array[piwot2] > q && index < piwot2) {
                    --piwot2;
                    COMPARE++;
                }
                swap(&array[index], &array[piwot2]);
                SWITCH += 3;
                --piwot2;
                if (array[index] < p) {
                    swap(&array[index], &array[piwot1]);
                    SWITCH += 3;
                    ++piwot1;
                }
            }
            COMPARE++;
            ++index;
        }
        --piwot1; ++piwot2;

        swap(&array[start], &array[piwot1]); swap(&array[endd], &array[piwot2]);
        SWITCH += 6;
        dual_pivot_quicksort(array, start, piwot1 - 1);
        dual_pivot_quicksort(array, piwot1 + 1, piwot2 - 1);
        dual_pivot_quicksort(array, piwot2 + 1, endd);
    }
}

void freeArray(int * array, int size) {
    if (size>0) {
        while (size--)
            free(&array[size]);
    }
}

int* copy_array(int *array, int n) {
    int* array1 = (int *)malloc(sizeof(int)*(n + 1));
    for (int i = 0; i < n; i++)
        array1[i] = array[i];
    return array1;
}

void insert_merge(int* array, int startIndex, int endIndex) {
    if (endIndex - startIndex > 15) {
        int mid = (startIndex + endIndex + 1) / 2;
        insert_merge(array, startIndex, mid - 1);
        insert_merge(array, mid, endIndex);
        merge(array, startIndex, mid - 1, endIndex);
    }
    else if (endIndex - startIndex > 0)
        insertion_sort(array, startIndex, endIndex + 1);
}

void insert_quick(int* array, int start, int end) {
    if (start >= end)
        return;

    if (end - start > 16) {
        int pivot_idx = partition(array, start, end);
        insert_quick(array, start, pivot_idx - 1);
        insert_quick(array, pivot_idx + 1, end);
    }
    else
        insertion_sort(array, start, end + 1);
}

int *generate_array(int n, boolean random) {
    int *array = (int *)malloc(sizeof(int) * (n + 1));
    int seed;
    time_t t;
    seed = time(&t);
    srand((unsigned int)seed);
    if (random){
        for (int i = 0; i < n; i++)
            array[i] = rand();
    }
    else{
        for (int i = n; i >= 0; i--)
            array[n - i] = i;
    }

    array[n] = NULL;
    return array;
}

void print_array(int *array, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
}

void insertion_test() {
    unsigned long switchesAvg = 0;
    unsigned long comparsionsAvg = 0;

    FILE *f = fopen("insertionsort_operations.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "n; comparsionsAvg; switchesAvg\n");
    for (int i = 100; i <= 10000; i = i + 100) {
        for (int j = 0; j < 10; j++) {
            int *array = generate_array(i, 1);
            SWITCH = 0;
            COMPARE = 0;
            insertion_sort(array, 0, i);
            switchesAvg += SWITCH / 10;
            comparsionsAvg += COMPARE / 10;
            freeArray(array, i);
        }
        fprintf(f, "%d;%ld;%ld\n", i, comparsionsAvg, switchesAvg);
        comparsionsAvg = 0;
        switchesAvg = 0;
    }
    fclose(f);
}

void merge_sort_test() {
    unsigned long switchesAvg = 0;
    unsigned long comparsionsAvg = 0;

    FILE *f = fopen("mergesort_operations.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "n; comparsionsAvg; switchesAvg\n");
    for (int i = 100; i <= 100000; i = i + 100) {
        for (int j = 0; j < 10; j++) {
            int *array = generate_array(i, 1);
            SWITCH = 0;
            COMPARE = 0;
            merge_sort(array, 0, i - 1);
            switchesAvg += SWITCH / 10;
            comparsionsAvg += COMPARE / 10;
        }
        fprintf(f, "%d;%ld;%ld\n", i, comparsionsAvg, switchesAvg);
        comparsionsAvg = 0;
        switchesAvg = 0;
    }
    fclose(f);
}

void quick_sort_test() {
    unsigned long switchesAvg = 0;
    unsigned long comparsionsAvg = 0;

    FILE *f = fopen("quicksort_operations.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "n; comparsionsAvg; switchesAvg\n");
    for (int i = 100; i <= 100000; i = i + 100) {
        for (int j = 0; j < 10; j++) {
            int *array = generate_array(i, 1);
            SWITCH = 0;
            COMPARE = 0;
            quick_sort(array, 0, i - 1);
            switchesAvg += SWITCH / 10;
            comparsionsAvg += COMPARE / 10;
        }
        fprintf(f, "%d;%ld;%ld\n", i, comparsionsAvg, switchesAvg);
        comparsionsAvg = 0;
        switchesAvg = 0;
    }
    fclose(f);
}

void insert_quick_sort_test() {
    unsigned long switchesAvg = 0;
    unsigned long comparsionsAvg = 0;

    FILE *f = fopen("insertquick_operations.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "n; comparsionsAvg; switchesAvg\n");
    for (int i = 100; i <= 100000; i = i + 100) {
        for (int j = 0; j < 10; j++) {
            int *array = generate_array(i, 1);
            SWITCH = 0;
            COMPARE = 0;
            insert_quick(array, 0, i);
            switchesAvg += SWITCH / 10;
            comparsionsAvg += COMPARE / 10;
            freeArray(array, i);
        }
        fprintf(f, "%d;%ld;%ld\n", i, comparsionsAvg, switchesAvg);
        comparsionsAvg = 0;
        switchesAvg = 0;
    }
    fclose(f);
}

void insert_merge_sort_test() {
    unsigned long switchesAvg = 0;
    unsigned long comparsionsAvg = 0;

    FILE *f = fopen("insertmerge_operations.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "n; comparsionsAvg; switchesAvg\n");
    for (int i = 100; i <= 100000; i = i + 100) {
        for (int j = 0; j < 10; j++) {
            int *array = generate_array(i, 1);
            SWITCH = 0;
            COMPARE = 0;
            insert_merge(array, 0, i - 1);
            switchesAvg += SWITCH / 10;
            comparsionsAvg += COMPARE / 10;
            freeArray(array, i);
        }
        fprintf(f, "%d;%ld;%ld\n", i, comparsionsAvg, switchesAvg);
        comparsionsAvg = 0;
        switchesAvg = 0;
    }
    fclose(f);
}

void double_pivot_sort_test() {
    unsigned long switchesAvg = 0;
    unsigned long comparsionsAvg = 0;

    FILE *f = fopen("dualpivot_operations.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "n; comparsionsAvg; switchesAvg\n");
    for (int i = 100; i <= 100000; i = i + 100) {
        for (int j = 0; j < 10; j++) {
            int *array = generate_array(i, 1);
            SWITCH = 0;
            COMPARE = 0;
            dual_pivot_quicksort(array, 0, i - 1);
            switchesAvg += SWITCH / 10;
            comparsionsAvg += COMPARE / 10;
            freeArray(array, i);
        }
        fprintf(f, "%d;%ld;%ld\n", i, comparsionsAvg, switchesAvg);
        comparsionsAvg = 0;
        switchesAvg = 0;
    }
    fclose(f);
}
