#include <iostream>
#include <string>
#include "Stack.cpp"

bool f1(char a, char b)
{
	switch (a) {
	case '+':
	case '-':
		return true;
	case '*':
	case '/':
	case '%':
		if (b == '+' || b == '-')
			return false;
		else
			return true;
	}
}

int f2(std::string &s)
{
	std::string sr;
	for (int i = s.size() - 1; i >= 0; --i)
		sr += s[i];
	return std::stoi(sr);
}

std::string f3(char c, int a, int b)
{
	switch (c) {
	case '+':
		return std::to_string(a + b);
	case '-':
		return std::to_string(a - b);
	case '*':
		return std::to_string(a * b);
	case '/':
		return std::to_string(a / b);
	case '%':
		return std::to_string(a % b);
	}
}

int main()
{
	std::string expr;
	std::cin >> expr;

	Stack<char> ops;
	Stack<char> nums;
	char op;
	char num;
	std::string s1;
	int lhs;
	int rhs;
	std::string s2;

	for (size_t i = 0; i < expr.size(); ++i) {
		if (expr[i] >= '0' && expr[i] <= '9')
			nums.push(expr[i]);
		else {
			if (ops.empty()) {
				ops.push(expr[i]);

				if (!nums.empty())
					nums.push(',');
			}
			else {
				if (expr[i] == '(')
					ops.push(expr[i]);
				else if (expr[i] == ')') {
					op = ops.top();

					while (op != '(') {
						num = nums.top();

						while (num != ',') {
							s1 += num;
							nums.pop();
							num = nums.top();
						}

						rhs = f2(s1);
						s1.clear();
						nums.pop();
						num = nums.top();

						while (num != ',') {
							s1 += num;
							nums.pop();

							if (nums.empty())
								break;

							num = nums.top();
						}

						lhs = f2(s1);
						s1.clear();
						s2 = f3(op, lhs, rhs);

						for (size_t j = 0; j < s2.size(); ++j)
							nums.push(s2[j]);

						ops.pop();
						op = ops.top();
					}

					ops.pop();
				}
				else {
					op = ops.top();

					while (op != '(' && f1(expr[i], op)) {
						num = nums.top();

						while (num != ',') {
							s1 += num;
							nums.pop();
							num = nums.top();
						}

						rhs = f2(s1);
						s1.clear();
						nums.pop();
						num = nums.top();

						while (num != ',') {
							s1 += num;
							nums.pop();

							if (nums.empty())
								break;

							num = nums.top();
						}

						lhs = f2(s1);
						s1.clear();
						s2 = f3(op, lhs, rhs);

						for (size_t j = 0; j < s2.size(); ++j)
							nums.push(s2[j]);

						ops.pop();

						if (ops.empty())
							break;

						op = ops.top();
					}

					ops.push(expr[i]);
					nums.push(',');
				}
			}
		}
	}

	while (!ops.empty()) {
		op = ops.top();
		num = nums.top();

		while (num != ',') {
			s1 += num;
			nums.pop();
			num = nums.top();
		}

		rhs = f2(s1);
		s1.clear();
		nums.pop();
		num = nums.top();

		while (num != ',') {
			s1 += num;
			nums.pop();

			if (nums.empty())
				break;

			num = nums.top();
		}

		lhs = f2(s1);
		s1.clear();
		s2 = f3(op, lhs, rhs);

		for (size_t j = 0; j < s2.size(); ++j)
			nums.push(s2[j]);

		ops.pop();

		if (ops.empty())
			break;

		op = ops.top();
	}
	
	std::string res;

	while (!nums.empty()) {
		res += nums.top();
		nums.pop();
	}

	std::cout << f2(res) << std::endl;

	return 0;
}