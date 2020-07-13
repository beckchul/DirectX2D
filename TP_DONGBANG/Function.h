#pragma once

template<class T>
static inline void Safe_Delete(T& rData)
{
	if(rData)
	{
		delete rData;
		rData = NULL;
	}
}