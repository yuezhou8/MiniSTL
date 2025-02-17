#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* elements;  // Pointer to dynamically allocated array
    size_t capacity; // Total capacity
    size_t size;     // Number of elements currently stored

    void expand(size_t newCapacity) {
        T* newLocation = new T[newCapacity];
        std::copy(elements, elements + size, newLocation);
        delete[] elements;
        elements = newLocation;
        capacity = newCapacity;
    }

public:
    // Constructor
    Vector() : elements(nullptr), capacity(0), size(0) {}

    // Destructor
    ~Vector() {
        delete[] elements;
    }

    // Copy Constructor
    Vector(const Vector& other) : elements(nullptr), capacity(0), size(0) {
        if (this != &other) {
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            std::copy(other.elements, other.elements + size, elements);
        }
    }

    // Assignment Operator
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] elements;
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            std::copy(other.elements, other.elements + size, elements);
        }
        return *this;
    }

    // Push back
    void push_back(const T& value) {
        if (size == capacity) {
            if (capacity == 0) capacity = 1;
            else capacity *= 2;
            expand(capacity);
        }
        elements[size++] = value;
    }

    // Insert
    void insert(size_t index, const T& value) {
        if (index > size) throw std::out_of_range("Index out of range");
        if (size == capacity) {
            if (capacity == 0) capacity = 1;
            else capacity *= 2;
            expand(capacity);
        }
        for (size_t i = size; i > index; --i) {
            elements[i] = elements[i - 1];
        }
        elements[index] = value;
        ++size;
    }

    // Pop back
    void pop_back() {
        if (size > 0) {
            --size;
        }
    }

    // Clear
    void clear() {
        size = 0;
    }

    // Accessors
    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }

    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return elements[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return elements[index];
    }

    // Iterators
    T* begin() {
        return elements;
    }

    T* end() {
        return elements + size;
    }

    const T* begin() const {
        return elements;
    }

    const T* end() const {
        return elements + size;
    }

    // Print elements
    void printElements() const {
        for (size_t i = 0; i < size; i++) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Vector<int> myVector;

    int N;
    std::cin >> N;
    std::cin.ignore(); // Consume the newline character

    std::string line;
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "push") {
            int value;
            iss >> value;
            myVector.push_back(value);
        } else if (command == "print") {
            if (myVector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            myVector.printElements();
        } else if (command == "size") {
            std::cout << myVector.getSize() << std::endl;
        } else if (command == "get") {
            int index;
            iss >> index;
            std::cout << myVector[index] << std::endl;
        } else if (command == "insert") {
            int index, value;
            iss >> index >> value;
            myVector.insert(index, value);
        } else if (command == "pop") {
            myVector.pop_back();
        } else if (command == "iterator") {
            if (myVector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (auto it = myVector.begin(); it != myVector.end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        } else if (command == "foreach") {
            if (myVector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (const auto& element : myVector) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        } else if (command == "clear") {
            myVector.clear();
        }
    }
    return 0;
}
