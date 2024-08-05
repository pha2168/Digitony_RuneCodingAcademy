#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlogorithmQuestion/FAlgorithmQuestionMapData.h"
#include "MagicClicle/CMagicCircle.h"
#include "CodeBlocks/ECodeBlockType.h"
#include "CAlgorithmQuestion.generated.h"


UCLASS()
class DIGITONY_RCA_API ACAlgorithmQuestion : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAlgorithmQuestion();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDataTableRowHandle MapData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> ObstacleBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> StartBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> EndBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Spacing;

public:
	UFUNCTION(BlueprintCallable)
	void LoadMapData();

	UFUNCTION(BlueprintCallable)
	void CreateMap();

	UFUNCTION(BlueprintCallable)
	void StartMagic();
	
private:
	int32 ID;
	int32 Width;
	int32 Height;
	int32 Depth;
	FString Map;
};
