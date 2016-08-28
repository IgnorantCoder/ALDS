#include <iostream>
#include <vector>
#include <string>

constexpr int max_size()
{
    return static_cast<int>(1e+2);
}

void print(int* a, int n, int i) {
    if (i == n - 1) {
        std::cout << a[i] << std::endl;
        return;
    }

    std::cout << a[i] << " ";
    return print(a, n, i + 1);
}

void print(int* a, int n) {
    print(a, n, 0);
    return;
}

std::vector<int>
split(const std::string &s, const char delim) {
    std::vector<int> ret;
    std::string item;
    for (const char ch : s) {
        if (ch == delim) {
            if (!item.empty()) {
                ret.push_back(std::atoi(item.c_str()));
            }
            item.clear();
        }
        else {
            item += ch;
        }
    }
    if (!item.empty()) {
        ret.push_back(std::atoi(item.c_str()));
    }
    return ret;
}

int rise(int* a, int i, int j) {
    if (j == i) {
        return 0;
    }

    const bool is_swap = (a[j - 1] > a[j]);
    if (is_swap) {
        std::swap(a[j - 1], a[j]);
    }

    return (is_swap ? 1 : 0) + rise(a, i, j - 1);
}

int bubble_sort(int* a, int n, int i) {
    if (i == n) {
        return 0;
    }
    
    return rise(a, i, n - 1) + bubble_sort(a, n, i + 1);
}

int bubble_sort(int* a, int n) {
    return bubble_sort(a, n, 0);
}

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore();  //ignore \n

    constexpr int N = max_size();
    std::string buf;
    getline(std::cin, buf);

    std::vector<int> a = split(buf, ' ');
    int counter = bubble_sort(&a[0], n);
    print(&a[0], a.size());
    std::cout << counter << std::endl;

    return 0;
}