#include "Determinator.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <set>

void CDeterminator::Determinate()
{
	std::multimap<std::pair<std::string, std::string>, std::string> grammar = m_grammar.GetGrammar();
	std::map<std::pair<std::string, std::string>, std::string> resultGrammar;

	typedef CGrammar::Grammar::iterator GrammarIterator;

	std::set<std::pair<std::string, std::string>> uniqueKeys;
	std::string firstState;
	if (m_grammar.GetGrammarType() == CGrammar::GrammarType::RIGHT)
	{
		firstState = "S";
	}
	else
	{
		firstState = "H";
	}

	std::string resultOut;
	for (auto& item : grammar)
	{
		if (!uniqueKeys.count(item.first) && item.first.first == firstState)
		{
			std::pair<GrammarIterator, GrammarIterator> duplicateKeys = grammar.equal_range(item.first);
			std::cout << item.first.first << " " << item.first.second << std::endl;
			
			for (GrammarIterator it = duplicateKeys.first; it != duplicateKeys.second; it++)
			{
				std::cout << it->second << std::endl;
				resultOut.append(it->second);
			}
			std::sort(resultOut.begin(), resultOut.end());
			auto res = std::unique(resultOut.begin(), resultOut.end());
			resultOut = std::string(resultOut.begin(), res);
			resultGrammar.emplace(item.first, resultOut);
			std::cout << "it's result string: " << resultOut << std::endl;
			/*if (resultOut.size() > 1)
			{
				grammar.insert({ {resultOut, ""}, "" });
			}*/
			resultOut.clear();
			uniqueKeys.insert(item.first);
		}
	}

	std::cout << std::endl << "result after first action: " << std::endl;
	for (auto& item : resultGrammar)
	{
		std::cout << item.first.first << " " << item.first.second << " " << item.second << std::endl;
	}

	for (auto& item : grammar)
	{
		auto findResult = std::find_if(
			resultGrammar.begin(),
			resultGrammar.end(),
			[item](const auto& mo) {return mo.second == item.first.first; });

		std::cout << item.first.first << " " << item.first.second << std::endl;
		if (!uniqueKeys.count(item.first) && findResult != resultGrammar.end())
		{
			std::pair<GrammarIterator, GrammarIterator> duplicateKeys = grammar.equal_range(item.first);
			std::cout << item.first.first << " " << item.first.second << std::endl;

			for (GrammarIterator it = duplicateKeys.first; it != duplicateKeys.second; it++)
			{
				std::cout << it->second << std::endl;
				resultOut.append(it->second);
			}
			std::sort(resultOut.begin(), resultOut.end());
			auto res = std::unique(resultOut.begin(), resultOut.end());
			resultOut = std::string(resultOut.begin(), res);
			resultGrammar.emplace(item.first, resultOut);
			std::cout << "it's result string: " << resultOut << std::endl;
			resultOut.clear();
			uniqueKeys.insert(item.first);
		}
	}

	std::cout << std::endl;

	std::set<std::string> actions = m_grammar.GetActions();
	std::map<std::string, bool> compositeStates;
	bool isNewCompositeState = true;
	while (isNewCompositeState)
	{
		isNewCompositeState = false;
		for (auto& item : resultGrammar)
		{
			std::cout << item.first.first << " " << item.first.second << " " << item.second << std::endl;
			if (item.second.size() > 1)
			{
				std::cout << "ITEM.SECOND: " << item.second << " size: " << item.second.size() << std::endl;
				compositeStates.emplace(item.second, false);
			}
			if (compositeStates.find(item.second) != compositeStates.end())
			{
				std::cout << "state from item second: " << item.second << std::endl;
				for (auto& state : item.second)
				{
					std::cout << "composite state: " << state << std::endl;
					for (auto& action : actions)
					{
						std::cout << "action: " << action << std::endl;
						std::string stateStr = { state };
						std::pair<GrammarIterator, GrammarIterator> duplicateKeys = grammar.equal_range({ stateStr, action });

						for (GrammarIterator it = duplicateKeys.first; it != duplicateKeys.second; it++)
						{
							std::cout << "from duplicate: " << it->second << std::endl;
							resultOut.append(it->second);
						}
						if (!resultOut.empty())
						{
							std::cout << "stateStr: " << item.second << " action: " << action << " resultOut: " << resultOut << std::endl;
							std::string out = resultGrammar[{item.second, action}];
							out.append(resultOut);
							std::cout << "out: " << out << std::endl;
							std::sort(out.begin(), out.end());
							std::cout << "sorted out: " << out << std::endl;
							auto res = std::unique(out.begin(), out.end());
							out = std::string(out.begin(), res);
							std::cout << "sorted unique out: " << out << std::endl;
							resultGrammar[{item.second, action}] = out;
							if (out.size() > 1 && compositeStates.find(out) == compositeStates.end())
							{
								compositeStates[out] = false;
								isNewCompositeState = true;
							}
							std::cout << "it's result string from composite str: " << resultOut << std::endl;
							resultOut.clear();
						}
					}
				}
			}
			compositeStates[item.second] = true;
		}
	}
	std::cout << "Result" << std::endl;
	for (auto& item : resultGrammar)
	{
		std::cout << item.first.first << " " << item.first.second << " " << item.second << std::endl;
	}
}
