#ifndef RUSTYPTR_BOX
#define RUSTYPTR_BOX

#include <memory>
#include <utility>

/**
 * A wrapper around unique_ptr.
 */
template <typename T>
class Box {
  std::unique_ptr<T> ptr;

 public:
  Box() : ptr{std::make_unique<T>()} {}

  Box(T&& object) : ptr{std::make_unique<T>(std::move(object))} {}

  Box(T const& object) : ptr{std::make_unique<T>(object)} {}

  Box(Box const& other) : Box{*other.ptr} {}
  Box& operator=(Box const& other) {
    *ptr = *other.ptr;
    return *this;
  }

  Box(Box&& other) = default;
  auto operator=(Box&& other) -> Box& = default;
  ~Box() = default;

  auto operator*() -> T& { return *ptr; }
  auto operator*() const -> T const& { return *ptr; }

  auto operator->() -> T* { return ptr.get(); }
  auto operator->() const -> T const* { return ptr.get(); }

  auto get() -> T* { return ptr.get(); }
  auto get() const -> T const* { return ptr.get(); }
};

#endif
