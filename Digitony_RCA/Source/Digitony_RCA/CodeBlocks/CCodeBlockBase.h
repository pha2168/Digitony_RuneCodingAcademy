#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ECodeBlockType.h"
#include "CCodeBlockBase.generated.h"

UCLASS()
class DIGITONY_RCA_API ACCodeBlockBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCodeBlockBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<class UPhysicsHandleComponent> PhysicsHandle;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	ECodeBlockType CodeBlockType;

};
