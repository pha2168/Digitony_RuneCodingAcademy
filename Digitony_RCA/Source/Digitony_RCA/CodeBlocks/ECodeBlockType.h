#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ECodeBlockType : uint8
{
	None			UMETA(DisplayName = "None"),
	Forward			UMETA(DisplayName = "Forward"),
	RightTurn		UMETA(DisplayName = "RightTurn"),
	LeftTurn		UMETA(DisplayName = "LeftTurn"),
	Jump			UMETA(DisplayName = "Jump"),
	Repetition		UMETA(DisplayName = "Repetition"),
	Number			UMETA(DisplayName = "Number"),
};