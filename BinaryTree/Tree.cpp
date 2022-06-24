#pragma once
#include "Node.cpp"
#include <memory>
#include <functional>

template<typename T>
class Tree
{
private:
	std::shared_ptr<Node<T>> head;
	std::function<int(T, T)> compareFunc;

	std::shared_ptr<Node<T>> extractMaxChild(std::shared_ptr<Node<T>> target)
	{
		std::shared_ptr<Node<T>> max = target;
		std::shared_ptr < Node<T> parent;
		while (max->RightChild != nullptr)
		{
			max = max->RightChild;
		}
		return max;
	}

	std::shared_ptr<Node<T>> replace(std::shared_ptr<Node<T>> targetNode)
	{
		if (targetNode->LeftChild == nullptr)
		{
			if (targetNode->RightChild == nullptr)
			{
				return nullptr;
			}
			else
			{
				return targetNode->RightChild;
			}
		}
		return extractMaxChild(targetNode->LeftChild);
	}

public:
	

	Tree(std::function<int(T, T)> compareFunc)
		: compareFunc{ compareFunc }  {}

	void Add(T value)
	{
		if (head == nullptr)
		{
			head = std::make_shared<Node<T>>(value);
		}
		std::shared_ptr<Node<T>> current = head;
		std::shared_ptr<Node<T>> parent;
		while (current != nullptr)
		{
			parent = current;
			int compareResult = compareFunc(value, current->Value);
			switch (compareResult)
			{
			case 1:
				current = current->RightChild;
				break;

			case 0:
				current = current->RightChild;
				break;

			case -1:
				current = current->LeftChild;
				break;
			}
		}
		int compareResult = compareFunc(value, parent->Value);
		switch (compareResult)
		{
		case 1:
			parent->RightChild = std::make_shared<Node<T>>(value);
			break;

		case 0:
			parent->RightChild = std::make_shared<Node<T>>(value);
			break;

		case -1:
			parent->LeftChild = std::make_shared<Node<T>>(value);
			break;
		}

	}

	bool Remove(T targetValue)
	{
		if (head == nullptr)
		{
			return false;
		}
		std::shared_ptr<Node<T>> current = head;
		std::shared_ptr<Node<T>> parent;
		while (current != nullptr)
		{
			int compareResult = compareFunc(targetValue, current->Value);
			switch (compareResult)
			{
			case 1:
				parent = current;
				current = current->RightChild;
				break;

			case 0:
				if (compareFunc(targetValue, parent->Value) == 1)
				{
					parent->RightChild = replace(parent->RightChild);
				}
				else
				{
					parent->LeftChild = replace(parent->LeftChild);
				}
				return true;
				break;

			case -1:
				parent = current;
				current = current->LeftChild;
				break;
			}
		}
		return false;
	}

};