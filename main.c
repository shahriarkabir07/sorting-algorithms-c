#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 1000

void printArray(int arr[], int n, const char* label) {
    printf("%s: [ ", label);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("]\n");
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void copyArray(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

void generateRandom(int arr[], int n, int maxVal) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % maxVal + 1;
}

double getTimeMs(clock_t start, clock_t end) {
    return ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
}


// Bubble Sort
void bubbleSort(int arr[], int n) {
    int pass, j;
    int swapped;

    for (pass = 0; pass < n - 1; pass++) {
        swapped = 0;

        for (j = 0; j < n - pass - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        if (!swapped) break;
    }
}


// Selection Sort
void selectionSort(int arr[], int n) {
    int i, j, minIndex;

    for (i = 0; i < n - 1; i++) {
        minIndex = i;

        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        if (minIndex != i)
            swap(&arr[i], &arr[minIndex]);
    }
}


// Insertion Sort
void insertionSort(int arr[], int n) {
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}


// Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int i, j, k;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) L[i] = arr[left + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else               arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}


// Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int j;

    for (j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low >= high) return;

    int pivotIndex = partition(arr, low, high);
    quickSort(arr, low, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, high);
}


void runDemo(const char* name,
             void (*sortFn)(int[], int),
             int original[], int n)
{
    int arr[MAX_SIZE];
    copyArray(original, arr, n);

    printf("\n------------------------------\n");
    printf(" %s\n", name);
    printf("------------------------------\n");
    printArray(arr, n, "Before");

    clock_t start = clock();
    sortFn(arr, n);
    clock_t end = clock();

    printArray(arr, n, "After ");
    printf("Time  : %.4f ms\n", getTimeMs(start, end));
}

void mergeSortWrapper(int arr[], int n) {
    mergeSort(arr, 0, n - 1);
}
void quickSortWrapper(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

void showMenu(void) {
    printf("\n============================================\n");
    printf("       SORTING ALGORITHMS  -  C\n");
    printf("============================================\n");
    printf(" 1. Bubble Sort    (O(n^2))\n");
    printf(" 2. Selection Sort (O(n^2))\n");
    printf(" 3. Insertion Sort (O(n^2))\n");
    printf(" 4. Merge Sort     (O(n log n))\n");
    printf(" 5. Quick Sort     (O(n log n) avg)\n");
    printf(" 6. Compare ALL algorithms\n");
    printf(" 0. Exit\n");
    printf("--------------------------------------------\n");
    printf("Enter choice: ");
}

int main(void) {
    srand((unsigned int)time(NULL));

    int choice;
    int arr[MAX_SIZE];
    int n;

    do {
        showMenu();
        scanf("%d", &choice);

        if (choice == 0) break;
        if (choice < 1 || choice > 6) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        printf("\nEnter array size (or 0 for a random 10-element array): ");
        scanf("%d", &n);

        if (n <= 0) {
            n = 10;
            generateRandom(arr, n, 100);
        } else {
            if (n > MAX_SIZE) {
                printf("Size too large! Using max size %d.\n", MAX_SIZE);
                n = MAX_SIZE;
            }
            printf("Enter %d integers:\n", n);
            for (int i = 0; i < n; i++)
                scanf("%d", &arr[i]);
        }

        switch (choice) {
            case 1: runDemo("Bubble Sort",    bubbleSort,       arr, n); break;
            case 2: runDemo("Selection Sort", selectionSort,    arr, n); break;
            case 3: runDemo("Insertion Sort", insertionSort,    arr, n); break;
            case 4: runDemo("Merge Sort",     mergeSortWrapper, arr, n); break;
            case 5: runDemo("Quick Sort",     quickSortWrapper, arr, n); break;
            case 6:
                runDemo("Bubble Sort",    bubbleSort,       arr, n);
                runDemo("Selection Sort", selectionSort,    arr, n);
                runDemo("Insertion Sort", insertionSort,    arr, n);
                runDemo("Merge Sort",     mergeSortWrapper, arr, n);
                runDemo("Quick Sort",     quickSortWrapper, arr, n);
                break;
        }

    } while (choice != 0);

    printf("\nGoodbye!\n");
    return 0;
}
