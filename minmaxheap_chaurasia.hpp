/*
Author: Darsh Chaurasia

Date: 2024-03-14

Description: This header file contains the implementations of MinHeap and MaxHeap data structures. 
The MinHeap is a generic minimum priority queue implementation that supports insertion and deletion in O(log n) time. 
Similarly, the MaxHeap is a generic maximum priority queue implementation with the same time complexity characteristics.
Both data structures require that the types they are instantiated with have all comparison operators overloaded to ensure proper functionality.
These heap structures are suitable for efficient priority queue operations where elements need to be constantly retrieved in sorted order.
*/

// Include guard to prevent multiple inclusion of the header file
#ifndef MINMAXHEAP_CHAURASIA_HPP
#define MINMAXHEAP_CHAURASIA_HPP

#include <vector> // Include the vector container from the Standard Template Library (STL)
#include <stdexcept> // Include exceptions
#include <algorithm> // Include algorithm functions
#include <functional> // Include functional utilities

// Template declaration for MinHeap, requires the type T to be totally ordered
template<std::totally_ordered T>
class MinHeap {
private:
    std::vector<T> data; // Vector to store heap elements

    // Helper function to maintain heap property after insertion
    void bubbleUp(int index) {
        // Loop to correct the position of the newly added element
        while (index > 0) {
            int parentIndex = (index - 1) / 2; // Calculate parent index
            // If parent is greater, swap with child
            if (data[parentIndex] > data[index]) {
                std::swap(data[parentIndex], data[index]);
                index = parentIndex; // Update index to parent's index for next iteration
            } else {
                return; // If heap property is satisfied, exit loop
            }
        }
    }

    // Helper function to maintain heap property after deletion
    void bubbleDown(int index) {
        // Calculate indices of left and right children
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int smallest = index; // Assume current index is smallest

        // Find the smallest of the current, left child and right child
        if (leftChildIndex < static_cast<int>(data.size()) && data[leftChildIndex] < data[index]) {
            smallest = leftChildIndex;
        }

        if (rightChildIndex < static_cast<int>(data.size()) && data[rightChildIndex] < data[smallest]) {
            smallest = rightChildIndex;
        }

        // If smallest is not the current item, swap and continue down the heap
        if (smallest != index) {
            std::swap(data[index], data[smallest]);
            bubbleDown(smallest); // Recursively adjust the following tree
        }
    }

public:
    MinHeap() {} // Default constructor
    MinHeap(int initialSize) { // Constructor with initial size
        data.reserve(initialSize); // Reserve memory to optimize insertions
    }

    // Adds an item to the heap
    void enqueue(T item) {
        data.push_back(item); // Add new item to the end
        bubbleUp(data.size() - 1); // Adjust position to maintain heap property
    }

    // Removes the top (minimum) item from the heap
    void dequeue() {
        if (data.empty()) { // Check if heap is empty
            throw std::out_of_range("Cannot dequeue from an empty heap."); // Throw exception if empty
        }
        // Replace root with last element and remove the last element
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) {
            bubbleDown(0); // Adjust new root to maintain heap property
        }
    }

    // Returns the top (minimum) item without removing it
    T peek() const {
        if (data.empty()) { // Check if heap is empty
            throw std::out_of_range("Heap is empty."); // Throw exception if empty
        }
        return data.front(); // Return the first element
    }

    // Returns the number of elements in the heap
    int getSize() const {
        return data.size();
    }

    // Checks if the heap is empty
    bool isEmpty() const {
        return data.empty();
    }
};

// Template declaration for MaxHeap, similar to MinHeap but for maximum values
template<std::totally_ordered T>
class MaxHeap {
private:
    std::vector<T> data; // Vector to store heap elements

    // Similar to MinHeap but adjusts for maximum heap property
    void bubbleUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (data[parentIndex] < data[index]) {
                std::swap(data[parentIndex], data[index]);
                index = parentIndex;
            } else {
                return;
            }
        }
    }

    // Similar to MinHeap but adjusts for maximum heap property
    void bubbleDown(int index) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int largest = index;

        if (leftChildIndex < static_cast<int>(data.size()) && data[leftChildIndex] > data[index]) {
            largest = leftChildIndex;
        }

        if (rightChildIndex < static_cast<int>(data.size()) && data[rightChildIndex] > data[largest]) {
            largest = rightChildIndex;
        }

        if (largest != index) {
            std::swap(data[index], data[largest]);
            bubbleDown(largest);
        }
    }

public:
    MaxHeap() {} // Default constructor
    MaxHeap(int initialSize) { // Constructor with initial size
        data.reserve(initialSize); // Reserve memory to optimize insertions
    }

    // Adds an item to the heap, similar to MinHeap
    void enqueue(T item) {
        data.push_back(item);
        bubbleUp(data.size() - 1);
    }

    // Removes the top (maximum) item from the heap, similar to MinHeap
    void dequeue() {
        if (data.empty()) {
            throw std::out_of_range("Cannot dequeue from an empty heap.");
        }
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) {
            bubbleDown(0);
        }
    }

    // Returns the top (maximum) item without removing it, similar to MinHeap
    T peek() const {
        if (data.empty()) {
            throw std::out_of_range("Heap is empty.");
        }
        return data.front();
    }

    // Returns the number of elements in the heap, similar to MinHeap
    int getSize() const {
        return data.size();
    }

    // Checks if the heap is empty, similar to MinHeap
    bool isEmpty() const {
        return data.empty();
    }
};

#endif // MINMAXHEAP_CHAURASIA_HPP
