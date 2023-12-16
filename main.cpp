#include <iostream>
#include "prqueue.h"

int main() {
    prqueue<string> pq;

    // Enqueue some elements with priorities
    pq.enqueue("Ben", 1);
    pq.enqueue("Jen", 2);
    pq.enqueue("Sven", 2);
    pq.enqueue("Gwen", 3);

    // Print the priority queue using toString() function
    cout << "Priority Queue: " << pq.toString() << endl;
 
    // Peek at the next element without removing it
    //string peekValue = pq.peek();
    //cout << "Peeked Value: " << peekValue << endl;

    // Dequeue elements and print them
    while (pq.size() > 0) {
        string value;
        int priority;
        if (pq.next(value, priority)) {
            cout << "Priority " << priority << ", Value: " << value << endl;
        }
    }

    return 0;
}
