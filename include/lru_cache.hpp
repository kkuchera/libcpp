#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <list>
#include <stdexcept>
#include <unordered_map>

template <typename K, typename V, typename L = std::list<std::pair<const K, V>>,
          typename M = std::unordered_map<K, typename L::iterator>>
class lru_cache {
 public:
  using key_type = K;
  using mapped_type = V;
  using list_type = L;
  using map_type = M;
  using value_type = std::pair<const key_type, mapped_type>;
  using allocator_type = typename L::allocator_type;
  using size_type = typename L::size_type;
  using difference_type = typename L::difference_type;
  using reference = typename L::reference;
  using const_reference = typename L::const_reference;
  using pointer = typename L::pointer;
  using const_pointer = typename L::const_pointer;
  using iterator = typename L::iterator;
  using const_iterator = typename L::const_iterator;
  using reverse_iterator = typename L::reverse_iterator;
  using const_reverse_iterator = typename L::const_reverse_iterator;

 private:
  size_type c{0};
  list_type l;
  map_type m;

  void push_front(const value_type& x) {
    l.push_front(x);
    m.insert({x.first, l.begin()});
  }

 public:
  void foo(const value_type&) {}
  lru_cache() = default;
  explicit lru_cache(size_type x) { reserve(x); }
  explicit lru_cache(std::initializer_list<value_type> x)
      : lru_cache{x, x.size()} {}
  lru_cache(std::initializer_list<value_type> x, size_type s) {
    reserve(s);
    // std::for_each(x.begin(), x.end(), std::mem_fn(insert));
    for (const auto& v : x) insert(v);
  }

  reference front() { return l.front(); }
  const_reference front() const { return l.front(); }
  reference back() { return l.back(); }
  const_reference back() const { return l.back(); }
  mapped_type& at(const key_type& key) {
    if (const auto it = m.find(key); it != m.end()) {
      return it->second->second;
    }
    throw std::out_of_range{"key does not exist."};
  }
  const mapped_type& at(const key_type& key) const {
    if (const auto it = m.find(key); it != m.end()) {
      return it->second->second;
    }
    throw std::out_of_range{"key does not exist."};
  }
  mapped_type& operator[](const key_type& key) {
    if (const auto it = find(key); it != end()) {
      return it->second;
    }
    return insert({key, mapped_type{}}).first->second;
  }

  iterator begin() noexcept { return std::begin(l); }
  iterator end() noexcept { return std::end(l); }
  const_iterator begin() const noexcept { return std::begin(l); }
  const_iterator end() const noexcept { return std::end(l); }
  const_iterator cbegin() const noexcept { return std::cbegin(l); }
  const_iterator cend() const noexcept { return std::end(l); }
  reverse_iterator rbegin() noexcept { return std::rbegin(l); }
  reverse_iterator rend() noexcept { return std::rend(l); }
  const_reverse_iterator rbegin() const noexcept { return std::rbegin(l); }
  const_reverse_iterator rend() const noexcept { return std::rend(l); }
  const_reverse_iterator crbegin() const noexcept { return std::crbegin(l); }
  const_reverse_iterator crend() const noexcept { return std::crend(l); }
  [[nodiscard]] bool empty() const noexcept { return size() == 0; }
  [[nodiscard]] bool full() const noexcept { return size() == capacity(); }
  [[nodiscard]] size_type size() const noexcept { return l.size(); }
  [[nodiscard]] constexpr size_type capacity() const noexcept { return c; }
  [[nodiscard]] constexpr size_type max_size() const noexcept {
    return std::min(m.max_size(), l.max_size());
  }

  constexpr void reserve(size_type new_cap) {
    if (c >= new_cap) return;
    if (max_size() < new_cap) {
      throw std::length_error{"max_size() < new_cap"};
    }
    c = new_cap;
  }

  constexpr void shrink_to_fit() { c = size(); }
  constexpr void clear() noexcept {
    m.clear();
    l.clear();
  }

  iterator find(const key_type& key) {
    const auto it = m.find(key);
    if (it == m.end()) return end();
    l.splice(l.begin(), l, it->second);
    return it->second;
  }

  std::pair<iterator, bool> insert(const value_type& x) {
    const auto it = find(x.first);
    if (it != end()) {
      it->second = x.second;
      return std::make_pair(it, false);
    }
    if (full()) {
      pop_back();
    }
    push_front(x);
    return std::make_pair(begin(), true);
  }

  void pop_back() {
    m.erase(back().first);
    l.pop_back();
  }

  void pop_front() {
    m.erase(front().first);
    l.pop_front();
  }
};
