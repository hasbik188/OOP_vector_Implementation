#ifndef OOP_COMISSION_RANDOM_ACCESS_ITERATOR_H
#define OOP_COMISSION_RANDOM_ACCESS_ITERATOR_H

#include <iterator> // std::random_access_iterator_tag
#include <cstddef> // For std::ptrdiff_t

template<class T>
class RandomAccessIterator
{
public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        RandomAccessIterator() : m_ptr(nullptr) {}
        RandomAccessIterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        reference operator[](std::size_t index) const { return m_ptr[index]; }
        difference_type operator-(const RandomAccessIterator& other) const { return m_ptr - other.m_ptr; }

        RandomAccessIterator& operator++() { m_ptr++; return *this; }
        RandomAccessIterator operator++(int) { RandomAccessIterator tmp = *this; ++(*this); return tmp; }
        RandomAccessIterator& operator--() { m_ptr--; return *this; }
        RandomAccessIterator operator--(int) { RandomAccessIterator tmp = *this; --(*this); return tmp; }
        RandomAccessIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
        RandomAccessIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
        RandomAccessIterator operator+(difference_type n) const { return RandomAccessIterator(m_ptr + n); }
        RandomAccessIterator operator-(difference_type n) const { return RandomAccessIterator(m_ptr - n); }

        friend bool operator== (const RandomAccessIterator& a, const RandomAccessIterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const RandomAccessIterator& a, const RandomAccessIterator& b) { return a.m_ptr != b.m_ptr; };
        friend bool operator<  (const RandomAccessIterator& a, const RandomAccessIterator& b) { return a.m_ptr < b.m_ptr; };
        friend bool operator<= (const RandomAccessIterator& a, const RandomAccessIterator& b) { return a.m_ptr <= b.m_ptr; };
        friend bool operator>  (const RandomAccessIterator& a, const RandomAccessIterator& b) { return a.m_ptr > b.m_ptr; };
        friend bool operator>= (const RandomAccessIterator& a, const RandomAccessIterator& b) { return a.m_ptr >= b.m_ptr; };

    private:
        pointer m_ptr;
};
#endif //OOP_COMISSION_RANDOM_ACCESS_ITERATOR_H
