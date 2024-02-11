#ifndef RUSTYPTR_ARCDYN
#define RUSTYPTR_ARCDYN

#include <memory>
#include <utility>

/**
 * A wrapper around shared_ptr.
 */
template <typename Interface>
class ArcDyn {
  std::shared_ptr<Interface> ptr;

 public:
  template <typename Implementation,
            std::enable_if_t<!std::is_same_v<ArcDyn<Interface>,
                                             std::decay_t<Implementation>>,
                             bool> = true>
  ArcDyn(Implementation&& object)
      : ptr(std::make_shared<Implementation>(std::move(object))) {
    static_assert(!std::is_same_v<Interface, Implementation>,
                  "Use Arc if Interface is the same as Implementation.");
  }

  template <typename Implementation,
            std::enable_if_t<!std::is_same_v<ArcDyn<Interface>,
                                             std::decay_t<Implementation>>,
                             bool> = true>
  ArcDyn(Implementation const& object)
      : ptr(std::make_shared<Implementation>(object)) {
    static_assert(!std::is_same_v<Interface, Implementation>,
                  "Use Arc if Interface is the same as Implementation.");
  }

  ArcDyn(ArcDyn const& other) = default;
  ArcDyn& operator=(ArcDyn const& other) = default;

  ArcDyn(ArcDyn&& other) = default;
  ArcDyn& operator=(ArcDyn&& other) = default;

  ~ArcDyn() = default;

  auto operator*() -> Interface& { return *ptr; }
  auto operator*() const -> Interface const& { return *ptr; }

  auto operator->() -> Interface* { return ptr.get(); }
  auto operator->() const -> Interface const* { return ptr.get(); }

  auto get() -> Interface* { return ptr.get(); }
  auto get() const -> Interface const* { return ptr.get(); }
};

#endif
