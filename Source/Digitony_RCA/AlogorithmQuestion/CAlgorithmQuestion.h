// CAlgorithmQuestion.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlogorithmQuestion/FAlgorithmQuestionMapData.h"
#include "MagicClicle/CMagicCircle.h"  // Include the MagicCircle header file
#include "CodeBlocks/ECodeBlockType.h"
#include "CodeBlocks/CCodeBlockBase.h"
#include "CAlgorithmQuestion.generated.h"

// Forward declarations to reduce dependencies
class UCScoreWidget;
class UStaticMesh;

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
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FDataTableRowHandle MapData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UStaticMesh> ObstacleBlock;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UStaticMesh> TransparentObstacleBlock;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UStaticMesh> StartBlock;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UStaticMesh> EndBlock;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UStaticMesh> CoinMesh;  // 코인 메쉬

    TArray<AStaticMeshActor*> CreatedCoins;  // 생성된 코인들을 저장할 배열

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Spacing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECodeBlockType CodeBlockType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    AActor* Luni;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    ACMagicCircle* MagicCircle; // ACMagicCircle object reference

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Algorithm")
    float TimerInterval = 1.0f;

    UPROPERTY(BlueprintReadOnly)
    FVector StartBlockLocation;

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
    void MoveLuni(ECodeBlockType InCodeBlockType);

    UFUNCTION(BlueprintCallable)
    void ExecuteCodeBlock();

private:
    int32 ID;
    int32 Width;
    int32 Height;
    int32 Depth;
    FString Map;

    TArray<AStaticMeshActor*> CreatedActors;

    FTimerHandle CodeBlockTimerHandle;
    int32 CurrentCodeBlockIndex;

private:
    UPROPERTY(EditAnywhere, Category = "Luni")
    FRotator InitialLuniRotation;

};
