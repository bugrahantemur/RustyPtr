#ifndef RUSTYPTR_ARC
#define RUSTYPTR_ARC

#include <memory>
#include <utility>

/**
 * A wrapper around shared_ptr.
 */
template <typename T>
class Arc {
  std::shared_ptr<T> ptr;

 public:
  Arc() : ptr(std::make_shared<T>()) {}

  Arc(T&& object) : ptr(std::make_shared<T>(std::move(object))) {}

  Arc(T const& object) : ptr(std::make_shared<T>(object)) {}

  Arc(Arc const& other) = default;
  auto operator=(Arc const& other) -> Arc& = default;
  Arc(Arc&& other) = default;
  auto operator=(Arc&& other) -> Arc& = default;
  ~Arc() = default;

  T& operator*() { return *ptr; }
  T const& operator*() const { return *ptr; }

  T* operator->() { return ptr.get(); }
  T const* operator->() const { return ptr.get(); }

  auto get() -> T* { return ptr.get(); }
  auto get() const -> T const* { return ptr.get(); }
};

#endif
