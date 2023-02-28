#ifndef CADDIE_KERNEL_HASH_MAP_H
#define CADDIE_KERNEL_HASH_MAP_H
#include "types_caddie.hpp"

namespace caddie {

u32 MurmurHash(const void* key, int len);

/**
 * @brief Hash function template
 * TODO: Prevent automatic specialization for non-primitive key types
 */
template <typename T> class Hasher {
    u32 operator()(const T& key) {
        return MurmurHash(reinterpret_cast<const void*>(&key), sizeof(T));
    }
};

template <typename TKey, typename TValue> class HashMap {
public:
    struct Pair {
        TKey key;
        TValue value;
        bool used;
        struct Pair* next;
    };

    static const int scDefaultCapacity = 32;

public:
    HashMap(int capacity = scDefaultCapacity)
        : mCapacity(capacity), mSize(0), mBuckets(NULL) {
        // Allocate buckets
        mBuckets = new Pair[mCapacity];
        CADDIE_ASSERT(mBuckets != NULL);
    }

    ~HashMap() { delete[] mBuckets; }

    TValue* operator[](const TKey& key) { return Find(key); }

    // Insert new (or update existing) pair in table
    void Insert(const TKey& key, const TValue& value, TValue* old = NULL) {
        // Calculate bucket index
        const int idx = Hasher<TKey>()(key) % mCapacity;

        // Find free pair
        Pair* last = NULL;
        Pair* it = Find_(key, last);

        // No free pair
        if (it == NULL) {
            // New pair
            Pair* p = new Pair();
            p->key = key;
            p->value = value;

            // Link
            last->next = p;
        }
        // Free pair (updating existing value)
        else {
            // Save old value
            if (old != NULL) {
                *old = it->value;
            }

            it->value = value;
        }
    }

    // Find value with specified key
    TValue* Find(const TKey& key) const {
        // Find pair
        Pair* last = NULL;
        return Find_(key, last);
    }

    // Check whether table contains value with specified key
    bool Contains(const TKey& key) { return Find(key) != NULL; }

private:
    Pair* Find_(const TKey& key, Pair*& last) {
        // Calculate bucket index
        const int idx = Hasher<TKey>()(key) % mCapacity;

        // Search bucket for key
        for (Pair* it = mBuckets[idx]; it != NULL && it->used; it = it->next) {
            if (it->key == key) {
                return it;
            }
            last = it;
        }

        return NULL;
    }

private:
    u32 mCapacity;
    u32 mSize;
    Pair* mBuckets;
};

} // namespace caddie

#endif
