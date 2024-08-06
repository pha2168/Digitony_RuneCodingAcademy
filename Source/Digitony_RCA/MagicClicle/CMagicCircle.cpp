#include "CMagicCircle.h"
#include "CodeBlocks/CCodeBlockBase.h"
#include "Components/BoxComponent.h"

// Constructor
ACMagicCircle::ACMagicCircle()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and initialize components
    MagicCircleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagicCircleMeshComponent"));
    BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));

    // Set up component hierarchy
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

// Adds a code block to the magic circle
void ACMagicCircle::AddCodeBlock(ACCodeBlockBase* InCodeBlock)
{
    if (InCodeBlock == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("InCodeBlock is null"));
        return;
    }

    if (CodeBlocks.Num() >= CodeBlockArrayNum)
    {
        UE_LOG(LogTemp, Warning, TEXT("CodeBlock is full"));
        return;
    }

    // Create and populate FCodeBlockInfo struct
    FCodeBlockInfo NewBlockInfo;
    NewBlockInfo.CodeBlockType = InCodeBlock->GetCodeBlockType();
    NewBlockInfo.StaticMesh = InCodeBlock->GetStaticMesh();

    CodeBlocks.Add(NewBlockInfo);
    UpdateMagicCircle(); // This will call the blueprint implementation
}

// Removes the last code block from the magic circle
void ACMagicCircle::RemoveCodeBlock()
{
    if (CodeBlocks.Num() <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("CodeBlock is none"));
        return;
    }

    CodeBlocks.Pop();
    UpdateMagicCircle(); // This will call the blueprint implementation
}
