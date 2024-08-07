#pragma once

#include "CoreMinimal.h"
#include "FAlgorithmQuestionMapData.generated.h"


USTRUCT(BlueprintType)
struct DIGITONY_RCA_API FAlgorithmQuestionMapData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapData")
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapData")
	int32 Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapData")
	int32 Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapData")
	int32 Depth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapData")
	FString Map;
};
