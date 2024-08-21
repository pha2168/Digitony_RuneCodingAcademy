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
        // 플레이어 컨트롤러를 가져오기
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController && PlayerController->GetPawn())
        {
            // 플레이어의 위치와 방향 가져오기
            FVector PlayerLocation;
            FRotator PlayerRotation;
            PlayerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

            // 플레이어 앞 일정 거리 떨어진 위치 계산
            FVector SpawnLocation = PlayerLocation + PlayerRotation.Vector() * 200.0f; // 플레이어의 눈앞 200 유닛 거리
            FRotator SpawnRotation = PlayerRotation; // 플레이어가 바라보는 방향으로 회전 설정

            // 객체 소환
            AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, SpawnRotation);
            if (SpawnedActor)
            {
                UE_LOG(LogTemp, Log, TEXT("Actor spawned successfully in front of the player"));
            }
        }
    }
}

