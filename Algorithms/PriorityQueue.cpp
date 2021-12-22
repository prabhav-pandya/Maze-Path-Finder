#include "PriorityQueue.h"

using namespace std;

// return parent of A[i]
// don't call this function if i is already a root node
int PriorityQueue::PARENT(int i)
{
    return (i - 1) / 2;
}

// return left child of A[i]
int PriorityQueue::LEFT(int i)
{
    return (2 * i + 1);
}

// return right child of A[i]
int PriorityQueue::RIGHT(int i)
{
    return (2 * i + 2);
}

// Recursive Heapify-down algorithm
// the node at index i and its two direct children
// violates the heap property
void PriorityQueue::heapify_down(int i)
{
    // get left and right child of node at index i
    int left = LEFT(i);
    int right = RIGHT(i);

    int smallest = i;

    // compare A[i] with its left and right child
    // and find smallest value
    if (left < size() && A[left]->cost < A[i]->cost)
        smallest = left;

    if (right < size() && A[right]->cost < A[smallest]->cost)
        smallest = right;

    // swap with child having lesser value and
    // call heapify-down on the child
    if (smallest != i) {
        swap(A[i], A[smallest]);
        heapify_down(smallest);
    }
}

// Recursive Heapify-up algorithm
void PriorityQueue::heapify_up(int i)
{
    // check if node at index i and its parent violates
    // the heap property
    if (i && A[PARENT(i)]->cost > A[i]->cost)
    {
        // swap the two if heap property is violated
        swap(A[i], A[PARENT(i)]);

        // call Heapify-up on the parent
        heapify_up(PARENT(i));
    }
}

// return size of the heap
unsigned int PriorityQueue::size()
{
    return A.size();
}

// function to check if heap is empty or not
bool PriorityQueue::empty()
{
    return size() == 0;
}

// insert key into the heap
void PriorityQueue::push(point* key)
{
    // insert the new element to the end of the vector
    A.push_back(key);
    // get element index and call heapify-up procedure
    int index = size() - 1;
    heapify_up(index);
}

// function to remove element with lowest priority (present at root)
void PriorityQueue::pop()
{
    try {
        // if heap has no elements, throw an exception
        if (size() == 0)
            throw out_of_range("Vector<X>::at() : "
                               "index is out of range(Heap underflow)");

        // replace the root of the heap with the last element
        // of the vector
        A[0] = A.back();
        A.pop_back();

        // call heapify-down on root node
        heapify_down(0);
    }
        // catch and print the exception
    catch (const out_of_range& oor) {
        cout << "\n" << oor.what();
    }
}

// function to return element with lowest priority (present at root)
point* PriorityQueue::top()
{
    try {
        // if heap has no elements, throw an exception
        if (size() == 0)
            throw out_of_range("Vector<X>::at() : "
                               "index is out of range(Heap underflow)");

        // else return the top (first) element
        return A.at(0);	// or return A[0];
    }
        // catch and print the exception
    catch (const out_of_range& oor) {
        cout << "\n" << oor.what();
    }
}

int PriorityQueue::relaxation(point* p){

    vector<point*>::iterator it = A.begin();
    for(int i=0;i<A.size();i++) {
        if (A[i]->row == p->row && A[i]->col == p->col) {
            if (A[i]->cost > p->cost) {
                A[i]=p;
                heapify_up(i);
                return 1;
            }
        }
        it++;
    }
    return 0;
}