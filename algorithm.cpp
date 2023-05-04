#pragma once
#include "algorithm.h"

template<typename Iterator, typename Predicat>
inline Iterator container::find_if(Iterator begin, Iterator end, Predicat compare)
{
	for (; begin != end; begin++)
	{
		if (compare(*begin))
		{
			return begin;
		}
	}
	return Iterator(nullptr);
}

// Пересортировка дерева в соответствии с заданной в предикате операцией >
template<typename Tree, typename Iterator, typename Predicat>
Tree container::sort_tree_by_condition(Iterator begin, Iterator end, Predicat compare)
{
	Tree tree;
	for (; begin != end; begin++)
	{
		tree.PushByCondition(*begin, compare);
	}
	return tree;
}

template<typename Tree, typename Iterator, typename Predicat>
Tree container::find_all_if(Iterator begin, Iterator end, Predicat compare)
{
	Tree tree;
	for (; begin != end; begin++)
	{
		if (compare(*begin))
		{
			tree.AddData(*begin);
		}
	}
	return tree;
}

template<typename Iterator, typename Predicat>
int container::count_if(Iterator begin, Iterator end, Predicat compare)
{
	int num = 0;
	for (; begin != end; begin++)
	{
		if (compare(*begin)) num++;
	}
	return num;
}

template<typename Iterator>
Iterator container::find_max(Iterator begin, Iterator end)
{
	Iterator max = begin;
	for (; begin != end; begin++)
	{
		if (*begin > *max) max = begin;
	}
	return max;
}

template<typename Iterator, typename Predicat>
Iterator container::find_max(Iterator begin, Iterator end, Predicat operationGreater)
{
	Iterator max = begin;
	for (; begin != end; begin++)
	{
		if (operationGreater(*begin, *max)) max = begin;
	}
	return max;
}

template<typename Iterator>
Iterator container::find_min(Iterator begin, Iterator end)
{
	Iterator min = begin;
	for (; begin != end; begin++)
	{
		if (*begin < *min) min = begin;
	}
	return min;
}

template<typename Iterator, typename Predicat>
Iterator container::find_min(Iterator begin, Iterator end, Predicat operationLesser)
{
	Iterator min = begin;
	for (; begin != end; begin++)
	{
		if (operationLesser(*begin, *min)) min = begin;
	}
	return min;
}

template<typename Iterator, typename Predicat>
void container::for_each(Iterator begin, Iterator end, Predicat operation)
{
	for (; begin != end; begin++)
	{
		operation(*begin);
	}
}


