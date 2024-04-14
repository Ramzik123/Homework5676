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
                    // ����� ��������
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
            // ����� ��������
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

            /* ���������� �������� arr[0..i-1], ������� ������ key,
            �� ���� ������� ������ �� ������� ������� */
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
        std::vector<int> count(range + 1, 0); // ������� ��������������� ������ ��� �������� ���������
        std::vector<int> output(arr.size());

        // ������������ ���������� ������� �������� �� ������� �������
        for (int num : arr)
            count[num]++;

        // ����������� count[] ���, ����� ������ ������� i �������� ����� ��������� <= i
        for (int i = 1; i <= range; ++i)
            count[i] += count[i - 1];

        // ������ �������� �� �������� ������� � ���������� ������� � �������� �������
        for (int i = arr.size() - 1; i >= 0; --i) {
            output[count[arr[i]] - 1] = arr[i];
            count[arr[i]]--;
        }

        // �������� ��������������� �������� ������� � �������� ������
        for (int i = 0; i < arr.size(); ++i)
            arr[i] = output[i];
    }
};


class RadixSort {
public:
    static void sort(std::vector<int>& arr) {
        int max_element = *std::max_element(arr.begin(), arr.end());

        // ��������� �������� ���������� ��� ������� �������, ������� � ��������
        for (int exp = 1; max_element / exp > 0; exp *= 10)
            countingSort(arr, exp);
    }

private:
    static void countingSort(std::vector<int>& arr, int exp) {
        const int range = 10; // ���������� ��������� ���� �� 0 �� 9
        std::vector<int> count(range, 0);
        std::vector<int> output(arr.size());

        // ������������ ���������� ������������� ����
        for (int num : arr)
            count[(num / exp) % range]++;

        // ����������� count[] ���, ����� ������ ������� i �������� ����� ��������� <= i
        for (int i = 1; i < range; ++i)
            count[i] += count[i - 1];

        // ������ �������� �� �������� ������� � ���������� ������� � �������� �������
        for (int i = arr.size() - 1; i >= 0; --i) {
            output[count[(arr[i] / exp) % range] - 1] = arr[i];
            count[(arr[i] / exp) % range]--;
        }

        // �������� ��������������� �������� ������� � �������� ������
        for (int i = 0; i < arr.size(); ++i)
            arr[i] = output[i];
    }
};


std::vector<int> createArray() {
    int size;
    std::cout << "������� ���������� ��������� �������: ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "������� �������� �������: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }

    return arr;
}

// ������� ��� ������ ������ �������
void printClassList() {
    cout << "������ ������� ��� ����������:" << endl;
    cout << "1. BubbleSort" << endl;
    cout << "2. SelectionSort" << endl;
    cout << "3. InsertionSort" << endl;
    cout << "4. CountingSort" << endl;
    cout << "5. RadixSort" << endl;
}

// ������� ��� ����� ������������� ������ ������
int getUserChoice() {
    int choice;
    cout << "������� ����� ������ ����������: ";
    cin >> choice;
    cin.ignore(); // �������� ����� �����
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
        // ����������� ��������� ��� CountingSort
        int range = *std::max_element(arr.begin(), arr.end());
        CountingSort::sort(arr, range);
    }
    break;
    case 5:
        RadixSort::sort(arr);
        break;
    default:
        cout << "������: ������������ �����." << endl;
        break;
    }

    // ����� ���������������� �������
    std::cout << "��������������� ������: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}


