#pragma once
#include "Shapes.h"
using namespace syl_shapes;

template <typename T>
class Factory
{
public:
	Factory();
	~Factory();
	template <class U>
	T* create();
	template <class Rectangle>
	T* create(int x, int y, int height, int width);
};

template <typename T>
Factory<T>::Factory()
{
}

template <typename T>
Factory<T>::~Factory()
{
}

template <typename T>
template <class U>
T* Factory<T>::create()
{
	return new U;
}

template <typename T>
template <class Rectangle>
T* Factory<T>::create(int x, int y, int height, int width)
{
	return new Rectangle(std::make_pair(x, y), std::make_pair(height, width));
}