#include "CMagicCircle.h"
#include "CodeBlocks/CCodeBlockBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

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

    // Initialize scoring thresholds (Default values, can be adjusted in the Blueprint)
    PerfectThreshold = 3;
    GoodThreshold = 5;
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

// Evaluate the score based on the number of code blocks and spawn the appropriate actor
void ACMagicCircle::EvaluateScore()
{
    int32 CodeBlockCount = CodeBlocks.Num();

    TSubclassOf<AActor> ActorToSpawn = nullptr;

    if (CodeBlockCount <= PerfectThreshold)
    {
        UE_LOG(LogTemp, Log, TEXT("Perfect Score! CodeBlockCount = %d"), CodeBlockCount);
        ActorToSpawn = PerfectActorClass;
    }
    else if (CodeBlockCount <= GoodThreshold)
    {
        UE_LOG(LogTemp, Log, TEXT("Good Score! CodeBlockCount = %d"), CodeBlockCount);
        ActorToSpawn = GoodActorClass;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Bad Score! CodeBlockCount = %d"), CodeBlockCount);
        ActorToSpawn = BadActorClass;
    }

    if (ActorToSpawn)
    {
        FVector SpawnLocation = GetActorLocation() + FVector(200, 0, 0); // Set the spawn location relative to the MagicCircle
        FRotator SpawnRotation = FRotator::ZeroRotator; // Default rotation
        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, SpawnRotation);
        if (SpawnedActor)
        {
            UE_LOG(LogTemp, Log, TEXT("Actor spawned successfully"));
        }
    }
}
