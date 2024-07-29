#include "AlogorithmQuestion/CAlgorithmQuestion.h"


ACAlgorithmQuestion::ACAlgorithmQuestion()
{
	PrimaryActorTick.bCanEverTick = true;

}


void ACAlgorithmQuestion::BeginPlay()
{
	Super::BeginPlay();

	
}


void ACAlgorithmQuestion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACAlgorithmQuestion::LoadMapData()
{
	
}

void ACAlgorithmQuestion::CreateMap()
{
    int32 MapSize = Width * Height * Depth;

    for (int32 i = 0; i < MapSize; i++)
    {
        FVector Position;
        Position.X = (i % Width) * 100.0f;
        Position.Y = ((i / Width) % Height) * 100.0f;
        Position.Z = (i / (Width * Height)) * 100.0f; 

        switch (Map[i])
        {
        // 0 일경우 빈 공간
        case 0:
            UE_LOG(LogTemp, Warning, TEXT("void"));
            break;

        // 1 일경우 장애물 생성
        case 1:
            if (ObstacleBlock)
            {
                UStaticMeshComponent* NewObstacle = NewObject<UStaticMeshComponent>(this);
                if (NewObstacle)
                {
                    NewObstacle->SetStaticMesh(ObstacleBlock);
                    NewObstacle->SetWorldLocation(Position);
                    NewObstacle->RegisterComponent();
                    NewObstacle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
                    UE_LOG(LogTemp, Warning, TEXT("Obstacle"));
                }
            }
            break;

        // 2일 경우 시작지점
        case 2:
             if (StartBlock)
            {
                UStaticMeshComponent* NewStart = NewObject<UStaticMeshComponent>(this);
                if (NewStart)
                {
                    NewStart->SetStaticMesh(StartBlock);
                    NewStart->SetWorldLocation(Position);
                    NewStart->RegisterComponent();
                    NewStart->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
                }
            }
            break;

        // 3일 경우 도착 지점
        case 3:
            if (EndBlock)
            {
                UStaticMeshComponent* NewEnd = NewObject<UStaticMeshComponent>(this);
                if (NewEnd)
                {
                    NewEnd->SetStaticMesh(EndBlock);
                    NewEnd->SetWorldLocation(Position);
                    NewEnd->RegisterComponent();
                    NewEnd->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
                }
            }
            break;

        default:
            UE_LOG(LogTemp, Warning, TEXT("Invalid data format"));
            break;
        }
    }
}

