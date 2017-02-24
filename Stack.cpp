#include "Stack.h"

template<typename Type>
inline Stack<Type>::Stack():
	theCapacity(50)
{
	theArray = new Type[theCapacity]();
}

template<typename Type>
Stack<Type>::Stack(Stack &s):
	theCapacity(s.theCapacity)
{
	theArray = new Type[theCapacity]();

	size_t theSize = s.topOfStack + 1;
	s.topOfStack = 0;
	for (size_t i = 0; i < theSize; ++i) {
		push(s.top());
		++s.topOfStack;
	}
	--s.topOfStack;
}

template<typename Type>
Stack<Type> & Stack<Type>::operator=(Stack &rhs)
{
	if (this != &rhs) {
		delete[] theArray;

		topOfStack = -1;
		theCapacity = rhs.theCapacity;
		theArray = new Type[theCapacity]();

		size_t theSize = rhs.topOfStack + 1;
		rhs.topOfStack = 0;
		for (size_t i = 0; i < theSize; ++i) {
			push(rhs.top());
			++rhs.topOfStack;
		}
		--rhs.topOfStack;
	}

	return *this;  // TODO: 在此处插入 return 语句
}

template<typename Type>
Stack<Type>::~Stack()
{
	delete[] theArray;
}

template<typename Type>
size_t Stack<Type>::size()
{
	return topOfStack + 1;
}

template<typename Type>
bool Stack<Type>::empty()
{
	return topOfStack == -1;
}

template<typename Type>
void Stack<Type>::push(const Type &t)
{
	size_t theSize = topOfStack + 1;
	if (theSize == theCapacity) {
		theCapacity = 2 * theSize;
		Type *pNew = new Type[theCapacity]();
		
		topOfStack = 0;
		for (size_t i = 0; i < theSize; ++i) {
			pNew[i] = top();
			++topOfStack;
		}
		--topOfStack;
	}

	++topOfStack;
	theArray[topOfStack] = t;
}

template<typename Type>
Type & Stack<Type>::top()
{
	if (empty())
		throw std::invalid_argument("");

	return theArray[topOfStack];  // TODO: 在此处插入 return 语句
}

template<typename Type>
void Stack<Type>::pop()
{
	if (empty())
		throw std::invalid_argument("");

	--topOfStack;
}
