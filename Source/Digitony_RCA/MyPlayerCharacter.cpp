#include "MyPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

AMyPlayerCharacter::AMyPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // 카메라 컴포넌트 설정
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(GetRootComponent());
    CameraComponent->bUsePawnControlRotation = true;

    // 그랩 스피어 컴포넌트 설정
    GrabSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GrabSphere"));
    GrabSphere->SetupAttachment(CameraComponent);
    GrabSphere->SetSphereRadius(GrabRange);
    GrabSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMyPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AMyPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GrabbedActor)
    {
        FVector GrabLocation = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * GrabRange;
        GrabbedActor->SetActorLocation(GrabLocation);
    }
}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 이동 바인딩
    PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("MoveBack", this, &AMyPlayerCharacter::MoveBack);
    PlayerInputComponent->BindAxis("MoveLeft", this, &AMyPlayerCharacter::MoveLeft);

    // 시선 조정 바인딩
    PlayerInputComponent->BindAxis("LookUp", this, &AMyPlayerCharacter::LookUp);
    PlayerInputComponent->BindAxis("Turn", this, &AMyPlayerCharacter::Turn);

    // 그랩 기능 바인딩
    PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &AMyPlayerCharacter::Grab);
    PlayerInputComponent->BindAction("Grab", IE_Released, this, &AMyPlayerCharacter::Release);
}

void AMyPlayerCharacter::MoveForward(float Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void AMyPlayerCharacter::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void AMyPlayerCharacter::MoveBack(float Value)
{
    AddMovementInput(-GetActorForwardVector(), Value);
}

void AMyPlayerCharacter::MoveLeft(float Value)
{
    AddMovementInput(-GetActorRightVector(), Value);
}

void AMyPlayerCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void AMyPlayerCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void AMyPlayerCharacter::Grab()
{
    if (GrabbedActor == nullptr)
    {
        FVector Start = CameraComponent->GetComponentLocation();
        FVector End = Start + CameraComponent->GetForwardVector() * GrabRange;

        FHitResult HitResult;
        FCollisionQueryParams CollisionParams;
        GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

        if (HitResult.GetActor() && HitResult.GetActor()->FindComponentByClass<UPrimitiveComponent>())
        {
            GrabbedActor = HitResult.GetActor();
        }
    }
}

void AMyPlayerCharacter::Release()
{
    if (GrabbedActor)
    {
        GrabbedActor = nullptr;
    }
}
