#include "CodeBlocks/CCodeBlockBase.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

ACCodeBlockBase::ACCodeBlockBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("GrabComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));


}

void ACCodeBlockBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCodeBlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

