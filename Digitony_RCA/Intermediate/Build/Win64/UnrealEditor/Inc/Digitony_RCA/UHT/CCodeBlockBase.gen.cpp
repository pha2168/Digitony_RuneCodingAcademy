// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Digitony_RCA/CodeBlocks/CCodeBlockBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCCodeBlockBase() {}

// Begin Cross Module References
DIGITONY_RCA_API UClass* Z_Construct_UClass_ACCodeBlockBase();
DIGITONY_RCA_API UClass* Z_Construct_UClass_ACCodeBlockBase_NoRegister();
DIGITONY_RCA_API UEnum* Z_Construct_UEnum_Digitony_RCA_ECodeBlockType();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UPhysicsHandleComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_Digitony_RCA();
// End Cross Module References

// Begin Class ACCodeBlockBase
void ACCodeBlockBase::StaticRegisterNativesACCodeBlockBase()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACCodeBlockBase);
UClass* Z_Construct_UClass_ACCodeBlockBase_NoRegister()
{
	return ACCodeBlockBase::StaticClass();
}
struct Z_Construct_UClass_ACCodeBlockBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "CodeBlocks/CCodeBlockBase.h" },
		{ "ModuleRelativePath", "CodeBlocks/CCodeBlockBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PhysicsHandle_MetaData[] = {
		{ "Category", "CCodeBlockBase" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CodeBlocks/CCodeBlockBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshComponent_MetaData[] = {
		{ "Category", "CCodeBlockBase" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CodeBlocks/CCodeBlockBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CodeBlockType_MetaData[] = {
		{ "Category", "CCodeBlockBase" },
		{ "ModuleRelativePath", "CodeBlocks/CCodeBlockBase.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PhysicsHandle;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StaticMeshComponent;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CodeBlockType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CodeBlockType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACCodeBlockBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACCodeBlockBase_Statics::NewProp_PhysicsHandle = { "PhysicsHandle", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACCodeBlockBase, PhysicsHandle), Z_Construct_UClass_UPhysicsHandleComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PhysicsHandle_MetaData), NewProp_PhysicsHandle_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACCodeBlockBase_Statics::NewProp_StaticMeshComponent = { "StaticMeshComponent", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACCodeBlockBase, StaticMeshComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMeshComponent_MetaData), NewProp_StaticMeshComponent_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_ACCodeBlockBase_Statics::NewProp_CodeBlockType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ACCodeBlockBase_Statics::NewProp_CodeBlockType = { "CodeBlockType", nullptr, (EPropertyFlags)0x0020080000010015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACCodeBlockBase, CodeBlockType), Z_Construct_UEnum_Digitony_RCA_ECodeBlockType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CodeBlockType_MetaData), NewProp_CodeBlockType_MetaData) }; // 3122528773
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACCodeBlockBase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACCodeBlockBase_Statics::NewProp_PhysicsHandle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACCodeBlockBase_Statics::NewProp_StaticMeshComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACCodeBlockBase_Statics::NewProp_CodeBlockType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACCodeBlockBase_Statics::NewProp_CodeBlockType,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACCodeBlockBase_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ACCodeBlockBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Digitony_RCA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACCodeBlockBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ACCodeBlockBase_Statics::ClassParams = {
	&ACCodeBlockBase::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ACCodeBlockBase_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ACCodeBlockBase_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACCodeBlockBase_Statics::Class_MetaDataParams), Z_Construct_UClass_ACCodeBlockBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ACCodeBlockBase()
{
	if (!Z_Registration_Info_UClass_ACCodeBlockBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACCodeBlockBase.OuterSingleton, Z_Construct_UClass_ACCodeBlockBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ACCodeBlockBase.OuterSingleton;
}
template<> DIGITONY_RCA_API UClass* StaticClass<ACCodeBlockBase>()
{
	return ACCodeBlockBase::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ACCodeBlockBase);
ACCodeBlockBase::~ACCodeBlockBase() {}
// End Class ACCodeBlockBase

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_alice_Documents_GitHub_Digitony_seoyeon_Digitony_RCA_Source_Digitony_RCA_CodeBlocks_CCodeBlockBase_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACCodeBlockBase, ACCodeBlockBase::StaticClass, TEXT("ACCodeBlockBase"), &Z_Registration_Info_UClass_ACCodeBlockBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACCodeBlockBase), 841511966U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_alice_Documents_GitHub_Digitony_seoyeon_Digitony_RCA_Source_Digitony_RCA_CodeBlocks_CCodeBlockBase_h_494030889(TEXT("/Script/Digitony_RCA"),
	Z_CompiledInDeferFile_FID_Users_alice_Documents_GitHub_Digitony_seoyeon_Digitony_RCA_Source_Digitony_RCA_CodeBlocks_CCodeBlockBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_alice_Documents_GitHub_Digitony_seoyeon_Digitony_RCA_Source_Digitony_RCA_CodeBlocks_CCodeBlockBase_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
