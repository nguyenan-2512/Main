#pragma once

template<typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    Pair() : first(T1()), second(T2()) {}

    Pair(const T1& f, const T2& s) : first(f), second(s) {}

    Pair(const Pair& other) : first(other.first), second(other.second) {}

    Pair& operator=(const Pair& other) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }
    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }
    bool operator!=(const Pair& other) const {
        return !(*this == other);
    }

    bool operator<(const Pair& other) const {
        if (first != other.first) {
            return first < other.first;
        }
        return second < other.second;
    }
    bool operator>(const Pair& other) const {
        return other < *this;
    }
    bool operator<=(const Pair& other) const {
        return !(other < *this);
    }

    bool operator>=(const Pair& other) const {
        return !(*this < other);
    }
};

template<typename T1, typename T2>
Pair<T1, T2> make_pair(const T1& first, const T2& second) {
    return Pair<T1, T2>(first, second);
}