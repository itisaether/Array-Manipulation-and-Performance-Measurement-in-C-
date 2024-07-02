#include <iostream>
#include <memory>
#include <chrono> // Для работы с временем

template<typename T>
class Array {
private:
    std::unique_ptr<T[]> data;
    size_t size;

public:
    Array(size_t size) : data(new T[size]), size(size) {}
    ~Array() = default;

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Недопустимый индекс");
        }
        return data[index];
    }

    friend std::ostream& operator<<(std::ostream& out, const Array<T>& arr) {
        out << "[";
        for (size_t i = 0; i < arr.size; ++i) {
            out << arr.data[i];
            if (i < arr.size - 1) {
                out << ", ";
            }
        }
        out << "]";
        return out;
    }

    T* getData() {
        return data.get();
    }

    size_t getSize() const {
        return size;
    }
};

template<typename T>
bool is_monotonous(const T* arr, size_t n) {
    bool increasing = true;
    bool decreasing = true;

    for (size_t i = 1; i < n; ++i) {
        if (arr[i] > arr[i - 1]) {
            decreasing = false;
        }
        else if (arr[i] < arr[i - 1]) {
            increasing = false;
        }
    }

    return increasing || decreasing;
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "Введите длину массива: ";
    size_t length;
    std::cin >> length;

    // Измерение времени выполнения
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    Array<char> array(length);

    char k = ' '; // Начальное значение

    for (size_t i = 0; i < array.getSize(); ++i) {
        array[i] = k;
        ++k; // Увеличиваем значение символа на один для следующего элемента
        if (k > '~') // Если достигнут конец таблицы ASCII, возвращаемся к началу
            k = ' ';
    }

    std::chrono::steady_clock::time_point fill_end = std::chrono::steady_clock::now();

    std::cout << "Массив: " << array << std::endl;

    std::chrono::steady_clock::time_point check_begin = std::chrono::steady_clock::now();

    std::cout << "Массив монотонен: " << std::boolalpha << is_monotonous(array.getData(), array.getSize()) << std::endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Время заполнения массива: " << std::chrono::duration_cast<std::chrono::microseconds>(fill_end - begin).count() << " микросекунд" << std::endl;
    std::cout << "Время проверки монотонности массива: " << std::chrono::duration_cast<std::chrono::microseconds>(end - check_begin).count() << " микросекунд" << std::endl;

    return 0;
}
