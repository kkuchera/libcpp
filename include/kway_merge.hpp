#ifndef KWAY_MERGE_HPP
#define KWAY_MERGE_HPP

#include <algorithm>

template <typename I, typename O, typename Compare>
// requires I is a RandomAccessIterator
// requires O is a OutputIterator
// requires Compare is a StrictWeakOrdering on ValueType(I)
// requires get<0>(ValueType(I)) is first InputIterator
// requires get<1>(ValueType(I)) is last InputIterator
auto kway_merge(I first, I last, O out, Compare cmp) {
  const auto tcmp = [&](const auto& x, const auto& y) { return cmp(y, x); };
  std::make_heap(first, last, tcmp);
  while (first != last) {
    std::pop_heap(first, last, tcmp);
    const auto min = last - 1;
    using std::get;
    *out++ = *get<0>(*min)++;
    if (get<0>(*min) != get<1>(*min)) {
      std::push_heap(first, last, tcmp);
    } else {
      --last;
    }
  }
  return out;
}

template <typename I, typename O>
// requires I is a RandomAccessIterator
// requires O is a OutputIterator
// requires get<0>(ValueType(I)) is first InputIterator
// requires get<1>(ValueType(I)) is last InputIterator
auto kway_merge(I first, I last, O out) {
  const auto less = [](const auto& x, const auto& y) {
    using std::get;
    return *get<0>(x) < *get<0>(y);
  };
  return kway_merge(first, last, out, less);
}

#endif
