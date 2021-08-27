/* Reverse Polish Notation */

#include <iostream>
#include <vector>
#include <stack>
#include <string>

int getPrecedence(std::string &o) {
	if (o == "+" || o == "-") {
		return 1;
	}
	return 2; 
}


int calculate(int a, int b, const std::string &operation) {
	if (operation == "+") {
		return a + b; 
	}
	if (operation == "-") {
		return a - b;
	}
	if (operation == "*") {
		return a * b; 
	}
	if (operation == "/") {
		return a / b;
	}
	return -1;
}

void performOperation(std::stack<int> &numbers, std::stack<std::string> &operators) {
	int n1 = numbers.top();
	numbers.pop(); 
	int n2 = numbers.top();
	numbers.pop(); 
	std::string op = operators.top(); 
	operators.pop();

	numbers.push(calculate(n2, n1, op));
}


int RPN(std::vector<std::string> &notationExp) {
	std::stack<int> numbers; 
	std::stack<std::string> operators;

	if (notationExp.empty()) {
		return 0; 
	}

	numbers.push(stoi(notationExp[0])); 

	for (int i = 1; i < notationExp.size(); i += 2) {
		while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(notationExp[i])) {
			performOperation(numbers, operators);
		}

		numbers.push(std::stoi(notationExp[i + 1])); 
		operators.push(notationExp[i]); 
	}

	while (!operators.empty()) {
		performOperation(numbers, operators);
	}

	return numbers.top();
}



std::vector<std::string> parse(const std::string& input) {
	std::vector<std::string> vec; 
	std::string current;
	for (char c : input) {
		if (isdigit(c)) {
			current += c;
		}
		else if (c) {
			if (!current.empty()) {
				vec.emplace_back(std::move(current));
				current = "";
			}

			if (c != ' ') {
				vec.emplace_back(1, c);
			}
		}
	}

	if (!current.empty()) {
		vec.push_back(std::move(current));
	}
	return vec;
}

bool strCmp(std::string s1, std::string s2) {
	if (s1.size() != s2.size()) {
		return false;
	}
	for (int i = 0; i < s1.size(); i++) {
		if (s1[i] != s2[i]) {
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv) {
	// This program doesn't validate input.
	// It assumes that the input is always correct. 
	std::string input; 
	//std::getline(std::cin, input);
	//std::vector<std::string> notationExp = parse(input); 
	//std::cout << RPN(notationExp) << "\n";
	std::string quitExp = "quit";

	while (std::cout << "Enter a new expression: ", std::getline(std::cin, input)) {
		if (strCmp(input, quitExp)) {
			break;
		}
		std::vector<std::string> notationExp = parse(input);
		std::cout << RPN(notationExp) << "\n";
		
	}



	return 0; 
}


// test case 1 
// 1+2+3*3+3/3+5-4
// ans: 14  








