#pragma once
#include <vector>
// #include <utility>
#include "recipe.h"

using namespace std;

// Threshold for switching to Insertion Sort (typically between 10 and 20)
constexpr int INSERTION_THRESHOLD = 16;

// In-place Insertion Sort on slice arr[left..right]
void insertionSort(vector<Recipe>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        Recipe key = arr[i];
        int j = i - 1;
        // Sort descending by score
        while (j >= left && recipeRanksHigher(key, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(vector<Recipe>& arr, vector<Recipe>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (recipeRanksHigher(arr[i], arr[j])) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int idx = left; idx <= right; idx++) {
        arr[idx] = temp[idx];
    }
}

void hybridMergeSortHelper(vector<Recipe>& arr, vector<Recipe>& temp, int left, int right) {
    // Switch to Insertion Sort when the partition becomes small enough
    if (right - left + 1 <= INSERTION_THRESHOLD) {
        insertionSort(arr, left, right);
        return;
    }

    int mid = left + (right - left) / 2;
    hybridMergeSortHelper(arr, temp, left, mid);
    hybridMergeSortHelper(arr, temp, mid + 1, right);
    merge(arr, temp, left, mid, right);
}

void runMergeSort(vector<Recipe>& arr) {
    if (arr.size() <= 1) return;
    vector<Recipe> temp(arr.size());
    hybridMergeSortHelper(arr, temp, 0, static_cast<int>(arr.size()) - 1);
}

// Merge sort allocates one temporary Recipe vector alongside its input vector.
int mergeSortWorkingMemoryBytes(int recipeCount) {
    return recipeCount * sizeof(Recipe);
}

/**
Default mergeSort was taking way too long(46000ms) so I used insertion sort when the array gets small
enough, since insertion sort is really fast for small arrays. Idea obtained from the following 
stack-overflow thread: https://stackoverflow.com/questions/12590621/optimizing-mergesort
**/
