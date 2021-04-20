#include "catch2/catch.hpp"
#include "lift.hpp"

/*
Lift Rules
- The Lift only goes up or down!
- Each floor has both UP and DOWN Lift-call buttons (except top and ground
floors which have only DOWN and UP respectively)
- The Lift never changes direction until there are no more people wanting to get
on/off in the direction it is already travelling
- When empty the Lift tries to be smart. For example,
- If it was going up then it may continue up to collect the highest floor person
wanting to go down
- If it was going down then it may continue down to collect the lowest floor
person wanting to go up
- The Lift has a maximum capacity of people
- When called, the Lift will stop at a floor even if it is full, although unless
somebody gets off nobody else can get on!
- If the lift is empty, and no people are waiting, then it will return to the
ground floor People Rules:
- People are in "queues" that represent their order of arrival to wait for the
Lift
- All people can press the UP/DOWN Lift-call buttons
- Only people going the same direction as the Lift may enter it
- Entry is according to the "queue" order, but those unable to enter do not
block those behind them that can
- If a person is unable to enter a full Lift, they will press the UP/DOWN
Lift-call button again after it has departed without them
*/
std::vector<std::vector<int>> queues;
std::vector<int> result;

TEST_CASE("Lift test cases") {
  queues = {{}, {}, {5, 5, 5}, {}, {}, {}, {}};
  result = {0, 2, 5, 0};
  REQUIRE(the_lift(queues, 5) == (result));

  queues = {{}, {}, {1, 1}, {}, {}, {}, {}};
  result = {0, 2, 1, 0};
  REQUIRE(the_lift(queues, 5) == (result));

  queues = {{}, {3}, {4}, {}, {5}, {}, {}};
  result = {0, 1, 2, 3, 4, 5, 0};
  REQUIRE(the_lift(queues, 5) == (result));

  queues = {{}, {0}, {}, {}, {2}, {3}, {}};
  result = {0, 5, 4, 3, 2, 1, 0};
  REQUIRE(the_lift(queues, 5) == (result));

  queues = {{3}, {2}, {0}, {2}, {}, {}, {5}};
  result = {0, 1, 2, 3, 6, 5, 3, 2, 0};
  REQUIRE(the_lift(queues, 5) == (result));

  queues = {{},
            {},
            {
                4,
                4,
                4,
                4,
            },
            {},
            {
                2,
                2,
                2,
                2,
            },
            {},
            {}};
  result = {0, 2, 4, 2, 4, 2, 0};
  REQUIRE(the_lift(queues, 2) == (result));

  queues = {{},
            {},
            {},
            {
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
            },
            {},
            {},
            {}};
  result = {0, 3, 1, 3, 1, 3, 1, 0};
  REQUIRE(the_lift(queues, 5) == (result));

  queues = {{},
            {
                0,
                0,
                0,
                0,
            },
            {
                0,
                0,
                0,
                0,
            },
            {
                0,
                0,
                0,
                0,
            },
            {
                0,
                0,
                0,
                0,
            },
            {
                0,
                0,
                0,
                0,
            },
            {
                0,
                0,
                0,
                0,
            }};
  result = {0, 6, 5, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1,
            0, 4, 3, 2, 1, 0, 3, 2, 1, 0, 1, 0};
  REQUIRE(the_lift(queues, 5) == (result));
}
