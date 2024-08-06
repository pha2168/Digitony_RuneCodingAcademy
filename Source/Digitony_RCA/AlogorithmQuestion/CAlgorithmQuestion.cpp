#include "AlogorithmQuestion/CAlgorithmQuestion.h"
#include "Engine/StaticMeshActor.h"
#include "TimerManager.h"

// 생성자
ACAlgorithmQuestion::ACAlgorithmQuestion()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentCodeBlockIndex = 0; // 인덱스 초기화
}

// Begin Play
void ACAlgorithmQuestion::BeginPlay()
{
    Super::BeginPlay();
    LoadMapData();
}

// Tick 함수
void ACAlgorithmQuestion::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Load Map Data
void ACAlgorithmQuestion::LoadMapData()
{
    if (!MapData.DataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("MapData DataTable이 설정되지 않았습니다."));
        return;
    }

    FAlgorithmQuestionMapData* Row = MapData.DataTable->FindRow<FAlgorithmQuestionMapData>(MapData.RowName, TEXT(""));

    if (!Row)
    {
        UE_LOG(LogTemp, Warning, TEXT("MapData 행을 찾을 수 없습니다."));
        return;
    }

    ID = Row->ID;
    Width = Row->Width;
    Height = Row->Height;
    Depth = Row->Depth;
    Map = Row->Map;

    CreateMap();
}

// Create Map
void ACAlgorithmQuestion::CreateMap()
{
    StartBlockLocation = FVector::ZeroVector; // 시작 위치 초기화

    for (int32 Z = 0; Z < Depth; Z++)
    {
        for (int32 Y = 0; Y < Height; Y++)
        {
            for (int32 X = 0; X < Width; X++)
            {
                FVector ActorLocation = this->GetActorLocation();
                FVector NewLocation = FVector(ActorLocation.X + (X * Spacing), ActorLocation.Y + (Y * Spacing), ActorLocation.Z + (Z * Spacing));
                FRotator NewRotator = this->GetActorRotation();

                int32 Index = Z * (Width * Height) + Y * Width + X;

                if (!Map.IsValidIndex(Index))
                {
                    UE_LOG(LogTemp, Warning, TEXT("맵 인덱스가 유효하지 않습니다: %d"), Index);
                    continue;
                }

                char MapValue = Map[Index];

                if (MapValue == '0')
                {
                    continue;
                }

                AStaticMeshActor* NewMesh = GetWorld()->SpawnActor<AStaticMeshActor>(NewLocation, NewRotator);
                if (!NewMesh || !NewMesh->GetStaticMeshComponent())
                {
                    UE_LOG(LogTemp, Error, TEXT("새 메쉬 액터 생성에 실패했습니다."));
                    continue;
                }

                CreatedActors.Add(NewMesh); // 생성된 액터를 배열에 추가

                switch (MapValue)
                {
                case '1':
                    if (ObstacleBlock)
                    {
                        NewMesh->GetStaticMeshComponent()->SetStaticMesh(ObstacleBlock);
                    }
                    break;

                case '2':
                    if (StartBlock)
                    {
                        NewMesh->GetStaticMeshComponent()->SetStaticMesh(StartBlock);
                        StartBlockLocation = NewLocation; // 시작 위치 저장
                    }
                    break;

                case '3':
                    if (EndBlock)
                    {
                        NewMesh->GetStaticMeshComponent()->SetStaticMesh(EndBlock);
                    }
                    break;

                default:
                    UE_LOG(LogTemp, Warning, TEXT("유효하지 않은 맵 데이터: %c"), MapValue);
                    break;
                }
            }
        }
    }
}

// Start Magic
void ACAlgorithmQuestion::StartMagic()
{
    if (!MagicCircle)
    {
        UE_LOG(LogTemp, Warning, TEXT("MagicCircle이 설정되지 않았습니다."));
        return;
    }

    // Luni를 StartBlock의 위치로 이동
    if (Luni && !StartBlockLocation.IsZero())
    {
        Luni->SetActorLocation(StartBlockLocation);
        UE_LOG(LogTemp, Log, TEXT("Luni가 시작 위치로 이동되었습니다."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("StartBlock의 위치가 설정되지 않았습니다."));
    }

    // 코드 블록 인덱스 초기화
    CurrentCodeBlockIndex = 0;

    // 타이머 시작 (TimerInterval을 사용하여 타이머 간격 설정)
    GetWorldTimerManager().SetTimer(CodeBlockTimerHandle, this, &ACAlgorithmQuestion::ExecuteCodeBlock, TimerInterval, true);
}

// Execute Code Block
void ACAlgorithmQuestion::ExecuteCodeBlock()
{
    if (CurrentCodeBlockIndex < MagicCircle->CodeBlocks.Num())
    {
        MoveLuni(MagicCircle->CodeBlocks[CurrentCodeBlockIndex].CodeBlockType);
        CurrentCodeBlockIndex++;
    }
    else
    {
        // 모든 코드 블록 실행 완료 시 타이머 정지
        GetWorldTimerManager().ClearTimer(CodeBlockTimerHandle);
        // UE_LOG(LogTemp, Log, TEXT("모든 코드 블록 실행 완료"));
    }
}

// Move Luni
void ACAlgorithmQuestion::MoveLuni(ECodeBlockType InCodeBlockType)
{
    if (!Luni)
    {
        UE_LOG(LogTemp, Warning, TEXT("Luni가 설정되지 않았습니다."));
        return;
    }

    FVector NewLocation = Luni->GetActorLocation();

    switch (InCodeBlockType)
    {
    case ECodeBlockType::Forward:
        NewLocation += Luni->GetActorForwardVector() * Spacing;
        break;
    case ECodeBlockType::RightTurn:
        Luni->AddActorLocalRotation(FRotator(0.f, 90.f, 0.f));
        break;
    case ECodeBlockType::LeftTurn:
        Luni->AddActorLocalRotation(FRotator(0.f, -90.f, 0.f));
        break;
    case ECodeBlockType::Jump:
        NewLocation += FVector(0.f, 0.f, Spacing);
        NewLocation += Luni->GetActorForwardVector() * Spacing;
        break;
    case ECodeBlockType::Repetition:
        // 반복 로직 구현
        break;
    case ECodeBlockType::Number:
        // 숫자 로직 구현
        break;
    default:
        break;
    }

    // 장애물 및 EndBlock 오버랩 검사
    FCollisionQueryParams CollisionParams;
    if (GetWorld()->OverlapBlockingTestByChannel(NewLocation, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(50.f), CollisionParams))
    {
        // HitResult는 필요 없음
        TArray<FOverlapResult> Overlaps;
        if (GetWorld()->OverlapMultiByChannel(Overlaps, NewLocation, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(50.f), CollisionParams))
        {
            for (auto& Overlap : Overlaps)
            {
                AStaticMeshActor* HitActor = Cast<AStaticMeshActor>(Overlap.GetActor());

                if (HitActor)
                {
                    UStaticMesh* HitMesh = HitActor->GetStaticMeshComponent()->GetStaticMesh();

                    if (HitMesh == ObstacleBlock)
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Luni가 장애물과 겹쳤습니다."));
                        return;
                    }
                    else if (HitMesh == EndBlock)
                    {
                        UE_LOG(LogTemp, Log, TEXT("Luni가 EndBlock에 도달했습니다."));
                        
                        FinishMagic();
                        return;
                    }
                }
            }
        }
    }

    Luni->SetActorLocation(NewLocation);
}

// Clear Map
void ACAlgorithmQuestion::ClearMap()
{
    // 생성된 모든 액터 제거
    for (AStaticMeshActor* Actor : CreatedActors)
    {
        if (Actor)
        {
            Actor->Destroy();
        }
    }
    CreatedActors.Empty();

    // Luni 제거
    if (Luni)
    {
        Luni->Destroy();
        Luni = nullptr;
    }

    UE_LOG(LogTemp, Log, TEXT("맵이 클리어되었습니다."));
}
