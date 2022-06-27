#pragma once
#include <iostream>
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
		std::shared_ptr<Node<T>> parent = target;
		std::shared_ptr<Node<T>> max = target->RightChild;
		while (max->RightChild != nullptr)
		{
			parent = max;
			max = max->RightChild;
		}
		parent->RightChild = nullptr;
		return max;
	}

	std::shared_ptr<Node<T>> replace(std::shared_ptr<Node<T>> targetNode)
	{
		if (targetNode->LeftChild == nullptr)
		{
			std::cout << "case 1\n";
			return targetNode->RightChild;
		}
		else if (targetNode->LeftChild->RightChild == nullptr)
		{
			std::cout << "case 2\n";
			targetNode->LeftChild->RightChild = targetNode->RightChild;
			return targetNode->LeftChild;
		}
		else
		{
			std::cout << "case 3\n";
			std::shared_ptr<Node<T>> temp = extractMaxChild(targetNode->LeftChild);
			temp->LeftChild = targetNode->LeftChild;
			temp->RightChild = targetNode->RightChild;
			return temp;
		}
	}

public:
	

	Tree(std::function<int(T, T)> compareFunc)
		: compareFunc{ compareFunc }  {}

	void Add(T value)
	{
		if (head == nullptr)
		{
			head = std::make_shared<Node<T>>(value);
			return;
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
		else if (head->Value == targetValue)
		{
			head = replace(head);
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