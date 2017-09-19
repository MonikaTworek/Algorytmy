#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <sys/types.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <limits.h>

#define NUMBER_OF_TESTS 1

using namespace std;

int COMPARE = 0;
int SWITCH = 0;

int *generate_array(int n, int random);
void print_array(int* array, int n);
void radix(int* array, int log, int n);
int getNthDigitByBase(int number, int n, int base);
void countingSort(int *array, int sortedElementIndex, int base, int log, int n);
int getBiggestValue(int *array, int n);
void generateDataFile();
int randomizedSelect(int* array, int first, int last, int find, int log);
void generateRandomizedSelect();
int* lol_generate_array(int n);
void select(const vector<int> values, int k, int log);
int median(vector<int> vec, int log);
void generateSelect();
void generateDataFileQS();
void insertionSort(int *array, int startIndex, int endIndex);
void quickSortMM(int *array, int arraySize);
void quickSortDividerMM(int *array, int startIndex, int endIndex);
void selectPivot(int *array, int startIndex, int endIndex);
void swap(int *array, int firstElementIndex, int secondElementIndex);
void quickSort(int *array, int i);
int medianDistanceFromBeginning(int number);
void quickSortDivider(int *array, int startIndex, int endIndex);


int main() {

    printf("Wybierz: \n"
                   "[1] RADIX SORT \n"
                   "[2] RADIX SORT TEST \n"
                   "[3] RANDOMIZED SELECT \n"
                   "[4] RANDOMIZED SELECT TEST \n"
                   "[5] SELECT \n"
                   "[6] SELECT TEST \n"
                   "[7] QUICK SORT SELECT TEST \n");
    int choose;
    scanf("%d", &choose);

    int N;
    int arrayType;
    int* array;
    int k;
    int find;
    vector <int> myvector;

    switch(choose){
        case 1:
            printf("[1] losowy ciag \n[2] posortowany malejaco \n");
            scanf("%d", &arrayType);

            printf("Podaj wielkosc  \n");
            scanf("%d", &N);

            array = generate_array(N, arrayType);
            radix(array, 1, N);
            break;

        case 2:
            generateDataFile();
            break;
        case 3:
            printf("Podaj wielkosc \n");
            scanf("%d", &N);
            printf("[1] losowy ciag \n[2] losowy ciag roznowartosiowy \n");
            scanf("%d", &arrayType);
            if(arrayType==1)
                array = generate_array(N, arrayType);
            else
                array = lol_generate_array(N);

            printf("Podaj statystyke pozycyjna \n");
            scanf("%d", &k);
            find =randomizedSelect(array,0,N-1,k,1);
            printf("%d \n", find);
            system("PAUSE");
            printf("tablica posortowana: \n");

            for(int j=1; j<N; j++)
            {
                int key = array[j];
                int i = j -1;
                while(i>=0 && array[i]>key)
                {
                    array[i+1] = array[i];
                    i--;
                }
                array[i+1] = key;
            }
            print_array(array, N);
            break;
        case 4:
            generateRandomizedSelect();
            break;
        case 5:
            printf("Podaj wielkosc \n");
            scanf("%d", &N);
            printf("[1] losowy ciag \n[2] losowy ciag roznowartosiowy \n");
            scanf("%d", &arrayType);
            if(arrayType==1)
                for(int i=0; i<N; i++)
                    myvector.push_back(rand()%N);
            else{
                for (int i=0; i<N; i++)
                    myvector.push_back(i);
                for (int i=0; i<N; i++)
                {
                    int first = rand()%N;
                    int second = rand()%N;
                    int temp = myvector[first];
                    myvector[first] = myvector[second];
                    myvector[second] = temp;
                }
            }

            printf("Podaj statystyke pozycyjna \n");
            scanf("%d", &k);
            select(myvector,N-k+1,1);
            system("PAUSE");
            printf("\ntablica posortowana: \n");
            for(int j=1; j<N; j++) {
                int key = myvector[j];
                int i = j -1;
                while(i>=0 && myvector[i]>key) {
                    myvector[i+1] = myvector[i];
                    i--;
                }
                myvector[i+1] = key;
            }

            for(int i=0; i<N; i++)
                cout << myvector[i] << " ";
            break;
        case 6:
            generateSelect();
            break;
        case 7:
            generateDataFileQS();
            break;
    }
    system("PAUSE");
    return 0;
}

int *generate_array(int n, int random) {
    int *array = (int *)malloc(sizeof(int) * (n + 1));
    if (random){
        int seed;
        time_t t;
        seed = time(&t);
        srand((unsigned int)seed);
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

void radix(int* array, int log, int n){
    if (log) {
        printf("RADIX: Start radix sort na:\n");
        print_array(array, n);
    }

    if(n == 1) {
        if (log) {
            printf("RADIX: Bawimy sie na jednoelementowej liscie:\n");
            print_array(array, n);
        }
        return;
    }
    COMPARE++;
    int max = getBiggestValue(array, n);
    int base = (int)ceil(sqrt(max));
    int digitsNumber = 3;

    for (int i = 1; i <= digitsNumber; i++) {
        COMPARE++;
        if (log) printf("RADIX: Uruchamiamy counting sort po %d element\n", i);
        countingSort(array, i, base, log, n);
    }
}

void countingSort(int *array, int sortedElementIndex, int base, int log, int n) {
    if (log) printf("COUNTING SORT: Poradkujemy po %d index\n", sortedElementIndex);
    COMPARE++;
    int positionsArray[base + 1];

    memset(positionsArray, 0, sizeof(long) * (base + 1));

    for (int i = 0; i < n; i++) {
        positionsArray[getNthDigitByBase(array[i], sortedElementIndex, base)]++;
    }

    if (log) {
        printf("COUNTING SORT: positionsArray wyglada tak:\n");
        print_array(positionsArray, base);
    }

    int lastNonZeroNumber;
    int i = 0;

    while (i < base) {
        lastNonZeroNumber = positionsArray[i];
        do {
            i++;
        } while (positionsArray[i] == 0);
        positionsArray[i] += lastNonZeroNumber;
    }

    if (log) {
        printf("COUNTING SORT:Dodajemy poprzedni element od lewej do prawej:\n");
        printf("COUNTING SORT: pozycje elementow zostaly podsumowane:\n");
        print_array(positionsArray, base);
    }

    int orderedArray[n];

    if (log) {
        print_array(positionsArray, base);
        printf("COUNTING SORT: pozycje wygenerowane:\n");
    }


    for (int j = n - 1; j >= 0; j--) {
        int elementAtNthIndex = getNthDigitByBase(array[j], sortedElementIndex, base);
        orderedArray[positionsArray[elementAtNthIndex] - 1] = array[j];
        SWITCH++;
        COMPARE++;
        positionsArray[elementAtNthIndex]--;
    }

    if (log) {
        printf("COUNTING SORT: Wygenerowano (posortowano po %d index):\n", sortedElementIndex);
        printf("COUNTING SORT: orderedArray wygenerowano:\n");
        print_array(orderedArray, n);
    }

    memcpy(array, orderedArray, n * sizeof(int));
    return;
}

int getNthDigitByBase(int number, int n, int base) {
    return ((number % (int) (pow(base, n))) / (int) pow(base, n - 1));
}

int getBiggestValue(int *array, int n) {
    int max = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > max) max = array[i];

    }
    return max;
}

void generateDataFile() {
    int n=100000;
    unsigned long long swapsSum = 0;
    unsigned long long comparisonsSum = 0;
    int *array;

    printf("Generating stats for RADIX SORT...\n");
    FILE *f = fopen("radix_sort_swaps.csv", "w");
    FILE *g = fopen("radix_sort_comps.csv", "w");

    int maxArraySize = n;
    for (int i = 100; i < maxArraySize; i += 100) {
        n = i;
        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            array = generate_array(n, 1);

            COMPARE = 0;
            SWITCH = 0;

            radix(array,0,n);
            free(array);

            swapsSum += SWITCH;
            comparisonsSum += COMPARE;
        }
        printf("%d / 100000\n", i);

        fprintf(f, "%d %llu\n", i, swapsSum / NUMBER_OF_TESTS);
        fprintf(g, "%d %llu\n", i, comparisonsSum / NUMBER_OF_TESTS);
        swapsSum = 0;
        comparisonsSum = 0;
    }
    fclose(f);
    fclose(g);
    printf("Stats for RADIX SORT generated...\n");
}

int randomizedSelect(int* array, int first, int last, int find, int log) {
    if (first == last) {
        if(log)
            printf("tablica ma jeden element - znalazlem %d \n", array[first]);
        return array[first];
    }
    srand(time(NULL));
    int r = first + rand() % (last-first+1);
    int temp = array[first];
    array[first] = array[r];
    array[r] = temp;
    if(log){
        cout <<"Zamienilem " << array[r] <<" z " << array[first] << " (pierwszy)" << endl;
    }
    int i = first;
    COMPARE++;
    for(int j=first+1; j<=last; j++) {
        COMPARE++;
        if(array[j] < array[first]) {
            if(log)
                cout << "Zamiany - " << array[i] << " i " << array[j] << endl;
            COMPARE++;
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    if(log)
        cout << "Zamiany - " << array[i] << " i " << array[first] << endl;
    temp = array[i];
    array[i] = array[first];
    array[first] = temp;
    int k = i - first + 1;
    if (find == k) {
        if(log)
            cout << "znodlem!" << endl;
        return array[i];
    }
    else if (find < k) {
        if(log)
            cout << "ida w lewo" << endl;
        COMPARE++;
        return randomizedSelect(array, first, i-1, find, log);
    }
    else {
        if(log)
            cout << "ida w prawo" << endl;
        return randomizedSelect(array, i+1, last, find - k, log);
    }
}

void generateRandomizedSelect(){
    printf("Generating stats for RANDOMIED SELECT...\n");
    FILE *f = fopen("randomized_min.csv", "w");
    FILE *g = fopen("randomized_max.csv", "w");
    FILE *h = fopen("randomized_avg.csv", "w");
    for (int i=100; i<=100000; i+=100) {
        srand(time(NULL));

        int howMany = 100;
        int lol[howMany];
        long avg = 0;
        long min = 214483647;//milion pięćset sto dziewięććset
        long max = 0;

        for (int j=0; j<howMany; j++)
            lol[j] = rand()%i+1;
        for (int j=0; j<howMany; j++) {
            int array[i];
            for (int k=0; k<i; k++)
                array[k] = k;
            for (int k=0; k<i; k++) {
                int random1 = rand()%i;
                int random2 = rand()%i;
                int temp = array[random1];
                array[random1] = array[random2];
                array[random2] = temp;
            }
            COMPARE=0;
            randomizedSelect(array, 0, i-1, lol[j],0);
            if (COMPARE < min)
                min = COMPARE;
            if (COMPARE > max)
                max = COMPARE;
            avg += COMPARE;
        }
        avg /= howMany;
        fprintf(f, "%d %llu\n", i, min);
        fprintf(g, "%d %llu\n", i, max);
        fprintf(h, "%d %llu\n", i, avg);
    }
    fclose(f);
    fclose(g);
    fclose(h);
}

int* lol_generate_array(int N){
    int *array = (int *)malloc(sizeof(int) * (N + 1));
    for (int i = 0; i < N; i++)
        array[i] = i;
    for (int i = 0; i < N; i++) {
        int first = rand() % N;
        int second = rand() % N;
        int temp = array[first];
        array[first] = array[second];
        array[second] = temp;
    }
    return array;
}

int median(vector<int> vec, int log) {
    int median;
    size_t size = vec.size();
    median = vec[(size/2)];
    if(log)
        cout<<"wybralem mediane "<<median<<endl;
    return median;
}

void select(const vector<int> values, int k, int log) {
    vector< vector<int> > vec2D;
    int count = 0;
    COMPARE++;
    while (count != values.size()) {
        COMPARE++;
        int countRow = 0;
        vector<int> row;
        COMPARE++;
        while ((countRow < 5) && (count < values.size())) {
            COMPARE++;
            row.push_back(values[count]);
            count++;
            countRow++;
        }
        vec2D.push_back(row);
    }
    if(log)
        cout<<"podzielilem na 5 tablice"<<endl;
    vector<int> medians;
    COMPARE++;
    for (int i = 0; i < vec2D.size(); i++)
    {
        int n = median(vec2D[i], log);
        medians.push_back(n);
    }
    int m = median(medians, log);
    if(log)
        cout<<"Dziele na wieksze od mediany i mniejsze"<<endl;
    vector<int> L1, L2;
    bool nd = false;
    COMPARE++;
    for (int i = 0; i < vec2D.size(); i++) {
        COMPARE++;
        for (int j = 0; j < vec2D[i].size(); j++) {
            COMPARE++;
            if (vec2D[i][j] > m)
                L1.push_back(vec2D[i][j]);
            else if (vec2D[i][j] < m)
                L2.push_back(vec2D[i][j]);
        }
    }
    COMPARE+=3;
    if ((k - 1) == L1.size())
        cout << endl << endl << "Pod szukanym numerem jest " << m << endl << endl;
    else if (k <= L1.size()) {
        if(log)
            cout<<"Szukam na prawo"<<endl;
        return select(L1, k, log);
    }else if (k > (L1.size() + 1))
    {
        if(log)
            cout<<"Szukam na lewo"<<endl;
        return select(L2, k-((int)L1.size())-1, log);
    }

}

void generateSelect(){
    printf("Generating stats for RANDOMIED SELECT...\n");
    FILE *f = fopen("select_min.csv", "w");
    FILE *g = fopen("select_max.csv", "w");
    FILE *h = fopen("select_avg.csv", "w");
    int N=100000;
    for (int i=100; i<=N; i+=100) {
        srand(time(NULL));
        int howMany = 100;
        vector <int> lol;
        long avg = 0;
        long min = 214483647;//milion pięćset sto dziewięććset
        long max = 0;
        vector <int> array;
        for (int j=0; j<howMany; j++)
            lol.push_back(rand()%i+1);
        for (int j=0; j<howMany; j++) {
            for (int k=0; k<i; k++)
                array[k] = k;
            for (int k=0; k<i; k++) {
                int random1 = rand()%i;
                int random2 = rand()%i;
                int temp = array[random1];
                array[random1] = array[random2];
                array[random2] = temp;
            }
            COMPARE=0;
            select(array,N-i+1,0);
            if (COMPARE < min)
                min = COMPARE;
            if (COMPARE > max)
                max = COMPARE;
            avg += COMPARE;
        }
        avg /= howMany;
        fprintf(f, "%d %llu\n", i, min);
        fprintf(g, "%d %llu\n", i, max);
        fprintf(h, "%d %llu\n", i, avg);
    }
    fclose(f);
    fclose(g);
    fclose(h);
}

void generateDataFileQS() {

    unsigned long long operationsSum = 0;
    int operationsMax = 0;
    int operationsMin = INT_MAX;
    int *array;
    int maxArraySize;

    printf("Generating stats for quickSort (random pivot).\n");

    FILE* f = fopen("qs_rand_100_10000.csv", "w");
    FILE* min = fopen("qs_rand_100_10000_min.csv", "w");
    FILE* max = fopen("qs_rand_100_10000_max.csv", "w");

    maxArraySize = 10000;
    for (int i = 100; i < maxArraySize; i += 100) {
        for (int j = 0; j < NUMBER_OF_TESTS; j++) {

            array = generate_array(i,0);


            COMPARE = 0;
            quickSort(array, i);
            free(array);

            operationsSum += COMPARE;
            if(COMPARE > operationsMax) operationsMax = COMPARE;
            if(COMPARE < operationsMin) operationsMin = COMPARE;
        }

        printf("%d / %d\n", i, maxArraySize);
        fprintf(f, "%d %llu\n", i, operationsSum / NUMBER_OF_TESTS);
        fprintf(min, "%d %llu\n", i, operationsMin);
        fprintf(max, "%d %llu\n", i, operationsMax);
        operationsMax = 0;
        operationsMin = INT_MAX;
        operationsSum = 0;
        COMPARE = 0;
    }

    fclose(f);
    fclose(min);
    fclose(max);

    printf("Generating stats for quickSort (median of medians).\n");

    f = fopen("qs_mm_100_10000.csv", "w");
    min = fopen("qs_mm_100_10000_min.csv", "w");
    max = fopen("qs_mm_100_10000_max.csv", "w");

    maxArraySize = 10000;
    for (int i = 100; i < maxArraySize; i += 100) {
        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            array = generate_array(i,0);

            COMPARE = 0;
            quickSortMM(array,i);
            free(array);

            operationsSum += COMPARE;
            if(COMPARE > operationsMax) operationsMax = COMPARE;
            if(COMPARE < operationsMin) operationsMin = COMPARE;
        }
        
        printf("%d / %d\n", i, maxArraySize);
        fprintf(f, "%d %llu\n", i, operationsSum / NUMBER_OF_TESTS);
        fprintf(min, "%d %llu\n", i, operationsMin);
        fprintf(max, "%d %llu\n", i, operationsMax);
        operationsMax = 0;
        operationsMin = INT_MAX;
        operationsSum = 0;
        COMPARE = 0;
    }

    fclose(f);
    fclose(min);
    fclose(max);
}

void insertionSort(int *array, int startIndex, int endIndex) {
    for (int i = startIndex + 1; i < endIndex + 1; i++) {
        for (int j = i - 1; j >= startIndex; j--) {
            if (array[j] > array[j + 1]) {
                swap(array, j, j + 1);
            } else break;
        }
    }
}

void quickSortMM(int *array, int arraySize) {
    quickSortDividerMM(array, 0, arraySize - 1);
}

void quickSortDividerMM(int *array, int startIndex, int endIndex) {

    if (startIndex >= endIndex) return;

    selectPivot(array, startIndex, endIndex);

    int pivotValue = array[startIndex];

    int leftSearchIndex = startIndex;
    int rightSearchIndex = endIndex;

    while (leftSearchIndex <= rightSearchIndex) {
        while (array[leftSearchIndex] < pivotValue) {
            leftSearchIndex++;
        }

        while (array[rightSearchIndex] > pivotValue) {
            rightSearchIndex--;
        }

        if (leftSearchIndex <= rightSearchIndex) {
            swap(array, leftSearchIndex, rightSearchIndex);
            COMPARE++;
            leftSearchIndex++;
            rightSearchIndex--;
        }
    }
    if (rightSearchIndex > startIndex) quickSortDividerMM(array, startIndex, rightSearchIndex);
    if (leftSearchIndex < endIndex) quickSortDividerMM(array, leftSearchIndex, endIndex);
}

void selectPivot(int *array, int startIndex, int endIndex) {
    int arraySize = endIndex - startIndex + 1;
    int numberOfGroups;
    numberOfGroups = ((arraySize % 5) ? arraySize / 5 + 1 : arraySize / 5);

    while (arraySize > 5) {

        int sizeOfLastGroup = (arraySize % 5) ? arraySize % 5 : 5;

        for (int i = 0; i < numberOfGroups - 1; i++) {
            insertionSort(array, (i * 5) + startIndex, ((i + 1) * 5 - 1) + startIndex);
        }

        insertionSort(array, ((numberOfGroups - 1) * 5) + startIndex,
                      ((numberOfGroups) * 5 - 1 - (5 - sizeOfLastGroup)) + startIndex);

        for (int i = 0; i < numberOfGroups - 1; i++) {
            swap(array, i + startIndex, (5 * i + 2) + startIndex);
        }
        swap(array, (numberOfGroups - 1) + startIndex,
             (5 * (numberOfGroups - 1) + medianDistanceFromBeginning(sizeOfLastGroup)) + startIndex);

        arraySize = numberOfGroups;

        numberOfGroups = ((arraySize % 5) ? arraySize / 5 + 1 : arraySize / 5);

    }

    insertionSort(array, 0 + startIndex, (arraySize - 1) + startIndex);

    swap(array, 0 + startIndex, (medianDistanceFromBeginning(arraySize)) + startIndex);
}

void swap(int *array, int firstElementIndex, int secondElementIndex) {
    int tmp = array[secondElementIndex];
    array[secondElementIndex] = array[firstElementIndex];
    array[firstElementIndex] = tmp;
}

void quickSort(int *array, int i) {
    quickSortDivider(array, 0, i - 1);
}

void quickSortDivider(int *array, int startIndex, int endIndex) {

    if (startIndex >= endIndex) return;
    int pivotIndex = startIndex;

    int pivotValue = array[pivotIndex];
    int leftSearchIndex = startIndex;
    int rightSearchIndex = endIndex;

    while (leftSearchIndex <= rightSearchIndex) {
        while (array[leftSearchIndex] < pivotValue) {
            leftSearchIndex++;
        }

        while (array[rightSearchIndex] > pivotValue) {
            rightSearchIndex--;
        }

        if (leftSearchIndex <= rightSearchIndex) {
            swap(array, leftSearchIndex, rightSearchIndex);
            COMPARE++;
            leftSearchIndex++;
            rightSearchIndex--;
        }
    }

    if (rightSearchIndex > startIndex) quickSortDivider(array, startIndex, rightSearchIndex);
    if (leftSearchIndex < endIndex) quickSortDivider(array, leftSearchIndex, endIndex);
}

int medianDistanceFromBeginning(int number) {
    if (number == 1 || number == 2) return 0;
    else if (number == 3 || number == 4) return 1;
    else return 2;
}