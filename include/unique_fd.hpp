#ifndef UNIQUE_FD_HPP
#define UNIQUE_FD_HPP

#include <unistd.h>

#include <utility>

class unique_fd {
 private:
  int fd = -1;

 public:
  constexpr explicit unique_fd(int x) noexcept : fd{x} {};
  constexpr explicit operator bool() const noexcept { return get() != -1; }
  constexpr unique_fd() noexcept = default;
  unique_fd(const unique_fd&) = delete;
  unique_fd& operator=(const unique_fd&) = delete;
  constexpr unique_fd(unique_fd&& x) noexcept : fd{x.release()} {}
  constexpr unique_fd& operator=(unique_fd&& x) noexcept {
    reset(x.release());
    return *this;
  }
  constexpr ~unique_fd() { reset(); }
  constexpr int release() noexcept { return std::exchange(fd, -1); }
  constexpr void reset(int x = -1) noexcept {
    if (get() != -1) {
      ::close(get());
    }
    fd = x;
  }
  constexpr void swap(unique_fd& x) noexcept { std::swap(fd, x.fd); }
  constexpr int get() const noexcept { return fd; }
};

#endif
