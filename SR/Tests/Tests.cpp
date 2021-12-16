#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "../SR/recursive_descent.h"

SCENARIO("nonterminal F")
{
	WHEN("expression is '7'")
	{
		std::istringstream iss("7");
		std::ostringstream oss;

		CheckExpression(iss, oss);

		THEN("It's Ok")
		{
			REQUIRE(oss.str() == "Ok\n");
		}
	}

	AND_WHEN("expression is 'a'")
	{
		std::istringstream iss("a");
		std::ostringstream oss;

		CheckExpression(iss, oss);

		THEN("It's Ok")
		{
			REQUIRE(oss.str() == "Ok\n");
		}
	}

	AND_WHEN("expression is '-a'")
	{
		std::istringstream iss("-a");
		std::ostringstream oss;

		CheckExpression(iss, oss);

		THEN("It's Ok")
		{
			REQUIRE(oss.str() == "Ok\n");
		}
	}

	AND_WHEN("expression is '(E)' (when M and N are empty, E->F, for example '7')")
	{
		std::istringstream iss("(7)");
		std::ostringstream oss;

		CheckExpression(iss, oss);

		THEN("It's Ok")
		{
			REQUIRE(oss.str() == "Ok\n");
		}
	}

	AND_WHEN("expression is '(E' (without ')' at the end)")
	{
		std::istringstream iss("(7");
		std::ostringstream oss;

		CheckExpression(iss, oss);

		THEN("It's Error")
		{
			REQUIRE(oss.str() == "Error\n");
		}
	}

	AND_WHEN("expression is '*'")
	{
		std::istringstream iss("*");
		std::ostringstream oss;

		CheckExpression(iss, oss);

		THEN("It's Error")
		{
			REQUIRE(oss.str() == "Error\n");
		}
	}
}

SCENARIO("nonterminal E")
{
	WHEN("expression is '(E)', then (TM) and M is empty, N is *FN'")
	{
		std::istringstream iss("(a*7)");
		std::ostringstream oss;

		CheckExpression(iss, oss);

		THEN("It's Ok")
		{
			REQUIRE(oss.str() == "Ok\n");
		}
	}

	AND_WHEN("expression is '(E)', then (TM) and M is empty, F in FN is '-F' N is *FN'")
	{
		std::istringstream iss("(-a*7*a)");
		std::ostringstream oss;

		CheckExpression(iss, oss);

		THEN("It's Ok")
		{
			REQUIRE(oss.str() == "Ok\n");
		}
	}

	AND_WHEN("expression than T is false")
	{
		std::string str = " 7*7";

		THEN("It's false")
		{
			REQUIRE(E(str) == false);
		}
	}

	AND_WHEN("expression T doesn't have N at the end")
	{
		std::string str = "(7+a)";

		THEN("It's false")
		{
			REQUIRE(E(str) == false);
		}
	}
}

SCENARIO("nonterminal M")
{
	WHEN("expression is ''")
	{
		std::string str = "";
		
		THEN("It's true")
		{
			REQUIRE(M(str) == true);
		}
	}

	AND_WHEN("expression is '+TM', then M and N are empty")
	{
		std::string str = "+7";

		THEN("It's true")
		{
			REQUIRE(M(str) == true);
		}
	}

	AND_WHEN("expression is '+TM', then M is empty")
	{
		std::string str = "+7*a";

		THEN("It's true")
		{
			REQUIRE(M(str) == true);
		}
	}

	AND_WHEN("expression doesn't start from '+'")
	{
		std::string str = " ";

		THEN("It's false")
		{
			REQUIRE(M(str) == false);
		}
	}

	AND_WHEN("expression doesn't end at M")
	{
		std::string str = "+7-a";

		THEN("It's false")
		{
			REQUIRE(M(str) == false);
		}
	}

	AND_WHEN("expression doesn't start at T")
	{
		std::string str = "+*a";

		THEN("It's false")
		{
			REQUIRE(M(str) == false);
		}
	}
}

SCENARIO("nonterminal N")
{
	WHEN("expression is ''")
	{
		std::string str = "";

		THEN("It's true")
		{
			REQUIRE(N(str) == true);
		}
	}

	AND_WHEN("expression is '*FN', then N is empty")
	{
		std::string str = "*7";

		THEN("It's true")
		{
			REQUIRE(N(str) == true);
		}
	}

	AND_WHEN("expression is '*FN', then M is not empty")
	{
		std::string str = "*7*a";

		THEN("It's true")
		{
			REQUIRE(N(str) == true);
		}
	}

	AND_WHEN("expression doesn't start from '+'")
	{
		std::string str = " ";

		THEN("It's false")
		{
			REQUIRE(N(str) == false);
		}
	}

	AND_WHEN("expression doesn't have N at the end")
	{
		std::string str = "*7a";

		THEN("It's false")
		{
			REQUIRE(N(str) == false);
		}
	}

	AND_WHEN("expression doesn't have F at the start")
	{
		std::string str = "* 7";

		THEN("It's false")
		{
			REQUIRE(N(str) == false);
		}
	}
}
