#ifndef KWAY_MERGE_HPP
#define KWAY_MERGE_HPP

#include <algorithm>
#include <functional>

template <typename I, typename O, typename Compare>
// requires I is a RandomAccessIterator
// requires O is a OutputIterator
// requires Compare is a StrictWeakOrdering on ValueType(I)
// requires get<0>(ValueType(I)) is first InputIterator
// requires get<1>(ValueType(I)) is last InputIterator
auto kway_merge(I first, I last, O out, Compare cmp) {
  std::make_heap(first, last, std::not_fn(cmp));
  while (first != last) {
    std::pop_heap(first, last, std::not_fn(cmp));
    const auto min = last - 1;
    *out++ = *std::get<0>(*min)++;
    if (std::get<0>(*min) != std::get<1>(*min)) {
      std::push_heap(first, last, std::not_fn(cmp));
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
  auto less = [](const auto &x, const auto &y) {
    return *std::get<0>(x) < *std::get<0>(y);
  };
  return kway_merge(first, last, out, less);
}

#endif
