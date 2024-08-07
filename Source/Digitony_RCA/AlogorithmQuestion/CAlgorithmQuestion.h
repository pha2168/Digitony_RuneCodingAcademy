#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlogorithmQuestion/FAlgorithmQuestionMapData.h"
#include "MagicClicle/CMagicCircle.h"
#include "CodeBlocks/ECodeBlockType.h"
#include "CodeBlocks/CCodeBlockBase.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECodeBlockType CodeBlockType; // ECodeBlockType 속성 추가

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	AActor* Luni; // Luni 오브젝트 참조 추가

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ACMagicCircle* MagicCircle; // MagicCircle 오브젝트 참조 추가

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Algorithm")
	float TimerInterval = 1.0f; // 기본값은 1초

	UPROPERTY(BlueprintReadOnly)
	FVector StartBlockLocation; // 블루프린트에서 읽을 수 있도록 설정

public:
	UFUNCTION(BlueprintCallable)
	void LoadMapData();

	UFUNCTION(BlueprintCallable)
	void CreateMap();

	UFUNCTION(BlueprintCallable)
	void StartMagic();

	UFUNCTION(BlueprintImplementableEvent)
	void FinishMagic();

	UFUNCTION(BlueprintCallable)
	void ClearMap();

	UFUNCTION(BlueprintCallable)
	void MoveLuni(ECodeBlockType InCodeBlockType); // Luni 이동 함수

	UFUNCTION(BlueprintCallable)
	void ExecuteCodeBlock(); // 코드 블록 실행용 함수


private:
	int32 ID;
	int32 Width;
	int32 Height;
	int32 Depth;
	FString Map;

	TArray<AStaticMeshActor*> CreatedActors; // 생성된 블록들을 저장할 배열

	FTimerHandle CodeBlockTimerHandle;
	int32 CurrentCodeBlockIndex;
};
