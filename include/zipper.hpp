#ifndef ZIPPER_HPP
#define ZIPPER_HPP

#include <cstddef>
#include <tuple>
#include <utility>

template <typename... Cs>
class zipper {
 public:
  using container_type = std::tuple<Cs...>;
  using value_type = std::tuple<typename Cs::value_type...>;
  using size_type = std::tuple_element_t<0, container_type>::size_type;
  using reference = std::tuple<typename Cs::value_type&...>;
  using const_reference = std::tuple<const typename Cs::value_type&...>;

 private:
  container_type t;

  template <size_t I, typename... Us>
  friend auto get(zipper<Us...>&);

 public:
  void push_back(const typename Cs::value_type&... xs) {
    const auto f = [&xs...](auto&... as) { (as.push_back(xs), ...); };
    std::apply(f, t);
  }

  void push_front(const typename Cs::value_type&... xs) {
    const auto f = [&xs...](auto&... as) { (as.push_front(xs), ...); };
    std::apply(f, t);
  }

  void pop_back() {
    const auto f = [](auto&... as) { (as.pop_back(), ...); };
    std::apply(f, t);
  }

  void pop_front() {
    const auto f = [](auto&... as) { (as.pop_front(), ...); };
    std::apply(f, t);
  }

  void clear() {
    const auto f = [](auto&... as) { (as.clear(), ...); };
    std::apply(f, t);
  }

  [[nodiscard]] bool empty() const { return std::get<0>(t).empty(); }
  size_type size() const { return std::get<0>(t).size(); }
};

template <size_t I, typename... Us>
auto get(zipper<Us...>& z) {
  return std::make_pair(std::get<I>(z.t).begin(), std::get<I>(z.t).end());
}

#include <deque>
#include <list>
#include <vector>

template <typename... Ts>
using zip_vector = zipper<std::vector<Ts>...>;
template <typename... Ts>
using zip_deque = zipper<std::deque<Ts>...>;
template <typename... Ts>
using zip_list = zipper<std::list<Ts>...>;

#endif
