#include "catch2/catch.hpp"
#include "transformations.hpp"

TEST_CASE("Rotations_And_Reflections_I", "[Dih4]") {
  REQUIRE(Dih4::ROTATE_180.is_rotation());
  REQUIRE(Dih4::REFLECT_VERTICAL.is_reflection());

  REQUIRE(Dih4::ROTATE_90_CLOCKWISE.inv() == Dih4::ROTATE_90_ANTICLOCKWISE);

  REQUIRE(Dih4::ROTATE_90_CLOCKWISE.then(Dih4::REFLECT_VERTICAL) ==
          Dih4::REFLECT_REVERSE_DIAGONAL);

  Dih4 r = Dih4::ROTATE_90_ANTICLOCKWISE;
  Dih4 f = Dih4::REFLECT_HORIZONTAL;
  REQUIRE(r.then(r).then(r) == r.inv());
  REQUIRE(r.inv().then(f) == f.then(r));

  REQUIRE(Dih4::ROTATE_90_CLOCKWISE == Dih4::ROTATE_90_CLOCKWISE);
  REQUIRE(Dih4::ROTATE_90_CLOCKWISE != Dih4::ROTATE_90_ANTICLOCKWISE);
}

using namespace std;
ostream &operator<<(ostream &os, Dih4 r);

/* --------------------------------------------------------------------------------------
 */
// Output of Dih4 objects (used by the test framework when asserts fail).

ostream &operator<<(ostream &os, Dih4 r) {
  return os
         << (r == Dih4::IDENTITY
                 ? "(identity transformation)"
                 : r == Dih4::ROTATE_90_ANTICLOCKWISE
                       ? "(rotation 90 degrees anticlockwise)"
                       : r == Dih4::ROTATE_180
                             ? "(rotation 180 degrees)"
                             : r == Dih4::ROTATE_90_CLOCKWISE
                                   ? "(rotation 90 degrees clockwise)"
                                   : r == Dih4::REFLECT_VERTICAL
                                         ? "(reflection in vertical line)"
                                         : r == Dih4::REFLECT_FORWARD_DIAGONAL
                                               ? "(reflection in "
                                                 "forward-diagonal line)"
                                               : r == Dih4::REFLECT_HORIZONTAL
                                                     ? "(reflection in "
                                                       "horizontal line)"
                                                     : r == Dih4::REFLECT_REVERSE_DIAGONAL
                                                           ? "(reflection in "
                                                             "reverse-diagonal "
                                                             "line)"
                                                           : "(unknown Dih4 "
                                                             "value)");
}
