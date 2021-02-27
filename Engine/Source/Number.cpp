#include "..\Include\Number.h"
#include "Text.h"

template<typename T>
Number<T>::Number(Desc * _desc)
{
	m_targetValue = _desc->targetValue;
}

template<typename T>
void Number<T>::Initialize()
{
}
template<typename T>
void Number<T>::Update()
{
	if (m_observeValue != *m_targetValue)
	{


	}

}

template<typename T>
void Number<T>::SetTargetValue(T _value)
{
}

template<typename T>
T Number<T>::GetTargetValue()
{
	return T();
}

template<typename T>
wstring Number<T>::PrintNumber()
{
	(*m_targetValue)
	return wstring();
}
