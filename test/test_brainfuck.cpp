#include "brainfuck.hpp"
#include "catch2/catch.hpp"
// clang-format off
// > increment the data pointer (to point to the next cell to the right).
// < decrement the data pointer (to point to the next cell to the left).
// + increment (increase by one, truncate overflow: 255 + 1 = 0) the byte at the data pointer.
// - decrement (decrease by one, treat as unsigned byte: 0 - 1 = 255 ) the byte at the data pointer.
// . output the byte at the data pointer.
// , accept one byte of input, storing its value in the byte at the data pointer.
// [ if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
// ] if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.
// clang-format on

TEST_CASE("ReadOneEchoOne") {
  const std::string input = "a";
  const std::string output = brainLuck(",.", input);
  const std::string expected = "a";
  REQUIRE(output == expected);
}
TEST_CASE("ReadTwoEchoLast") {
  const std::string input = "ab";
  const std::string output = brainLuck(",>,.", input);
  const std::string expected = "b";
  REQUIRE(output == expected);
}
TEST_CASE("ReadTwoEchoFirst") {
  const std::string input = "ab";
  const std::string output = brainLuck(",>,<.", input);
  const std::string expected = "a";
  REQUIRE(output == expected);
}
TEST_CASE("Increment") {
  const std::string input = "a";
  const std::string output = brainLuck(",+.", input);
  const std::string expected = "b";
  REQUIRE(output == expected);
}
TEST_CASE("Decrement") {
  const std::string input = "b";
  const std::string output = brainLuck(",-.", input);
  const std::string expected = "a";
  REQUIRE(output == expected);
}
TEST_CASE("Inititalized") {
  const std::string input = "";
  const std::string output = brainLuck(".", input);
  const std::string expected(1, static_cast<char>(0));
  REQUIRE(output == expected);
}
TEST_CASE("DecrementUnderflow") {
  const std::string input = "";
  const std::string output = brainLuck("-.", input);
  const std::string expected(1, static_cast<char>(255));
  REQUIRE(output == expected);
}
TEST_CASE("DecrementUnderflowIncrementOverflow") {
  const std::string input = "";
  const std::string output = brainLuck("-+.", input);
  const std::string expected(1, static_cast<char>(0));
  REQUIRE(output == expected);
}
TEST_CASE("Loop") {
  const std::string input = "f";
  const std::string output = brainLuck(",[.-]", input);
  std::string expected{};
  for (int i = static_cast<int>(input.back()); i > 0; --i)
    expected.append(1, static_cast<char>(i));
  REQUIRE(output == expected);
}
TEST_CASE("Skip first loop") {
  const std::string input = "";
  const std::string output = brainLuck("[.-]+[.-]", input);
  std::string expected(1, static_cast<char>(1));
  REQUIRE(output == expected);
}
TEST_CASE("Nested loops") {
  const std::string input = "";
  const std::string output = brainLuck("+[-[.-]+[.-]].", input);
  std::string expected(1, static_cast<char>(1));
  expected.append(1, static_cast<char>(0));
  REQUIRE(output == expected);
}
TEST_CASE("Skip nested loops") {
  const std::string input = "";
  const std::string output = brainLuck("[-[.-]+[.-]].", input);
  std::string expected(1, static_cast<char>(0));
  REQUIRE(output == expected);
}
TEST_CASE("Repeat nested loops") {
  const std::string input = "";
  const std::string output = brainLuck("++[.>[-]<-].", input);
  std::string expected(1, static_cast<char>(2));
  expected.append(1, static_cast<char>(1));
  expected.append(1, static_cast<char>(0));
  REQUIRE(output == expected);
}
TEST_CASE("Codewars") {
  // echo until "255"
  std::string tw = "codewars";
  tw.append(1, (char)255);
  REQUIRE(brainLuck(",+[-.,+]", tw) == "codewars");

  // echo until "0";
  std::string mw = "codewars";
  mw.append(1, (char)0);
  REQUIRE(brainLuck(",[.[-],]", mw) == "codewars");

  // two number multiplier
  std::string dw;
  dw.append(1, (char)7);
  dw.append(1, (char)3);
  std::string result;
  result.append(1, (char)21);
  REQUIRE(brainLuck(",>,<[>[->+>+<<]>>[-<<+>>]<<<-]>>.", dw) == result);

  // Skip loop completly
  std::string ew;
  ew.append(1, (char)8);
  ew.append(1, (char)0);
  result.clear();
  result.append(1, (char)0);
  REQUIRE(brainLuck(",>,<[>[->+>+<<]>>[-<<+>>]<<<-]>>.", ew) == result);

  std::string fw(1, (char)10);
  result = "1, 1, 2, 3, 5, 8, 13, 21, 34, 55";
  REQUIRE(brainLuck(
      ",>+>>>>++++++++++++++++++++++++++++++++++++++++++++>++++++++++++"
      "++++++++++++++++++++<<<<<<[>[>>>>>>+>+<<<<<<<-]>>>>>>>[<<<<<<<+>"
      ">>>>>>-]<[>++++++++++[-<-[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<"
      "<[>>>+<<<-]>>[-]]<<]>>>[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<+"
      ">>[-]]<<<<<<<]>>>>>[++++++++++++++++++++++++++++++++++++++++++++"
      "++++.[-]]++++++++++<[->-<]>+++++++++++++++++++++++++++++++++++++"
      "+++++++++++.[-]<<<<<<<<<<<<[>>>+>+<<<<-]>>>>[<<<<+>>>>-]<-[>>.>."
      "<<<[-]]<<[>>+>+<<<-]>>>[<<<+>>>-]<<[<+>-]>[<+>-]<<<-]",
      fw) == result);
}
