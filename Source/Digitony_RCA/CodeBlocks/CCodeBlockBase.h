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

    UFUNCTION(BlueprintCallable, Category = "CodeBlock")
    ECodeBlockType GetCodeBlockType() const { return CodeBlockType; }

    UFUNCTION(BlueprintCallable, Category = "CodeBlock")
    UStaticMesh* GetStaticMesh() const { return StaticMeshComponent->GetStaticMesh(); }

protected:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    TObjectPtr<class UPhysicsHandleComponent> PhysicsHandle;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
    ECodeBlockType CodeBlockType;
};
