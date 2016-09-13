#include <algorithm>
#include <cassert>
#include <map>
#include <cstring>
#include <string>
#include <iostream>
#include <memory>
#include <ostream>

class Trump {
    friend std::ostream& operator<<(std::ostream& os, const Trump& trump);

public:
    enum class Mark {
        None = 0,
        Heart,
        Diamond,
        Spade,
        Clover,
        Size
    };
    
    static Mark to_mark(const char c);
    static const char to_char(const Trump::Mark& mark);

public:
    Trump();
    Trump(const Mark& mark, const int num);
    Trump(const std::string& str);
    Trump(const Trump& rhs);

    Trump& operator =(Trump&& rhs);

    void swap(Trump& rhs) noexcept;

    bool operator< (const Trump& rhs) const;
    bool operator> (const Trump& rhs) const;
    bool operator==(const Trump& rhs) const;
    bool operator!=(const Trump& rhs) const;

private:
    Mark _mark;
    int _num;
};

inline Trump::Mark Trump::to_mark(const char c)
{
    static const std::map<char, Mark> dict
        = {
            { 'H', Mark::Heart },
            { 'D', Mark::Diamond },
            { 'S', Mark::Spade },
            { 'C', Mark::Clover }
    };
    const auto it = dict.find(c);

    return it != dict.cend()
        ? it->second
        : Mark::None;
}

inline const char Trump::to_char(const Trump::Mark& mark)
{
    const char dict [] = { 'N' , 'H', 'D', 'S', 'C' , 'N' };
    return dict[static_cast<int>(mark)];
}


Trump::Trump()
    : _mark(Mark::None),
    _num('0')
{
}

inline Trump::Trump(const Mark & mark, const int num)
    : _mark(mark),
    _num(num)
{
    assert(_num >= 1);
    assert(_num <= 13);
}

Trump::Trump(const std::string & str)
    : _mark(Trump::to_mark(str[0])),
    _num(std::atoi(str.substr(1, str.size() - 1).c_str()))
{
    assert(_num >= 1);
    assert(_num <= 13);
}

Trump::Trump(const Trump& rhs)
    : _mark(rhs._mark),
    _num(rhs._num)
{
    assert(_num >= 1);
    assert(_num <= 13);
}

Trump & Trump::operator=(Trump&& rhs)
{
    this->swap(rhs);
    return *this;
}

void Trump::swap(Trump& rhs) noexcept
{
    std::swap(_mark, rhs._mark);
    std::swap(_num, rhs._num);
    return;
}

bool Trump::operator<(const Trump & rhs) const
{
    return _num < rhs._num;
}

bool Trump::operator>(const Trump & rhs) const
{
    return rhs._num < _num;
}

bool Trump::operator==(const Trump & rhs) const
{
    return _mark == rhs._mark
        && !(*this < rhs || rhs < *this);
}

bool Trump::operator!=(const Trump & rhs) const
{
    return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& os, const Trump& trump)
{
    os << Trump::to_char(trump._mark) << trump._num;
    return os;
}

void get_array(
    Trump* arr,
    const std::string& str,
    int i,  //arr index
    int s,  //start pos
    int e)  //end pos
{
    if (e == str.size()) {
        arr[i] = Trump(str.substr(s, e - s));
        return;
    }

    constexpr char delim = ' ';
    if (str[e] == delim) {
        arr[i] = Trump(str.substr(s, e - s));
        get_array(arr, str, i + 1, e + 1, e + 1);
        return;
    }

    get_array(arr, str, i, s, e + 1);
    return;
}

void get_array(Trump* arr, std::istream& stream)
{
    std::string buf;
    getline(stream, buf);
    get_array(arr, buf, 0, 0, 0);

    return;
}

void print(Trump* arr, int n, int i)
{
    if (n - 1 == i) {
        std::cout << arr[i];
        return;
    }

    std::cout << arr[i] << " ";
    print(arr, n, i + 1);
    return;
}

void print(Trump* arr, int n)
{
    print(arr, n, 0);
    return;
}

void rise(Trump* arr, int i, int j) {
    if (j == i) {
        return;
    }

    if (arr[j - 1] > arr[j]) {
        arr[j - 1].swap(arr[j]);
    }

    rise(arr, i, j - 1);
    return;
}

void bubble_sort(Trump* arr, int n, int i) {
    if (i == n) {
        return;
    }

    rise(arr, i, n - 1);
    bubble_sort(arr, n, i + 1);
    return;
}

void bubble_sort(Trump* arr, int n) {
    bubble_sort(arr, n, 0);
    return;
}

void selection_sort(Trump* arr, int n, int i) {
    if (i == n) {
        return;
    }

    int m = i;
    for (int k = i + 1; k < n; ++k) {
        if (arr[k] < arr[m]) {
            m = k;
        }
    }

    if (i != m) {
        arr[i].swap(arr[m]);
    }

    selection_sort(arr, n, i + 1);
    return;
}

void selection_sort(Trump* arr, int n) {
    selection_sort(arr, n, 0);
    return;
}

bool is_equal(
    Trump const* const arr0,
    Trump const* const arr1,
    int n,
    int i)
{
    if (i == n - 1) {
        return arr0[i] == arr1[i];
    }

    if (arr0[i] != arr1[i]) {
        return false;
    }

    return is_equal(arr0, arr1, n, i + 1);
}

bool is_equal(
    Trump const* const arr0, 
    Trump const* const arr1,
    int n) 
{
    return is_equal(arr0, arr1, n, 0);
}

int main()
{
    int n;
    std::cin >> n;
    std::cin.ignore();  //ignore \n

    const auto arr0
        = std::make_unique<Trump[]>(n);
    get_array(arr0.get(), std::cin);
    const auto arr1
        = std::make_unique<Trump[]>(n);
    std::memcpy(arr1.get(), arr0.get(), sizeof(Trump) * n);

    bubble_sort(arr0.get(), n);
    selection_sort(arr1.get(), n);

    const std::string stable = "Stable";
    const std::string unstable = "Not stable";

    print(arr0.get(), n);
    std::cout << std::endl;
    std::cout << stable << std::endl;

    print(arr1.get(), n);
    std::cout << std::endl;
    const std::string str
        = is_equal(arr0.get(), arr1.get(), n) ? stable : unstable;
    std::cout << str << std::endl;

    return 0;
}


