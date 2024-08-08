#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECodeBlockType : uint8
{
	None			UMETA(DisplayName = "None"),
	Forward			UMETA(DisplayName = "Forward"),
	RightTurn		UMETA(DisplayName = "RightTurn"),
	LeftTurn		UMETA(DisplayName = "LeftTurn"),
	Jump			UMETA(DisplayName = "Jump"),
	Repetition		UMETA(DisplayName = "Repetition"),
	Number_2			UMETA(DisplayName = "Number2"),
	Number_3			UMETA(DisplayName = "Number3"),
	Number_4			UMETA(DisplayName = "Number4")
};
