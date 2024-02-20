#ifndef RUSTYPTR_ARCDYN
#define RUSTYPTR_ARCDYN

#include <memory>
#include <type_traits>
#include <utility>

/**
 * A wrapper around shared_ptr.
 */
template <typename Interface>
class ArcDyn {
  std::shared_ptr<Interface> ptr;

 public:
  template <
      typename Implementation,
      std::enable_if_t<!std::is_same_v<ArcDyn<Interface>,
                                       std::remove_cvref_t<Implementation>>,
                       bool> = true>
  ArcDyn(Implementation&& object)
      : ptr(std::make_shared<std::remove_cvref_t<Implementation>>(
            std::forward<Implementation>(object))) {
    static_assert(!std::is_same_v<std::remove_cvref_t<Interface>,
                                  std::remove_cvref_t<Implementation>>,
                  "Use Arc if Interface is the same as Implementation.");
  }

  ArcDyn(ArcDyn const& other) = default;
  auto operator=(ArcDyn const& other) -> ArcDyn& = default;

  ArcDyn(ArcDyn&& other) = default;
  auto operator=(ArcDyn&& other) -> ArcDyn& = default;

  ~ArcDyn() = default;

  auto operator*() -> Interface& { return *ptr; }
  auto operator*() const -> Interface const& { return *ptr; }

  auto operator->() -> Interface* { return ptr.get(); }
  auto operator->() const -> Interface const* { return ptr.get(); }

  auto get() -> Interface* { return ptr.get(); }
  auto get() const -> Interface const* { return ptr.get(); }
};

#endif
