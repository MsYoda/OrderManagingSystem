#pragma once

// Шаблон класса сравнителя
template<typename T1, typename T2 = T1>
class Comparator
{
public:
    virtual bool operator()(T1* a, T2* b) = 0;
};