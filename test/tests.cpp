#include <gtest/gtest.h>

#include <string>

#include "../include/RustyPtr/Arc.hpp"
#include "../include/RustyPtr/ArcDyn.hpp"
#include "../include/RustyPtr/Box.hpp"
#include "../include/RustyPtr/BoxDyn.hpp"

/************************************************
 * Helper type for Box and Arc tests
 ************************************************/
struct Number {
  double a;

  Number() : a(1.0) {}
  Number(double a) : a(a) {}

  ~Number() = default;

  virtual auto name() -> std::string { return "Number"; }
};

/************************************************
 * Test Box
 ************************************************/
TEST(TestBox, CanBeDefaultConstructed) {
  Box<Number> const box;

  ASSERT_EQ(box->a, 1.0);
}

TEST(TestBox, CanBeConstructedByMovingValue) {
  Box<Number> const box{Number{2.0}};

  ASSERT_EQ(box->a, 2.0);
}

TEST(TestBox, CanBeConstructedByCopyingValue) {
  Number number{2.0};

  Box<Number> box{number};

  ASSERT_EQ(box->a, 2.0);

  number.a = 3.0;

  ASSERT_EQ(box->a, 2.0);
}

TEST(TestBox, CanBeMoveConstructed) {
  Box<Number> to_move{Number{2.0}};

  Box<Number> const box{std::move(to_move)};

  ASSERT_EQ(box->a, 2.0);
}

TEST(TestBox, CanBeCopyConstructed) {
  Box<Number> to_copy{Number{2.0}};

  Box<Number> const box{to_copy};

  ASSERT_EQ(box->a, 2.0);

  to_copy->a = 3.0;

  ASSERT_EQ(box->a, 2.0);
}

/************************************************
 * Test Arc
 ************************************************/
TEST(TestArc, CanBeDefaultConstructed) {
  Arc<Number> const arc;

  ASSERT_EQ(arc->a, 1.0);
}

TEST(TestArc, CanBeConstructedByMovingValue) {
  Arc<Number> const arc{Number{2.0}};

  ASSERT_EQ(arc->a, 2.0);
}

TEST(TestArc, CanBeConstructedByCopyingValue) {
  Number number{2.0};

  Arc<Number> arc{number};

  ASSERT_EQ(arc->a, 2.0);

  number.a = 3.0;

  ASSERT_EQ(arc->a, 2.0);
}

TEST(TestArc, CanBeMoveConstructed) {
  Arc<Number> to_move{Number{2.0}};

  Arc<Number> const arc{std::move(to_move)};

  ASSERT_EQ(arc->a, 2.0);
}

TEST(TestArc, CanBeMoveAssigned) {
  Arc<Number> to_move{Number{2.0}};

  Arc<Number> arc{Number{3.0}};

  arc = std::move(to_move);

  ASSERT_EQ(arc->a, 2.0);
}

TEST(TestArc, CanBeCopyConstructed) {
  Arc<Number> to_copy{Number{2.0}};

  Arc<Number> arc{to_copy};

  to_copy->a = 3.0;

  ASSERT_EQ(arc->a, 3.0);
}

TEST(TestArc, CanBeCopyAssigned) {
  Arc<Number> to_copy{Number{2.0}};

  Arc<Number> arc{Number{3.0}};

  arc = to_copy;

  ASSERT_EQ(arc->a, 2.0);
}

/************************************************
 * Helper types for BoxDyn and ArcDyn tests
 ************************************************/
struct Foo {
  virtual ~Foo() = default;

  virtual auto name() const -> std::string { return "Foo"; }
};

struct Bar : public Foo {
  auto name() const -> std::string final { return "Bar"; }
};

struct Baz : public Foo {
  auto name() const -> std::string final { return "Baz"; }
};

/************************************************
 * Test BoxDyn
 ************************************************/
TEST(TestBoxDyn, CanBeConstructedByMovingValue) {
  BoxDyn<Foo> boxdyn{Bar{}};

  ASSERT_EQ(boxdyn->name(), "Bar");
}

TEST(TestBoxDyn, CanBeConstructedByCopyingValue) {
  Bar const bar{};

  BoxDyn<Foo> const boxdyn{bar};

  ASSERT_EQ(boxdyn->name(), "Bar");
}

TEST(TestBoxDyn, CanBeMoveConstructed) {
  BoxDyn<Foo> to_move{Bar{}};

  BoxDyn<Foo> const boxdyn{std::move(to_move)};

  ASSERT_EQ(boxdyn->name(), "Bar");
}

TEST(TestBoxDyn, CanBeMoveAssigned) {
  BoxDyn<Foo> to_move{Bar{}};

  BoxDyn<Foo> boxdyn{Baz{}};

  boxdyn = std::move(to_move);

  ASSERT_EQ(boxdyn->name(), "Bar");
}

/************************************************
 * Test ArcDyn
 ************************************************/
TEST(TestArcDyn, CanBeConstructedByMovingValue) {
  ArcDyn<Foo> boxdyn{Bar{}};

  ASSERT_EQ(boxdyn->name(), "Bar");
}

TEST(TestArcDyn, CanBeConstructedByCopyingValue) {
  Bar const bar{};

  ArcDyn<Foo> const arcdyn{bar};

  ASSERT_EQ(arcdyn->name(), "Bar");
}

TEST(TestArcDyn, CanBeMoveConstructed) {
  ArcDyn<Foo> to_move{Bar{}};

  ArcDyn<Foo> const arcdyn{std::move(to_move)};

  ASSERT_EQ(arcdyn->name(), "Bar");
}

TEST(TestArcDyn, CanBeMoveAssigned) {
  ArcDyn<Foo> to_move{Bar{}};

  ArcDyn<Foo> arcdyn{Baz{}};

  arcdyn = std::move(to_move);

  ASSERT_EQ(arcdyn->name(), "Bar");
}

TEST(TestArcDyn, CanBeCopyConstructed) {
  ArcDyn<Foo> to_copy{Bar{}};

  ArcDyn<Foo> arcdyn{to_copy};

  ASSERT_EQ(arcdyn->name(), "Bar");
}

TEST(TestArcDyn, CanBeCopyAssigned) {
  ArcDyn<Foo> to_copy{Bar{}};

  ArcDyn<Foo> arcdyn{Baz{}};

  arcdyn = to_copy;

  ASSERT_EQ(arcdyn->name(), "Bar");
}
