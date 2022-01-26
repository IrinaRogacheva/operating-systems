#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../RegularExpressions/Converter.h"
#include "../RegularExpressions/Automaton.h"

TEST_CASE("simple line")
{
	CConverter converter("abc");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, "a"}, 1}, {{1, "b"}, 2}, {{2, "c"}, 3} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("Asterisk")
{
	CConverter converter("a*");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, std::nullopt}, 2}, {{2, "a"}, 2}, {{2, std::nullopt}, 1} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("two asterisks")
{
	CConverter converter("a*b*");
	
	CAutomaton::NondeterministicAutomaton automaton = { {{0, std::nullopt}, 2}, {{2, "a"}, 2}, {{1, std::nullopt}, 4}, {{2, std::nullopt}, 1}, {{4, "b"}, 4}, {{4, std::nullopt}, 3} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("complicate asterisks")
{
	CConverter converter("a*b*cd*");
	
	CAutomaton::NondeterministicAutomaton automaton = { {{0, std::nullopt}, 2}, {{2, "a"}, 2}, {{1, std::nullopt}, 4}, {{2, std::nullopt}, 1}, {{4, "b"}, 4}, {{4, std::nullopt}, 3}, {{3, "c"}, 5}, {{5, std::nullopt}, 6}, {{6, std::nullopt}, 7}, {{6, "d"}, 6}};

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("Asterisk and char after")
{
	CConverter converter("a*b");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, std::nullopt}, 2}, {{2, "a"}, 2}, {{2, std::nullopt}, 1}, {{1, "b"}, 3} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("Asterisk and char after and before")
{
	CConverter converter("ca*b");
	CAutomaton::NondeterministicAutomaton automaton = { {{0, "c"}, 1}, {{1, std::nullopt}, 3}, {{3, "a"}, 3}, {{3, std::nullopt}, 2}, {{2, "b"}, 4} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

/*
TEST_CASE("plus sign")
{
	CConverter converter("a+");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, "a"}, 1}, {{1, "a"}, 1}, {{1, std::nullopt}, 2} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}
*/

TEST_CASE("or")
{
	CConverter converter("a|b");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, "a"}, 1}, {{0, "b"}, 1} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("few or")
{
	CConverter converter("a|b|c|d");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, "a"}, 1}, {{0, "b"}, 1}, {{0, "c"}, 1}, {{0, "d"}, 1} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("or and line after")
{
	CConverter converter("a|b|cd");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, "a"}, 1}, {{0, "b"}, 1}, {{0, "c"}, 1}, {{1, "d"}, 2} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("or and line before")
{
	CConverter converter("da|b|c");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, "d"}, 1}, {{1, "a"}, 2}, {{1, "b"}, 2}, {{1, "c"}, 2} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("or and star at second elem")
{
	CConverter converter("a|b*");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, "a"}, 1}, {{0, std::nullopt}, 2}, {{2, "b"}, 2}, {{2, std::nullopt}, 1} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("or and star at first elem")
{
	CConverter converter("a*|b");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, std::nullopt}, 2}, {{2, "a"}, 2}, {{2, std::nullopt}, 1}, {{0, "b"}, 1} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("or and star at first and second elem")
{
	CConverter converter("a*|b*");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, std::nullopt}, 2}, {{2, "a"}, 2}, {{2, std::nullopt}, 1}, {{0, std::nullopt}, 3}, { {3, "b"}, 3}, {{3, std::nullopt}, 1} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("or and star at first and second elem and third")
{
	CConverter converter("a*|b*|c*");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, std::nullopt}, 2}, {{2, "a"}, 2}, {{2, std::nullopt}, 1}, {{0, std::nullopt}, 3}, { {3, "b"}, 3}, {{3, std::nullopt}, 1}, {{0, std::nullopt}, 4}, { {4, "c"}, 4}, {{4, std::nullopt}, 1} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("or and star at first and second elem and third and line before and after")
{
	CConverter converter("da*|b*|c*f");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, "d"}, 1}, {{1, std::nullopt}, 3}, {{3, "a"}, 3}, {{3, std::nullopt}, 2}, {{1, std::nullopt}, 4}, {{4, "b"}, 4}, {{4, std::nullopt}, 2}, {{1, std::nullopt}, 5}, {{5, "c"}, 5}, {{5, std::nullopt}, 2}, {{2, "f"}, 6} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("bracket + asterisk")
{
	CConverter converter("(abc)*");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, std::nullopt}, 2}, {{2, std::nullopt}, 1}, {{2, "a"}, 3}, {{3, "b"}, 4}, {{4, "c"}, 2} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("bracket + asterisk + line before and after")
{
	CConverter converter("d(abc)*fk");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, "d"}, 1}, {{1, std::nullopt}, 3}, {{2, "f"}, 7}, {{3, std::nullopt}, 2}, {{3, "a"}, 4}, {{4, "b"}, 5}, {{5, "c"}, 3}, {{7, "k"}, 8} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}

TEST_CASE("bracket + asterisk + or in brackets")
{
	CConverter converter("d(a|b|c)*fk");

	CAutomaton::NondeterministicAutomaton automaton = { {{0, "d"}, 1}, {{1, std::nullopt}, 3}, {{2, "f"}, 5}, {{3, std::nullopt}, 2}, {{4, std::nullopt}, 3}, {{3, "a"}, 4}, {{3, "b"}, 4}, {{3, "c"}, 3}, {{5, "k"}, 6} };

	REQUIRE(converter.ConvertExpressionToAutomaton().GetAutomaton() == automaton);
}