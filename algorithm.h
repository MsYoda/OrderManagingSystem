#pragma once
#include "templates//BinaryTree.cpp"

namespace container
{
	// Поиск по условию, заданному в comapre
	template<typename Iterator, typename Predicat>
	Iterator find_if(Iterator begin, Iterator end, Predicat compare);

	// Пересортровка дерева по условию, зданному в compare
	template<typename Tree, typename Iterator, typename Predicat>
	Tree sort_tree_by_condition(Iterator begin, Iterator end, Predicat compare);

	// Поиск всех элементов, удовлетворяющих условию compare
	template<typename Tree, typename Iterator, typename Predicat>
	Tree find_all_if(Iterator begin, Iterator end, Predicat compare);

	// Подсчитать число элементов, удовлетворяющих условию compare
	template<typename Iterator, typename Predicat>
	int count_if(Iterator begin, Iterator end, Predicat compare);

	// Найти максимальное значение
	template<typename Iterator>
	Iterator find_max(Iterator begin, Iterator end);

	// Найти максимальное значение
	template<typename Iterator, typename Predicat>
	Iterator find_max(Iterator begin, Iterator end, Predicat operationGreater);

	// Найти минимальное значение
	template<typename Iterator>
	Iterator find_min(Iterator begin, Iterator end);

	// Найти минимальное значение
	template<typename Iterator, typename Predicat>
	Iterator find_min(Iterator begin, Iterator end, Predicat operationLesser);

	// Применить к каждому эленменту функцию operation
	template<typename Iterator, typename Predicat>
	void for_each(Iterator begin, Iterator end, Predicat operation);
}


