#pragma once

#include "CoreMinimal.h"

template <typename ElementType>
class TArray2D 
{
private:
	int SizeX = 0;
	int SizeY = 0;
	TArray<ElementType> InnerArray;
	
public:
	void Init(const ElementType& element, int sizeX, int sizeY)
	{
		SizeX = sizeX;
		SizeY = sizeY;
		InnerArray.Init(element, sizeX * sizeY);
	}

	FORCEINLINE ElementType& GetElement(const int x, const int y)
	{
		return InnerArray[(x * SizeY) + y];
	}

	FORCEINLINE void SetElement(const int x, const int y, const ElementType& item)
	{
		InnerArray[(x * SizeY) + y] = item;
	}

	void ForEachElement(void (*Func)(const int x, const int y, const ElementType& item))
	{
		int i = 0;
		for (int y = 0; y < SizeY; y++)
		{
			for (int x = 0; x < SizeX; x++)
			{
				Func(x, y, InnerArray[i]);
				i++;
			}
		}
	}
};
