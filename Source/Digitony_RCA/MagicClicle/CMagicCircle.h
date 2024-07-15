#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMagicCircle.generated.h"

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

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TArray<TObjectPtr<class ACCodeBlockBase>> CodeBlocks;

public:
	UFUNCTION(BlueprintCallable)
	void AddCodeBlock(ACCodeBlockBase* InCodeBlock);

	UFUNCTION(BlueprintCallable)
	void RomoveCodeBlock();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateMagicCircle();

private:
	int CodeBlockArrayNum = 16;
};
