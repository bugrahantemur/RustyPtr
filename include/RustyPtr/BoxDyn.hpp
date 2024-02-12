#ifndef RUSTYPTR_BOXDYN
#define RUSTYPTR_BOXDYN

#include <memory>
#include <type_traits>
#include <utility>

/**
 * A wrapper around unique_ptr.
 */
template <typename Interface>
class BoxDyn {
  std::unique_ptr<Interface> ptr;

 public:
  template <
      typename Implementation,
      std::enable_if_t<!std::is_same_v<BoxDyn<Interface>,
                                       std::remove_cvref_t<Implementation>>,
                       bool> = true>
  BoxDyn(Implementation&& object)
      : ptr(std::make_unique<std::remove_cvref_t<Implementation>>(
            std::forward<Implementation>(object))) {
    static_assert(!std::is_same_v<Interface, Implementation>,
                  "Use Box if Interface is the same as Implementation.");
  }

  BoxDyn(BoxDyn const& other) = delete;
  auto operator=(BoxDyn const& other) -> BoxDyn& = delete;

  BoxDyn(BoxDyn&& other) = default;
  auto operator=(BoxDyn&& other) -> BoxDyn& = default;

  ~BoxDyn() = default;

  auto operator*() -> Interface& { return *ptr; }
  auto operator*() const -> Interface const& { return *ptr; }

  auto operator->() -> Interface* { return ptr.get(); }
  auto operator->() const -> Interface const* { return ptr.get(); }

  auto get() -> Interface* { return ptr.get(); }
  auto get() const -> Interface const* { return ptr.get(); }
};

#endif
