#pragma once

#include "CoreMinimal.h"

template<typename T>
class DIGITONY_RCA_API C3DArray
{
public:
	C3DArray(int32 InWidth, int32 InHeight, int32 InDepth)
		: Width(InWidth), Height(InHeight), Depth(InDepth)
	{
		Array.SetNum(Width * Height * Depth);
	}

public:
	FORCEINLINE int32 GetWidth() const { return Width; }
	FORCEINLINE int32 GetHeight() const { return Height; }
	FORCEINLINE int32 GetDepth() const { return Depth; }

	const T& At(int32 X, int32 Y, int32 Z) const
	{
		if (!IsValidIndex(X, Y, Z))
		{
			return nullptr;
		}

		return Array[GetIndex(X, Y, Z)];
	}

private:
	bool IsValidIndex(int32 X, int32 Y, int32 Z) const
	{
		return X >= 0 && X < Width && Y >= 0 && Y < Height && Z >= 0 && Z < Depth;
	}

	int32 GetIndex(int32 X, int32 Y, int32 Z) const
	{
		return X + (Y * Width) + (Z * Width * Height);
	}


private:
	int32 Width;
	int32 Height;
	int32 Depth;

	TArray<T> Array;
};
