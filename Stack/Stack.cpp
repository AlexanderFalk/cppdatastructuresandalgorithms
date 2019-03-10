#include <iostream>
template <typename T>
struct Stack {
    private:
        int* array;
        // Keeping track of the array
        int index;
    public:
        Stack(int x) : array(new T[x]) {};
        ~Stack() {
            delete[] array;
        };
        void push(T data);
        T pop();
        void printArray(int size);
};

template <typename T>
void Stack<T>::push(T data) {
    array[index] = data;
    std::cout << "Added: " << array[index] << "\n";
    index++;
};

template <typename T>
T Stack<T>::pop() {
    array[index-1] = 0;
    std::cout << "Removed: " << array[index] << "\n";
    index--;
};

template <typename T>
void Stack<T>::printArray(int size) {
    for(int i = 0; i < size; i++) {
        std::cout << "Element: " << array[i] << "\n";
    }
};

int main() {
    int size = 5;
    Stack<int> stack(size);
    stack.push(2);
    stack.push(4);
    stack.push(3);
    stack.push(9);
    stack.printArray(size);
    stack.pop();
    stack.printArray(size);
    stack.push(9);
    stack.printArray(size);
}