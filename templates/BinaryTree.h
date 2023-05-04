#pragma once
#include <iostream>
#include "Comparator.h"

template <typename Type>
class BinaryTree
{
private:
	class TreeNode  // Вложенный класс элемента дерева
	{
	public:
		TreeNode(Type* data = nullptr);
		~TreeNode();

		Type data;         // Информация в дереве
		TreeNode* left;    // Сслыка на левый узел
		TreeNode* right;   // Ссылка на правый узел
		TreeNode* previous; // Ссылка на предыдущий узел

	};

	TreeNode* mainRoot;     // Ссылка на корень

	TreeNode* PushNode(Type data, TreeNode* root, TreeNode* previous = nullptr);    // Добавить элементв дерево

	// Рекурсивная функция добавления элемента в дерево с операцией больше определённой в operationGreater
	template <typename Predicat>
	TreeNode* PushByCondition(Type data, TreeNode* root, Predicat operationGreater, TreeNode* previous = nullptr);
	
	TreeNode* GetMinInTree(TreeNode* root);                                         // Найти минимальный узел в дереве
	void ClrTree(TreeNode* node);                                                   // Очистить дерево
	TreeNode* Copy(TreeNode* node, TreeNode* other, TreeNode* previous = nullptr);  // Скопировать дерево
	TreeNode* RemoveData(TreeNode* node, Type* data);			// Удалить узел с информацией == data

public:
	// Конструкторы
	BinaryTree();               
	BinaryTree(Type* data);
	BinaryTree(const BinaryTree<Type>& other);

	// Деструктор
	~BinaryTree();

	void AddData(Type data);            // Внешний метод добавления элемента в дерево

	// Добавление элемента в дерево, где операция > определена в operationGreater
	template<typename Predicat>
	void AddDataWithCondition(Type data, Predicat operationGreater);

	void ClrTree();                     // Внешний метод очистки дерева

	void RemoveData(Type* data);
	//void RemoveWhere(Type& searchMask, Comparator<Type>* comparator = nullptr);                 // Удалить узел дерева по филльтру

   
	Type* GetRootData();                // Вернуть значение корня
	TreeNode* GetRoot();                // Вернуть корень

	BinaryTree<Type>& operator= (const BinaryTree<Type>& other);    

	class Iterator
	{
		TreeNode* current;          // Текущий узел
		TreeNode* nodeCameFrom;     // Узел с которого пришёл итератор

	public:
		Iterator();                 // Конструктор
		Iterator(TreeNode* current, TreeNode* cameFrom = nullptr);  // Конструктор для функций Begin и End

		Type& operator++(int value);   // Оператор передвижения вперёд
		Type& operator--(int value);   // Оператор передвижения назад
		Type& operator*();             // Оператор получения данных по итератору

		bool operator!=(Iterator b);    // Оператор не равно
		bool operator==(Iterator b);    // Оператор равно
	};

	Iterator Begin();                   // Вернуть итератор на начало дерева
	Iterator End();                     // Вернуть итератор на конец дерева

};

