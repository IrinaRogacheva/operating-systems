#include "Determinator.h"
#include <algorithm>
#include <iterator>
#include <set>

CGrammar::DeterministicGrammar CDeterminator::Determinate()
{
	GetOutsForStartState();
	GetSimpleOuts();
	GetCompositeOuts();
	
	return m_resultGrammar;
}

void CDeterminator::GetOutsForStartState()
{
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
	for (auto& item : m_grammar.GetGrammar())
	{
		if (!m_keysWithFoundStates.count(item.first) && item.first.first == firstState)
		{
			m_resultGrammar.emplace(item.first, GetResultOut(item.first));
			m_keysWithFoundStates.insert(item.first);
		}
	}

}

void CDeterminator::GetSimpleOuts()
{
	for (auto& item : m_grammar.GetGrammar())
	{
		auto findStateInResultGrammar = std::find_if(
			m_resultGrammar.begin(),
			m_resultGrammar.end(),
			[item](const auto& resultGrammarItem) {return resultGrammarItem.second == item.first.first; });

		if (!m_keysWithFoundStates.count(item.first) && findStateInResultGrammar != m_resultGrammar.end())
		{
			m_resultGrammar.emplace(item.first, GetResultOut(item.first));
			m_keysWithFoundStates.insert(item.first);
		}
	}
}

void CDeterminator::GetCompositeOuts()
{
	std::string resultOut;
	std::set<std::string> actions = m_grammar.GetActions();
	std::set<std::string> compositeStates;
	bool isNewCompositeState = true;

	while (isNewCompositeState)
	{
		isNewCompositeState = false;
		for (auto& item : m_resultGrammar)
		{
			if (item.second.size() > 1)
			{
				compositeStates.insert(item.second);
			}
			if (compositeStates.count(item.second) != 0)
			{
				for (auto& state : item.second)
				{
					for (auto& action : actions)
					{
						std::string stateStr = { state };
						resultOut = GetResultOut({ stateStr, action }, item.second);
						if (!resultOut.empty())
						{
							m_resultGrammar[{item.second, action}] = resultOut;
							if (resultOut.size() > 1 && compositeStates.find(resultOut) == compositeStates.end())
							{
								compositeStates.insert(resultOut);
								isNewCompositeState = true;
							}
							resultOut.clear();
						}
					}
				}
			}
		}
	}
}

std::string CDeterminator::GetResultOut(const std::pair<std::string, std::string>& stateActionPair, const std::string& changeableState)
{
	typedef CGrammar::NondeterministicGrammar::iterator GrammarIterator;
	CGrammar::NondeterministicGrammar grammar = m_grammar.GetGrammar();

	std::string resultOut;
	if (m_resultGrammar.find({ changeableState , stateActionPair.second}) != m_resultGrammar.end())
	{
		resultOut = m_resultGrammar[{ changeableState, stateActionPair.second}];
	}
	
	std::pair<GrammarIterator, GrammarIterator> duplicateKeys = grammar.equal_range(stateActionPair);
	for (GrammarIterator it = duplicateKeys.first; it != duplicateKeys.second; it++)
	{
		resultOut.append(it->second);
	}
	std::sort(resultOut.begin(), resultOut.end());
	auto res = std::unique(resultOut.begin(), resultOut.end());
	resultOut = std::string(resultOut.begin(), res);

	return resultOut;
}
