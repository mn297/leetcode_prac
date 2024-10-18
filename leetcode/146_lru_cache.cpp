#include <unordered_map>
#include <list>
#include <iostream>

using namespace std;

class LRUCache
{
public:
    LRUCache(int capacity) : capacity_(capacity)
    {
    }

    int get(int key)
    {
        auto it = cache_map_.find(key);
        if (it == cache_map_.end())
        {
            return -1; // Key not found
        }
        // Move the accessed element to the front of the list (most recently used)
        cache_items_.splice(cache_items_.begin(), cache_items_, it->second);
        return it->second->second;
    }

    void put(int key, int value)
    {
        auto it = cache_map_.find(key);
        if (it != cache_map_.end())
        {
            // Update the value and move it to the front
            it->second->second = value;
            cache_items_.splice(cache_items_.begin(), cache_items_, it->second);
        }
        else
        {
            // If the cache is at capacity, remove the least recently used item
            if (cache_items_.size() == capacity_)
            {
                int lru_key = cache_items_.back().first;
                cache_items_.pop_back();
                cache_map_.erase(lru_key);
            }
            // Insert the new item at the front
            cache_items_.emplace_front(key, value);
            cache_map_[key] = cache_items_.begin();
        }
    }

private:
    int capacity_;
    list<pair<int, int>> cache_items_;                             // Doubly linked list to maintain access order
    unordered_map<int, list<pair<int, int>>::iterator> cache_map_; // Hash map for O(1) access
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main()
{
    LRUCache lruCache(2); // Create an LRU Cache with capacity 2

    lruCache.put(1, 1);
    lruCache.put(2, 2);
    cout << "Get 1: " << lruCache.get(1) << endl; // Returns 1
    lruCache.put(3, 3);                           // Evicts key 2
    cout << "Get 2: " << lruCache.get(2) << endl; // Returns -1 (not found)
    lruCache.put(4, 4);                           // Evicts key 1
    cout << "Get 1: " << lruCache.get(1) << endl; // Returns -1 (not found)
    cout << "Get 3: " << lruCache.get(3) << endl; // Returns 3
    cout << "Get 4: " << lruCache.get(4) << endl; // Returns 4

    return 0;
}
