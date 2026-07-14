#pragma once

#include <algorithm>
#include <iostream>
#include "Item.h"

template<typename T>
class Inventory {
private:
    T* pItems_;
    int capacity_;
    int size_;

    void Resize(int newCapacity) {
        T* pNewItems = new T[newCapacity];
        for (int index = 0; index < size_; ++index) {
            pNewItems[index] = pItems_[index];
        }

        delete[] pItems_;
        pItems_ = pNewItems;
        capacity_ = newCapacity;
    }

public:
    explicit Inventory(int capacity = 10)
        : pItems_(nullptr), capacity_(capacity > 0 ? capacity : 1), size_(0) {
        pItems_ = new T[capacity_];
    }

    ~Inventory() {
        delete[] pItems_;
    }

    Inventory(const Inventory& other)
        : pItems_(new T[other.capacity_]),
          capacity_(other.capacity_),
          size_(other.size_) {
        for (int index = 0; index < size_; ++index) {
            pItems_[index] = other.pItems_[index];
        }
    }

    Inventory& operator=(const Inventory& other) {
        if (this == &other) {
            return *this;
        }

        T* pNewItems = new T[other.capacity_];
        for (int index = 0; index < other.size_; ++index) {
            pNewItems[index] = other.pItems_[index];
        }

        delete[] pItems_;
        pItems_ = pNewItems;
        capacity_ = other.capacity_;
        size_ = other.size_;
        return *this;
    }

    bool AddItem(const T& item) {
        bool wasExpanded = false;
        if (size_ >= capacity_) {
            const int oldCapacity = capacity_;
            std::cout << "Adding item... (" << size_ << '/' << capacity_ << " full)\n";
            Resize(capacity_ * 2);
            wasExpanded = true;
            std::cout << "-> Inventory auto-expanded! (" << oldCapacity
                      << " -> " << capacity_ << ")\n";
        }

        pItems_[size_] = item;
        ++size_;

        if (wasExpanded) {
            std::cout << "-> Item added\n";
        }
        return true;
    }

    void SortItems() {
        std::sort(pItems_, pItems_ + size_, compareByPrice);
    }

    bool RemoveLastItem() {
        if (size_ <= 0) {
            return false;
        }

        --size_;
        pItems_[size_] = T{};
        return true;
    }

    bool RemoveItem(int index) {
        if (index < 0 || index >= size_) {
            return false;
        }

        for (int moveIndex = index; moveIndex < size_ - 1; ++moveIndex) {
            pItems_[moveIndex] = pItems_[moveIndex + 1];
        }

        return RemoveLastItem();
    }

    void PrintAllItems() const {
        for (int index = 0; index < size_; ++index) {
            std::cout << index + 1 << ". ";
            pItems_[index].PrintInfo();
        }
    }

    int GetSize() const {
        return size_;
    }

    int GetCapacity() const {
        return capacity_;
    }

    const T* GetItem(int index) const {
        if (index < 0 || index >= size_) {
            return nullptr;
        }

        return &pItems_[index];
    }
};
