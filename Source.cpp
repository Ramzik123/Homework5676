#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BubbleSort {
public:
    static void sort(std::vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    // Обмен значений
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
};

class SelectionSort {
public:
    static void sort(std::vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            // Обмен значений
            int temp = arr[minIndex];
            arr[minIndex] = arr[i];
            arr[i] = temp;
        }
    }
};

class InsertionSort {
public:
    static void sort(std::vector<int>& arr) {
        int n = arr.size();
        for (int i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;

            /* Перемещаем элементы arr[0..i-1], которые больше key,
            на одну позицию вперед от текущей позиции */
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }
};

class CountingSort {
public:
    static void sort(std::vector<int>& arr, int range) {
        std::vector<int> count(range + 1, 0); // Создаем вспомогательный массив для подсчета элементов
        std::vector<int> output(arr.size());

        // Подсчитываем количество каждого элемента во входном массиве
        for (int num : arr)
            count[num]++;

        // Преобразуем count[] так, чтобы каждый элемент i содержал сумму элементов <= i
        for (int i = 1; i <= range; ++i)
            count[i] += count[i - 1];

        // Ставим элементы из входного массива в правильные позиции в выходном массиве
        for (int i = arr.size() - 1; i >= 0; --i) {
            output[count[arr[i]] - 1] = arr[i];
            count[arr[i]]--;
        }

        // Копируем отсортированные элементы обратно в исходный массив
        for (int i = 0; i < arr.size(); ++i)
            arr[i] = output[i];
    }
};


class RadixSort {
public:
    static void sort(std::vector<int>& arr) {
        int max_element = *std::max_element(arr.begin(), arr.end());

        // Применяем цифровую сортировку для каждого разряда, начиная с младшего
        for (int exp = 1; max_element / exp > 0; exp *= 10)
            countingSort(arr, exp);
    }

private:
    static void countingSort(std::vector<int>& arr, int exp) {
        const int range = 10; // количество возможных цифр от 0 до 9
        std::vector<int> count(range, 0);
        std::vector<int> output(arr.size());

        // Подсчитываем количество встречающихся цифр
        for (int num : arr)
            count[(num / exp) % range]++;

        // Преобразуем count[] так, чтобы каждый элемент i содержал сумму элементов <= i
        for (int i = 1; i < range; ++i)
            count[i] += count[i - 1];

        // Ставим элементы из входного массива в правильные позиции в выходном массиве
        for (int i = arr.size() - 1; i >= 0; --i) {
            output[count[(arr[i] / exp) % range] - 1] = arr[i];
            count[(arr[i] / exp) % range]--;
        }

        // Копируем отсортированные элементы обратно в исходный массив
        for (int i = 0; i < arr.size(); ++i)
            arr[i] = output[i];
    }
};


std::vector<int> createArray() {
    int size;
    std::cout << "Введите количество элементов массива: ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "Введите элементы массива: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }

    return arr;
}

// Функция для вывода списка классов
void printClassList() {
    cout << "Выбери функцию для сортировки:" << endl;
    cout << "1. BubbleSort" << endl;
    cout << "2. SelectionSort" << endl;
    cout << "3. InsertionSort" << endl;
    cout << "4. CountingSort" << endl;
    cout << "5. RadixSort" << endl;
}

// Функция для ввода пользователем выбора класса
int getUserChoice() {
    int choice;
    cout << "Введите номер класса сортировки: ";
    cin >> choice;
    cin.ignore(); // очистить буфер ввода
    return choice;
}

int main() {
    setlocale(LC_ALL, "RUS");
    std::vector<int> arr = createArray();
    printClassList();
    int choice = getUserChoice();

    switch (choice) {
    case 1:
        BubbleSort::sort(arr);
        break;
    case 2:
        SelectionSort::sort(arr);
        break;
    case 3:
        InsertionSort::sort(arr);
        break;
    case 4:
    {
        // Определение диапазона для CountingSort
        int range = *std::max_element(arr.begin(), arr.end());
        CountingSort::sort(arr, range);
    }
    break;
    case 5:
        RadixSort::sort(arr);
        break;
    default:
        cout << "Ошибка: некорректный выбор." << endl;
        break;
    }

    // Вывод отсортированного массива
    std::cout << "Отсортированный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}


