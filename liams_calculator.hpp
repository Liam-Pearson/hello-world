/*
	TODO: add an include guard here
*/

#include <iostream>
#include <string>
#include <vector>

namespace calculator{

	class calculator{
	public:
		calculator(std::ostream& debug_log);

		float execute(std::string const equation);
	private:
		float add(float const a, float const b);
		float subtract(float const a, float const b);
		float divide(float const a, float const b);
		float multiply(float const a, float const b);

		float pow(float const base, float const exp);		
		float fact_i(int const n); // iterative factorial
		float fact_r(int const n); // recursive factorial

		bool hasSpaces(const std::string equation);
		bool consecutiveOperators(std::string const equation);
		bool equationLeadEndOpCleanup(std::string const equation);
		bool hasInvalidLeadingFactorial(const std::string equation);
		std::string wrapInBrackets(const std::string equation);
		bool bracketsMatch(std::string const equation);
		bool containsOperator(const std::string equation);
		std::vector<int> findInnermostBrackets(const std::string equation);
		std::vector<bool> numBeforeAfter(std::string equation, std::vector<int> bracketPos);
		std::string extractSubstring(const std::string equation, std::vector<int> bracketPos);
		std::string evaluateExpressionAsString(const std::string equation);
		std::string replacement(std::string result, std::string equation, std::vector<int> bracketPos);
		std::string insertMultiplicationAroundBrackets(std::string equation, std::vector<bool> bracketBool, std::vector<int> bracketPos);

		std::ostream& debug_log;
		
		float memory; // the result of the last execution
	};
}
