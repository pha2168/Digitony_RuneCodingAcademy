#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeBlocks/ECodeBlockType.h"
#include "CodeBlocks/CCodeBlockBase.h"
#include "CMagicCircle.generated.h"

USTRUCT(BlueprintType)
struct FCodeBlockInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ECodeBlockType CodeBlockType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<UStaticMesh> StaticMesh;

    FCodeBlockInfo()
        : CodeBlockType(ECodeBlockType::None), StaticMesh(nullptr)
    {}
};

UCLASS()
class DIGITONY_RCA_API ACMagicCircle : public AActor
{
    GENERATED_BODY()

public:
    ACMagicCircle();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> MagicCircleMeshComponent;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    TObjectPtr<class UBoxComponent> BoxCollisionComponent;

public:
    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
    TArray<FCodeBlockInfo> CodeBlocks;

public:
    UFUNCTION(BlueprintCallable)
    void AddCodeBlock(ACCodeBlockBase* InCodeBlock);

    UFUNCTION(BlueprintCallable)
    void RemoveCodeBlock();

    UFUNCTION(BlueprintImplementableEvent)
    void UpdateMagicCircle();

private:
    int CodeBlockArrayNum = 16;
};
