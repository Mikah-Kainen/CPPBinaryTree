#pragma once
#include <memory>

template<typename T>
class Node
{
public:
	T Value;
	std::shared_ptr<Node<T>> LeftChild;
	std::shared_ptr<Node<T>> RightChild;
	Node(T value)
		: Value{value} {}


};