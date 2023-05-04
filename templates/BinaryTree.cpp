#pragma once

#include <iostream>
#include "BinaryTree.h"
#include "../ContainerException.h"

//==========================
//  Конструкторы
//==========================

template<typename Type>
BinaryTree<Type>::BinaryTree()
{
	this->mainRoot = nullptr;
}

template<typename Type>
BinaryTree<Type>::BinaryTree(Type* data)
{
	if (!data) this->mainRoot = nullptr;
	this->mainRoot = new TreeNode(data);
}

template<typename Type>
BinaryTree<Type>::BinaryTree(const BinaryTree<Type>& other)
{
	this->mainRoot = nullptr;
	this->mainRoot = this->Copy(this->mainRoot, other.mainRoot);
}

// Деструктор
template<typename Type>
BinaryTree<Type>::~BinaryTree()
{
	this->ClrTree(this->mainRoot);
	this->mainRoot = nullptr;
}

//==========================
//--------------------------
//==========================

// Добавить информацию в дерево
template<typename Type>
void BinaryTree<Type>::AddData(Type data)
{
	this->mainRoot = PushNode(data, this->mainRoot);
}

// Удалить информацию из дерева
template<typename Type>
void BinaryTree<Type>::RemoveData(Type* data)
{
	this->mainRoot = this->RemoveData(this->mainRoot, data);
}

//// Удалить узел по фильтру
//template<typename Type>
//void BinaryTree<Type>::RemoveWhere(Type& searchMask, Comparator<Type>* comparator)
//{
//    Type* toDel = this->FindWhere(this->mainRoot, &searchMask, comparator);
//    if (toDel)
//    {
//        this->mainRoot = this->RemoveData(this->mainRoot, toDel);
//    }
//}

// Вернуть значение корня
template<typename Type>
Type* BinaryTree<Type>::GetRootData()
{
	if (this->mainRoot) return &(this->mainRoot->data);
	return nullptr;
}


// Добавить элемент в дерево
template<typename Type>
BinaryTree<Type>::template TreeNode* BinaryTree<Type>::PushNode(Type data, TreeNode* root, TreeNode* previous)
{
	if (root)
	{
		// Поиск места для вставки элемента
		if (data > root->data) root->right = PushNode(data, root->right, root);
		else if (data < root->data) root->left = PushNode(data, root->left, root);
		else
		{
			root->left = PushNode(data, root->left, root);
		}
	}
	else
	{
		// Вставка элемента
		root = new TreeNode(&data);
		root->right = nullptr;
		root->left = nullptr;
		root->previous = previous;
	}
	return root;
}


// Очистка дерева
template<typename Type>
void BinaryTree<Type>::ClrTree()
{
	this->ClrTree(this->mainRoot);
	this->mainRoot = nullptr;
}

// Внутренняя функция очистки дерева
template<typename Type>
void BinaryTree<Type>::ClrTree(TreeNode* node)
{
	if (node)
	{
		ClrTree(node->left);
		ClrTree(node->right); //this
		delete node;
		node = nullptr;
	}
}

// Скопировать все узлы дерева
template<typename Type>
BinaryTree<Type>::template TreeNode* BinaryTree<Type>::Copy(TreeNode* node, TreeNode* other, TreeNode* previous)
{
	if (other)
	{
		node = new TreeNode(&other->data);
		node->previous = previous;
		node->right = this->Copy(node->right, other->right, node);
		node->left = this->Copy(node->left, other->left, node);
		return node;
	}
	return nullptr;
}


// Удалить узел с информацией data
template<typename Type>
BinaryTree<Type>::template TreeNode* BinaryTree<Type>::RemoveData(TreeNode* node, Type* data)
{
	if (node)
	{
		// Поиск удаляемого узла
		if (node->data < *data) node->right = RemoveData(node->right, data);
		else if (node->data > *data) node->left = RemoveData(node->left, data);
		else
		{
			// Нужно на случай, если операции > и < сравнивают одно поле, а операция == все поля класса 
			if (node->data != *data) node->left = RemoveData(node->left, data);
			else
			{
				// Если у узла нет связей, то удаляем его
				if (!(node->left) && !(node->right))
				{
					delete node;
					return nullptr;
				}
				// Если у узла есть 2 связи, то заменяем его на минимальный узел в его правом поддереве
				else if (node->right && node->left)
				{
					TreeNode* minInRightTree = GetMinInTree(node->right);
					node->data = minInRightTree->data;

					node->right = RemoveData(node->right, &minInRightTree->data);
				}
				// Если у узла только левая связь, то связываем левый указатель предыдущего узла с левым от удаляемого
				else if (node->left)
				{
					TreeNode* tmp = node->left;
					node->left->previous = node->previous;
					delete node;
					return tmp;
				}
				// Аналогично предыдущему
				else if (node->right)
				{
					TreeNode* tmp = node->right;
					node->right->previous = node->previous;
					delete node;
					return tmp;
				}
			}
		}
	}
	return node;
}

// Найти минимальный элемент в дереве
template<typename Type>
BinaryTree<Type>::template TreeNode* BinaryTree<Type>::GetMinInTree(TreeNode* root)
{
	if (root)
	{
		if (root->left)
			return GetMinInTree(root->left);
		else
			return root;
	}
	return 0;
}


// Вернуть узел корня
template<typename Type>
BinaryTree<Type>::template TreeNode* BinaryTree<Type>::GetRoot()
{
	return this->mainRoot;
}

// Оператор присовения
template<typename Type>
BinaryTree<Type>& BinaryTree<Type>::operator=(const BinaryTree<Type>& other)
{
	this->ClrTree(this->mainRoot);
	this->mainRoot = this->Copy(this->mainRoot, other.mainRoot);
	return *this;
}

// Вернуть итератор на 1 элемент дерева(самый левый)
template<typename Type>
BinaryTree<Type>::template Iterator BinaryTree<Type>::Begin()
{
	Iterator it(this->GetMinInTree(this->mainRoot));
	return it;
}

// Вернуть иетратор на конец дерева
template<typename Type>
BinaryTree<Type>::template Iterator BinaryTree<Type>::End()
{
	if (!this->mainRoot) return Iterator(nullptr);
	TreeNode* node = this->mainRoot->previous;
	TreeNode* cameFrom = this->mainRoot;

	while (cameFrom->right) cameFrom = cameFrom->right;

	Iterator it(node, cameFrom);
	return it;
}

// Конструктор TreeNode
template<typename Type>
BinaryTree<Type>::TreeNode::TreeNode(Type* data)
{
	this->data = *data;
	this->left = nullptr;
	this->right = nullptr;
	this->previous = nullptr;
}

// Деструктор TreeNode
template<typename Type>
BinaryTree<Type>::TreeNode::~TreeNode()
{
	this->left = nullptr;
	this->right = nullptr;
	this->previous = nullptr;
}

// Контруктор итератора по умолчанию
template<typename Type>
BinaryTree<Type>::Iterator::Iterator()
{
	current = nullptr;
	nodeCameFrom = nullptr;
}

// Конструктор с определёнными данными
template<typename Type>
BinaryTree<Type>::Iterator::Iterator(TreeNode* current, TreeNode* cameFrom)
{
	this->current = current;
	this->nodeCameFrom = cameFrom;
}

// Опеартор перемещение итератора на следующий элемент вправо
template<typename Type>
Type& BinaryTree<Type>::Iterator::operator++(int value)
{
	if (!current) throw ContainerException("Cant use ++ on nullptr");
	if (!current->right)  // От наличия правой ветви зависит дальнейший алгоритм
	{
		do  // Цикл перемещает итератор вверх по дереву до тех, пор, пока не обнаружит
			//что поднялся по левой ветви
		{
			this->nodeCameFrom = this->current;
			this->current = this->current->previous;
		} while (this->current && this->nodeCameFrom == this->current->right);
	}
	else
	{
		// В случае наличия правой ветви, итератор перемещается вправо, а после до конечной ветви влево
		this->current = current->right;
		while (this->current->left) this->current = this->current->left;
	}
	return current->data;
}

template<typename Type>
Type& BinaryTree<Type>::Iterator::operator--(int value)
{
	// Если итератор установлен на null, то перемещаем его на самый правый элемент дерева
	if (current == nullptr)
	{
		current = nodeCameFrom;
		return current->data;
	}
	// От наличия левой ветви зависит дальнейший алгоритм
	if (!current->left)
	{
		do	// Цикл перемещает итератор вверх по дереву до тех, пор, пока не обнаружит
			// что поднялся по правой ветви
		{
			this->nodeCameFrom = this->current;
			this->current = this->current->previous;
		} while (this->current && this->nodeCameFrom == this->current->left);
	}
	else
	{
		// В случае наличия правой ветви, итератор перемещается влево, а после до конечной ветви вправо
		this->current = current->left;
		while (this->current->right) this->current = this->current->right;
	}
	return current->data;
}

// Оператор получения данных по итератору
template<typename Type>
Type& BinaryTree<Type>::Iterator::operator*()
{
	return this->current->data;
}

// Оператор не равно
template<typename Type>
bool BinaryTree<Type>::Iterator::operator!=(Iterator b)
{
	if (this->current != b.current) return true;
	else return false;
}

// Оператор равно
template<typename Type>
bool BinaryTree<Type>::Iterator::operator==(Iterator b)
{
	return !(*this != b);
}
 
// Добавить элемент в дерево по условию operationGreater
template<typename Type>
template<typename Predicat>
BinaryTree<Type>::template TreeNode* BinaryTree<Type>::PushByCondition(Type data, TreeNode* root, Predicat operationGreater, TreeNode* previous)
{
	if (root)
	{
		// Поиск места для вставки элемента
		if (operationGreater(data, root->data)) root->right = PushWithCustomCondition(data, root->right, operationGreater, root);
		else
		{
			root->left = PushWithCustomCondition(data, root->left, operationGreater, root);
		}
	}
	else
	{
		// Вставка элемента
		root = new TreeNode(&data);
		root->right = nullptr;
		root->left = nullptr;
		root->previous = previous;
	}
	return root;
}

// Внешнаяя функция добавления элемента в дерево, инкапсулирующая рекрсивные параметры
template<typename Type>
template<typename Predicat>
void BinaryTree<Type>::AddDataWithCondition(Type data, Predicat operationGreater)
{
	this->mainRoot = PushWithCustomCondition(data, this->mainRoot, operationGreater);
}