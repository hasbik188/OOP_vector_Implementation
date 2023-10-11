#ifndef OOP_COMISSION_VECTOR_H
#define OOP_COMISSION_VECTOR_H

#include <memory>
#include <limits>
#include "random_access_iterator.h"

template<class T,class Allocator = std::allocator<T>>
        class Vector{
public:
            using value_type = T;
            using allocator_type = Allocator;
            using size_type = std::size_t;
            using difference_type = std::ptrdiff_t;
            using reference = value_type&;
            using const_reference = const value_type&;
            using pointer = typename std::allocator_traits<Allocator>::pointer;
            using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
            using iterator = RandomAccessIterator<T>;
            using const_iterator = RandomAccessIterator<T>;
            using reverse_iterator = typename std::reverse_iterator<iterator>;
            using const_reverse_iterator = typename std::reverse_iterator<const_iterator>;
private:
    /* Member functions */
        private:
            pointer ptr;
            size_type size_;
            size_type capacity_;
            allocator_type allocator_;

        public:
            //---------------------------Member functions---------------------------
            Vector(){
                ptr = nullptr;
                size_ = 0;
                capacity_ = 0;

            }

            explicit Vector(const Allocator& alloc)
                    : ptr(nullptr), size_(0), capacity_(0), allocator_(alloc) {}

        Vector(const Vector& other){
                    allocator_ = other.allocator_;
                    size_ = other.size_;
                    capacity_ = other.capacity_;
            ptr = allocator_.allocate(capacity_);
            for (size_type i = 0; i < size_; ++i)
                allocator_.construct(&ptr[i], other.ptr[i]);
        }
        Vector(Vector&& other){
                    allocator_ = std::move(other.allocator_);
                    size_ = other.size_;
                    capacity_ = other.capacity_;
                    ptr = other.ptr;
            other.size_ = 0;
            other.capacity_ = 0;
            other.ptr = nullptr;
        }
            ~Vector() {
                clear();
                allocator_.deallocate(ptr, capacity_);
            }

            Vector& operator=(const Vector& other) {
                if (this == &other) {
                    return *this;
                }

                clear();
                allocator_.deallocate(ptr, capacity_);

                allocator_ = other.allocator_;
                size_ = other.size_;
                capacity_ = other.capacity_;
                ptr = allocator_.allocate(capacity_);
                std::uninitialized_copy(other.ptr, other.ptr + size_, ptr);

                return *this;
            }
            void assign(size_type count, const T& value) {
                clear();
                if (count > capacity_) {
                    if (ptr)
                        allocator_.deallocate(ptr, capacity_);
                    capacity_ = count;
                    ptr = allocator_.allocate(capacity_);
                }
                for (size_type i = 0; i < count; ++i)
                    allocator_.construct(&ptr[i], value);

                size_ = count;
            }
            void assign(std::initializer_list<T> ilist) {
                assign(ilist.begin(), ilist.end());
            }
            allocator_type get_allocator() const noexcept {
                return allocator_;
            }
            //---------------------------Element access--------------------------- ✔
            reference at( size_type pos ){
                if(pos < size())
                    return (ptr[pos]);
            }
            const_reference at( size_type pos ) const{
                if(pos < size())
                    return (ptr[pos]);
            }
            reference operator[] (size_type pos){
                return (ptr[pos]);
            }
            const_reference operator[] (size_type pos) const{
                return (ptr[pos]);
            }
            reference front(){
                return ptr[0];
            }
            const_reference front() const{
                return ptr[0];
            }
            reference back(){
                return ptr[size_ - 1];
            }
            const_reference back() const{
                return ptr[size_ - 1];
            }
            T* data(){
                return ptr;
            }
            const T* data() const{
                return ptr;
            }
            //---------------------------Iterators--------------------------- ✔
            iterator begin() {
                return ptr;
            }
            iterator end() {
                return begin() + size_;
            }
            const_iterator begin() const {
                return begin();
            }
            const_iterator end() const {
                return end();
            }
            reverse_iterator rbegin() {
                return reverse_iterator(ptr + size_);
            }
            reverse_iterator rend() {
                return reverse_iterator(ptr);
            }
            const_reverse_iterator rbegin() const {
                return rbegin();
            }
            const_reverse_iterator rend() const {
                return rend();
            }
            //---------------------------Capacity---------------------------
            bool empty() const {
                return (begin() == end());
            }
            size_type size() const {
                return size_;
            }
            size_type max_size() const {
                return std::numeric_limits<size_type>::max();
            }
            void reserve(size_type new_cap) {
                if (new_cap > capacity()) {
                    pointer new_ptr = allocator_.allocate(new_cap);
                    for (size_type i = 0; i < size_; ++i) {
                        allocator_.construct(&new_ptr[i], std::move(ptr[i]));
                        allocator_.destroy(&ptr[i]);
                    }
                    allocator_.deallocate(ptr, capacity());
                    ptr = new_ptr;
                    capacity_ = new_cap;
                }
            }
            size_type capacity() const noexcept {
                return capacity_;
            }
            void shrink_to_fit() {
                if (size_ < capacity_) {
                    for (size_type i = size_; i < capacity_; ++i) {
                        allocator_.destroy(&ptr[i]);
                    }
                    capacity_ = size_;
                }
            }
            //---------------------------Modifiers---------------------------
            void clear() noexcept {
                for (size_type i = 0; i < size_; ++i) {
                    ptr[i].~value_type(); // Вызываем деструктор явно
                }
                size_ = 0;
            }

            template <class... Args>
            iterator emplace(const_iterator pos, Args&&... args) {
                size_type index = pos - begin();
                if (size_ == capacity()) {
                    size_type new_cap = (capacity() == 0) ? 1 : capacity() * 2;
                    reserve(new_cap);
                }
                std::move_backward(begin() + index, end(), end() + 1);
                allocator_.construct(ptr + index, std::forward<Args>(args)...);
                ++size_;
                return begin() + index;
            }
            iterator erase(iterator pos) {
                if (pos >= end() || pos < begin()) {
                    return end();
                }
                allocator_.destroy(pos);
                std::move(pos + 1, end(), pos);
                --size_;
                return pos;
            }

            iterator erase(iterator first, iterator last) {
                if (first >= last || first < begin() || last > end()) {
                    return end();
                }
                for (iterator it = first; it != last; ++it) {
                    allocator_.destroy(it);
                }
                std::move(last, end(), first);
                size_ -= std::distance(first, last);
                return first;
            }
            void push_back(const T& value) {
                if (size_ == capacity_) {
                    reserve(size_ + 1);
                }
                   allocator_.construct(&ptr[size_++],value);
            }
            void push_back(T&& value) {
                if (size_ == capacity_) {
                    reserve(size_ + 1);
                }
                allocator_.construct(&ptr[size_++], std::move(value));
            }

            iterator insert(const_iterator pos, const T& value) {

                auto diff = pos - begin();
                if (diff < 0 || static_cast<size_type>(diff) > size_)
                    throw std::runtime_error("Iterator out of bounds");
                size_type current{ static_cast<size_type>(diff) };
                if (size_ >= capacity_)
                    reserve(capacity_ * 2);
                for (auto i{ size_ }; i-- > current;)
                    ptr[i + 1] = ptr[i];
                ptr[current] = value;
                ++size_;
                return iterator{ ptr + current };
            }


            template <class... Args>
            void emplace_back(Args&&... args) {
                if (size_ == capacity_) {
                    reserve(size_ + 1);
                }
                allocator_.construct(&ptr[size_], std::forward<Args>(args)...);
                ++size_;
            }
            void pop_back() {
                if (size_ > 0) {
                    allocator_.destroy(&ptr[size_ - 1]);
                    --size_;
                } else
                    std::cerr << "ur container is empty\n";
            }
            void resize(size_type count) {
                if (count < size_) {
                    while (size_ > count) {
                        pop_back();
                    }
                } else if (count > size_) {
                    if (count > capacity()) {
                        reserve(count);
                    }
                    while (size_ < count) {
                        allocator_.construct(&ptr[size_], value_type());
                        ++size_;
                    }
                }
            }

            void resize(size_type count, const value_type& value) {
                if (count < size_) {
                    while (size_ > count) {
                        pop_back();
                    }
                } else if (count > size_) {
                    if (count > capacity()) {
                        reserve(count);
                    }
                    while (size_ < count) {
                        allocator_.construct(&ptr[size_], value);
                        ++size_;
                    }
                }
            }
            void swap(Vector& other) {
                std::swap(ptr, other.ptr);
                std::swap(size_, other.size_);
                std::swap(capacity_, other.capacity_);
                std::swap(allocator_, other.allocator_);
            }
        };
//---------------------------Non-member functions---------------------------
template <class T, class Allocator>
void swap(Vector<T, Allocator>& lhs, Vector<T, Allocator>& rhs) {
    lhs.swap(rhs);
}

template<class T, class Allocator>
bool operator==(const Vector<T, Allocator> &lhs, const Vector<T, Allocator> &rhs) {
    if (lhs.size() != rhs.size())
        return (false);
    for (unsigned int i = 0; i < rhs.size(); i++)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}

template<class T, class Allocator>
bool operator!=(const Vector<T, Allocator> &lhs, const Vector<T, Allocator> &rhs) {
    return (!(lhs == rhs));
}

template<class T, class Allocator>
bool operator<(const Vector<T, Allocator> &lhs, const Vector<T, Allocator> &rhs) {
    size_t n;
    n = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
    for (typename Vector<T>::size_type i = 0; i < n; i++)
        if (lhs.at(i) != rhs.at(i))
            return (lhs.at(i) < rhs.at(i) ? true : false);
    return (lhs.size() < rhs.size());
}

template<class T, class Allocator>
bool operator<=(const Vector<T, Allocator> &lhs, const Vector<T, Allocator> &rhs) {
    return (lhs < rhs || lhs == rhs);
}

template<class T, class Allocator>
bool operator>(const Vector<T, Allocator> &lhs, const Vector<T, Allocator> &rhs) {
    return (!(lhs < rhs) && !(lhs == rhs));
}

template<class T, class Allocator>
bool operator>=(const Vector<T, Allocator> &lhs, const Vector<T, Allocator> &rhs) {
    return (!(lhs < rhs));
}
#endif //OOP_COMISSION_VECTOR_H