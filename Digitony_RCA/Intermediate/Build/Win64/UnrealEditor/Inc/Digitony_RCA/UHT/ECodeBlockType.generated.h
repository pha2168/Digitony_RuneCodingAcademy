// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CodeBlocks/ECodeBlockType.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef DIGITONY_RCA_ECodeBlockType_generated_h
#error "ECodeBlockType.generated.h already included, missing '#pragma once' in ECodeBlockType.h"
#endif
#define DIGITONY_RCA_ECodeBlockType_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_alice_Documents_GitHub_Digitony_seoyeon_Digitony_RCA_Source_Digitony_RCA_CodeBlocks_ECodeBlockType_h


#define FOREACH_ENUM_ECODEBLOCKTYPE(op) \
	op(ECodeBlockType::None) \
	op(ECodeBlockType::Forward) \
	op(ECodeBlockType::RightTurn) \
	op(ECodeBlockType::LeftTurn) \
	op(ECodeBlockType::Jump) \
	op(ECodeBlockType::Repetition) \
	op(ECodeBlockType::Number) 

enum class ECodeBlockType : uint8;
template<> struct TIsUEnumClass<ECodeBlockType> { enum { Value = true }; };
template<> DIGITONY_RCA_API UEnum* StaticEnum<ECodeBlockType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
