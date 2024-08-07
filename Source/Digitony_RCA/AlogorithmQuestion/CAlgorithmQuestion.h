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
	ECodeBlockType CodeBlockType; // ECodeBlockType �Ӽ� �߰�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	AActor* Luni; // Luni ������Ʈ ���� �߰�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ACMagicCircle* MagicCircle; // MagicCircle ������Ʈ ���� �߰�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Algorithm")
	float TimerInterval = 1.0f; // �⺻���� 1��

	UPROPERTY(BlueprintReadOnly)
	FVector StartBlockLocation; // �������Ʈ���� ���� �� �ֵ��� ����

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
	void MoveLuni(ECodeBlockType InCodeBlockType); // Luni �̵� �Լ�

	UFUNCTION(BlueprintCallable)
	void ExecuteCodeBlock(); // �ڵ� ��� ����� �Լ�


private:
	int32 ID;
	int32 Width;
	int32 Height;
	int32 Depth;
	FString Map;

	TArray<AStaticMeshActor*> CreatedActors; // ������ ��ϵ��� ������ �迭

	FTimerHandle CodeBlockTimerHandle;
	int32 CurrentCodeBlockIndex;
};
