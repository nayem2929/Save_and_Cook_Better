#pragma once

#include <vector>

#include "recipe.h"

using namespace std;

// Higher score means it's a better recipe. If it's tied, I just use the smaller id.
bool isBetterRecipe(Recipe first, Recipe second) {
    if (first.score > second.score) {
        return true;
    }

    if (first.score == second.score && first.id < second.id) {
        return true;
    }

    return false;
}

// This moves a recipe up if it's weaker than the one above it.
void moveUp(vector<Recipe>& heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (isBetterRecipe(heap[parent], heap[index]) == false) {
            break;
        }

        Recipe temp = heap[parent];
        heap[parent] = heap[index];
        heap[index] = temp;

        index = parent;
    }
}

// This moves the first recipe down until it's in the right spot again.
void moveDown(vector<Recipe>& heap, int index) {
    int heapSize = heap.size();

    while (true) {
        int leftChild = index * 2 + 1;
        int rightChild = index * 2 + 2;
        int weakest = index;

        if (leftChild < heapSize && isBetterRecipe(heap[weakest], heap[leftChild])) {
            weakest = leftChild;
        }

        if (rightChild < heapSize && isBetterRecipe(heap[weakest], heap[rightChild])) {
            weakest = rightChild;
        }

        if (weakest == index) {
            break;
        }

        Recipe temp = heap[index];
        heap[index] = heap[weakest];
        heap[weakest] = temp;

        index = weakest;
    }
}

// Instead of sorting everything, this just keeps the best K recipes.
vector<Recipe> findTopKWithMinHeap(vector<Recipe>& recipes, int topK) {
    vector<Recipe> heap;
    int recipeCount = recipes.size();

    if (topK <= 0) {
        return heap;
    }

    for (int i = 0; i < recipeCount; i++) {
        int currentHeapSize = heap.size();

        if (currentHeapSize < topK) {
            heap.push_back(recipes[i]);
            moveUp(heap, heap.size() - 1);
        }
        else if (isBetterRecipe(recipes[i], heap[0])) {
            heap[0] = recipes[i];
            moveDown(heap, 0);
        }
    }

    // The heap isn't in order yet, so this puts the small list in order for printing.
    int heapSize = heap.size();
    for (int i = 0; i < heapSize; i++) {
        for (int j = i + 1; j < heapSize; j++) {
            if (isBetterRecipe(heap[j], heap[i])) {
                Recipe temp = heap[i];
                heap[i] = heap[j];
                heap[j] = temp;
            }
        }
    }

    return heap;
}

// This shows how much space the heap is using. It only keeps K recipes at most.
int minHeapWorkingMemoryBytes(int recipeCount, int topK) {
    if (recipeCount < topK) {
        return recipeCount * sizeof(Recipe);
    }

    return topK * sizeof(Recipe);
}
