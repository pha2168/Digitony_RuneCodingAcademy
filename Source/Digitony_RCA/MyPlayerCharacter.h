#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayerCharacter.generated.h"

UCLASS()
class DIGITONY_RCA_API AMyPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyPlayerCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // 이동
    void MoveForward(float Value);
    void MoveRight(float Value);
    void MoveBack(float Value);
    void MoveLeft(float Value);

    // 시선 조정
    void LookUp(float Value);
    void Turn(float Value);

    // 그랩
    void Grab();
    void Release();

private:
    UPROPERTY(VisibleAnywhere)
    class UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere)
    class USphereComponent* GrabSphere;

    UPROPERTY()
    AActor* GrabbedActor;

    UPROPERTY(EditAnywhere)
    float GrabRange = 200.0f;
};
