// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Digitony_RCA/CodeBlocks/ECodeBlockType.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeECodeBlockType() {}

// Begin Cross Module References
DIGITONY_RCA_API UEnum* Z_Construct_UEnum_Digitony_RCA_ECodeBlockType();
UPackage* Z_Construct_UPackage__Script_Digitony_RCA();
// End Cross Module References

// Begin Enum ECodeBlockType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECodeBlockType;
static UEnum* ECodeBlockType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ECodeBlockType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ECodeBlockType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Digitony_RCA_ECodeBlockType, (UObject*)Z_Construct_UPackage__Script_Digitony_RCA(), TEXT("ECodeBlockType"));
	}
	return Z_Registration_Info_UEnum_ECodeBlockType.OuterSingleton;
}
template<> DIGITONY_RCA_API UEnum* StaticEnum<ECodeBlockType>()
{
	return ECodeBlockType_StaticEnum();
}
struct Z_Construct_UEnum_Digitony_RCA_ECodeBlockType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Forward.DisplayName", "Forward" },
		{ "Forward.Name", "ECodeBlockType::Forward" },
		{ "Jump.DisplayName", "Jump" },
		{ "Jump.Name", "ECodeBlockType::Jump" },
		{ "LeftTurn.DisplayName", "LeftTurn" },
		{ "LeftTurn.Name", "ECodeBlockType::LeftTurn" },
		{ "ModuleRelativePath", "CodeBlocks/ECodeBlockType.h" },
		{ "None.DisplayName", "None" },
		{ "None.Name", "ECodeBlockType::None" },
		{ "Number.DisplayName", "Number" },
		{ "Number.Name", "ECodeBlockType::Number" },
		{ "Repetition.DisplayName", "Repetition" },
		{ "Repetition.Name", "ECodeBlockType::Repetition" },
		{ "RightTurn.DisplayName", "RightTurn" },
		{ "RightTurn.Name", "ECodeBlockType::RightTurn" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ECodeBlockType::None", (int64)ECodeBlockType::None },
		{ "ECodeBlockType::Forward", (int64)ECodeBlockType::Forward },
		{ "ECodeBlockType::RightTurn", (int64)ECodeBlockType::RightTurn },
		{ "ECodeBlockType::LeftTurn", (int64)ECodeBlockType::LeftTurn },
		{ "ECodeBlockType::Jump", (int64)ECodeBlockType::Jump },
		{ "ECodeBlockType::Repetition", (int64)ECodeBlockType::Repetition },
		{ "ECodeBlockType::Number", (int64)ECodeBlockType::Number },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Digitony_RCA_ECodeBlockType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Digitony_RCA,
	nullptr,
	"ECodeBlockType",
	"ECodeBlockType",
	Z_Construct_UEnum_Digitony_RCA_ECodeBlockType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Digitony_RCA_ECodeBlockType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Digitony_RCA_ECodeBlockType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Digitony_RCA_ECodeBlockType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Digitony_RCA_ECodeBlockType()
{
	if (!Z_Registration_Info_UEnum_ECodeBlockType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECodeBlockType.InnerSingleton, Z_Construct_UEnum_Digitony_RCA_ECodeBlockType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ECodeBlockType.InnerSingleton;
}
// End Enum ECodeBlockType

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_alice_Documents_GitHub_Digitony_seoyeon_Digitony_RCA_Source_Digitony_RCA_CodeBlocks_ECodeBlockType_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ECodeBlockType_StaticEnum, TEXT("ECodeBlockType"), &Z_Registration_Info_UEnum_ECodeBlockType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3122528773U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alice_Documents_GitHub_Digitony_seoyeon_Digitony_RCA_Source_Digitony_RCA_CodeBlocks_ECodeBlockType_h_1164670145(TEXT("/Script/Digitony_RCA"),
	nullptr, 0,
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_alice_Documents_GitHub_Digitony_seoyeon_Digitony_RCA_Source_Digitony_RCA_CodeBlocks_ECodeBlockType_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alice_Documents_GitHub_Digitony_seoyeon_Digitony_RCA_Source_Digitony_RCA_CodeBlocks_ECodeBlockType_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
