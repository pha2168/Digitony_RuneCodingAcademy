#include "MagicClicle/CMagicCircle.h"
#include "Components/BoxComponent.h"
#include "CodeBlocks/CCodeBlockBase.h"


ACMagicCircle::ACMagicCircle()
{
	PrimaryActorTick.bCanEverTick = true;

	MagicCircleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagicCircleMeshComponent"));
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));

	SetRootComponent(MagicCircleMeshComponent);
	BoxCollisionComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ACMagicCircle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACMagicCircle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACMagicCircle::AddCodeBlock(ACCodeBlockBase* InCodeBlock)
{
	if (InCodeBlock == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InCodeBlock is null"));
		return;
	}

	// 코드 블록이 16개 이상 입력되지 못하게 예외 처리
	if (CodeBlocks.Num() >= CodeBlockArrayNum)
	{
		UE_LOG(LogTemp, Warning, TEXT("CodeBlock is full"));
		return;
	}

	CodeBlocks.Add(InCodeBlock);

	UpdateMagicCircle();
}

void ACMagicCircle::RomoveCodeBlock()
{
	// 코드 블록이 16개 이상 입력되지 못하게 예외 처리
	if (0 >= CodeBlocks.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("CodeBlock is none"));
		return;
	}

	CodeBlocks.Pop();

	UpdateMagicCircle();
}

