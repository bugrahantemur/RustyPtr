#ifndef RUSTYPTR_BOXDYN
#define RUSTYPTR_BOXDYN

#include <memory>
#include <utility>

/**
 * A wrapper around unique_ptr.
 */
template <typename Interface>
class BoxDyn {
  std::unique_ptr<Interface> ptr;

 public:
  template <typename Implementation,
            std::enable_if_t<!std::is_same_v<BoxDyn<Interface>,
                                             std::decay_t<Implementation>>,
                             bool> = true>
  BoxDyn(Implementation&& object)
      : ptr(std::make_unique<Implementation>(std::move(object))) {
    static_assert(!std::is_same_v<Interface, Implementation>,
                  "Use Box if Interface is the same as Implementation.");
  }

  template <typename Implementation,
            std::enable_if_t<!std::is_same_v<BoxDyn<Interface>,
                                             std::decay_t<Implementation>>,
                             bool> = true>
  BoxDyn(Implementation const& object)
      : ptr(std::make_unique<Implementation>(object)) {
    static_assert(!std::is_same_v<Interface, Implementation>,
                  "Use Box if Interface is the same as Implementation.");
  }

  BoxDyn(BoxDyn const& other) = delete;
  BoxDyn& operator=(BoxDyn const& other) = delete;

  BoxDyn(BoxDyn&& other) = default;
  BoxDyn& operator=(BoxDyn&& other) = default;

  ~BoxDyn() = default;

  auto operator*() -> Interface& { return *ptr; }
  auto operator*() const -> Interface const& { return *ptr; }

  auto operator->() -> Interface* { return ptr.get(); }
  auto operator->() const -> Interface const* { return ptr.get(); }

  auto get() -> Interface* { return ptr.get(); }
  auto get() const -> Interface const* { return ptr.get(); }
};

#endif
