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

		float calc(std::vector<float> nums, std::vector<char> ops);
	private:
		float add(float const a, float const b);
		float subtract(float const a, float const b);
		float divide(float const a, float const b);
		float multiply(float const a, float const b);

		float pow(float const base, float const exp);		
		float fact_i(int const n); // iterative factorial
		float fact_r(int const n); // recursive factorial

		

		std::ostream& debug_log;
		
		float memory; // the result of the last execution
	};
}
