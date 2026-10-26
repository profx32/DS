#include <iostream>
using namespace std;
template <typename T>
class Vector {
    T* data_;
    size_t size_;
    size_t capacity_;

    void grow() {
        size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = move(data_[i]);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    // Copy constructor
    Vector(const Vector& other)
        : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
    }

    // Copy assignment
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector tmp(other);
            swap(data_, tmp.data_);
            swap(size_, tmp.size_);
            swap(capacity_, tmp.capacity_);
        }
        return *this;
    }

    ~Vector() { delete[] data_; }

    void push_back(const T& value) {
        if (size_ == capacity_) grow();
        data_[size_++] = value;
    }

    void pop_back() {
        if (size_ == 0) throw out_of_range("Vector is empty");
        --size_;
    }

    T& operator[](size_t i) { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

    T& at(size_t i) {
        if (i >= size_) throw out_of_range("Index out of range");
        return data_[i];
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    void clear() { size_ = 0; }
};

int main() {
    Vector<int> v;
    for (int i = 1; i <= 5; ++i) v.push_back(i * 10);

    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    cout << "\nsize=" << v.size() << " capacity=" << v.capacity() << "\n";
}