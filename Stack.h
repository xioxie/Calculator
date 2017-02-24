#include <stdexcept>
#pragma once

template<typename Type>
class Stack {
public:
	Stack();
	Stack(Stack &);
	Stack & operator=(Stack &);
	~Stack();

	size_t size();
	bool empty();

	void push(const Type &);
	Type & top();
	void pop();
private:
	Type *theArray;
	int topOfStack = -1;
	size_t theCapacity;
};
