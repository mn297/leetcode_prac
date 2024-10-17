#include <queue>
#include <iostream>

using namespace std;

class MedianFinder
{
public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        if (max_heap.empty() || num <= max_heap.top())
        {
            max_heap.push(num);
        }
        else
        {
            min_heap.push(num);
        }

        // Balance the heaps so that max_heap has at most one more element than min_heap
        if (max_heap.size() > min_heap.size() + 1)
        {
            min_heap.push(max_heap.top());
            max_heap.pop();
        }
        else if (min_heap.size() > max_heap.size())
        {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

    double findMedian()
    {
        if (max_heap.size() == min_heap.size())
        {
            return (max_heap.top() + min_heap.top()) / 2.0;
        }
        else
        {
            return max_heap.top();
        }
    }

private:
    priority_queue<int> max_heap;                            // Max-heap for the left half of the numbers
    priority_queue<int, vector<int>, greater<int>> min_heap; // Min-heap for the right half of the numbers
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main()
{
    MedianFinder *medianFinder = new MedianFinder();
    medianFinder->addNum(1);
    medianFinder->addNum(2);
    cout << "Median: " << medianFinder->findMedian() << endl; // Returns 1.5
    medianFinder->addNum(3);
    cout << "Median: " << medianFinder->findMedian() << endl; // Returns 2.0

    delete medianFinder;
    return 0;
}
