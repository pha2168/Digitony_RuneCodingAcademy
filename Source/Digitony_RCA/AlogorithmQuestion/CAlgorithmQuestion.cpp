#include "AlogorithmQuestion/CAlgorithmQuestion.h"
#include "Engine/StaticMeshActor.h"
#include "Containers/Array.h"
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

    UE_LOG(LogTemp, Log, TEXT("맵 데이터 로드 완료: Width=%d, Height=%d, Depth=%d"), Width, Height, Depth);

    // 맵 생성 로직을 비동기적으로 처리
    AsyncTask(ENamedThreads::GameThread, [this]()
        {
            CreateMap();
        });
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

                NewMesh->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
                NewMesh->GetStaticMeshComponent()->SetWorldScale3D(FVector(0.1f));

                CreatedActors.Add(NewMesh);

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
                        UE_LOG(LogTemp, Log, TEXT("StartBlock 위치: %s"), *StartBlockLocation.ToString());
                    }
                    break;

                case '3':
                    if (EndBlock)
                    {
                        NewMesh->GetStaticMeshComponent()->SetStaticMesh(EndBlock);
                    }
                    break;

                case '4':
                    if (TransparentObstacleBlock)
                    {
                        NewMesh->GetStaticMeshComponent()->SetStaticMesh(TransparentObstacleBlock);
                    }
                    break;

                case '5':
                    if (CoinMesh)
                    {
                        NewMesh->GetStaticMeshComponent()->SetStaticMesh(CoinMesh);
                        NewMesh->GetStaticMeshComponent()->SetWorldScale3D(FVector(0.05f));
                        CreatedCoins.Add(NewMesh);  // 코인을 배열에 추가
                        UE_LOG(LogTemp, Log, TEXT("코인 소환: 위치 = %s"), *NewLocation.ToString());
                    }
                    break;

                default:
                    UE_LOG(LogTemp, Warning, TEXT("유효하지 않은 맵 데이터: %c"), MapValue);
                    break;
                }
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("CreateMap() 완료됨"));
}

// Start Magic
void ACAlgorithmQuestion::StartMagic()
{
    if (!MagicCircle)
    {
        UE_LOG(LogTemp, Warning, TEXT("MagicCircle이 설정되지 않았습니다."));
        return;
    }

    // 맵 재설정 및 코인 재생성
    ClearMap();
    LoadMapData();

    if (Luni && !StartBlockLocation.IsZero())
    {
        Luni->SetActorLocation(StartBlockLocation);
        Luni->SetActorRotation(InitialLuniRotation);  // 초기 회전 설정
        UE_LOG(LogTemp, Log, TEXT("Luni가 시작 위치로 이동되었으며 초기 회전이 설정되었습니다."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("StartBlock의 위치가 설정되지 않았습니다."));
    }

    CurrentCodeBlockIndex = 0;
    GetWorldTimerManager().SetTimer(CodeBlockTimerHandle, this, &ACAlgorithmQuestion::ExecuteCodeBlock, TimerInterval, true);
}

// Execute Code Block
void ACAlgorithmQuestion::ExecuteCodeBlock()
{
    static TArray<ECodeBlockType> RepetitionBlocks;
    static bool bIsRepetitionActive = false;

    if (CurrentCodeBlockIndex < MagicCircle->CodeBlocks.Num())
    {
        ECodeBlockType CurrentBlock = MagicCircle->CodeBlocks[CurrentCodeBlockIndex].CodeBlockType;

        if (bIsRepetitionActive)
        {
            if (CurrentBlock >= ECodeBlockType::Number_2 && CurrentBlock <= ECodeBlockType::Number_4)
            {
                int32 RepeatCount = static_cast<int32>(CurrentBlock) - static_cast<int32>(ECodeBlockType::Number_2) + 2;
                ProcessRepetitionBlocks(RepetitionBlocks, RepeatCount);
                bIsRepetitionActive = false;  // 반복 종료
            }
            else
            {
                RepetitionBlocks.Add(CurrentBlock);
            }
        }
        else
        {
            if (CurrentBlock == ECodeBlockType::Repetition)
            {
                bIsRepetitionActive = true;
                RepetitionBlocks.Empty();  // 이전 반복 블록을 초기화
            }
            else
            {
                MoveLuni(CurrentBlock);
            }
        }

        CurrentCodeBlockIndex++;
    }
    else
    {
        GetWorldTimerManager().ClearTimer(CodeBlockTimerHandle);
    }
}

// Process Repetition Blocks
void ACAlgorithmQuestion::ProcessRepetitionBlocks(const TArray<ECodeBlockType>& Blocks, int32 RepeatCount)
{
    if (Blocks.Num() == 0 || RepeatCount <= 0)
    {
        return;
    }

    // 타이머를 통해 반복 블록을 순차적으로 처리
    int32 CurrentIndex = 0;

    GetWorldTimerManager().SetTimer(CodeBlockTimerHandle, [this, Blocks, RepeatCount, CurrentIndex]() mutable
        {
            // 블록을 순차적으로 실행
            MoveLuni(Blocks[CurrentIndex]);
            CurrentIndex++;

            // 마지막 블록 처리 후 반복 처리
            if (CurrentIndex >= Blocks.Num())
            {
                CurrentIndex = 0;
                RepeatCount--;

                if (RepeatCount <= 0)
                {
                    GetWorldTimerManager().ClearTimer(CodeBlockTimerHandle); // 모든 반복이 끝나면 타이머 중지
                    return;
                }
            }

        }, TimerInterval, true);
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
        UE_LOG(LogTemp, Log, TEXT("전진 중: NewLocation = %s"), *NewLocation.ToString());
        break;

    case ECodeBlockType::RightTurn:
        Luni->AddActorLocalRotation(FRotator(0.f, 90.f, 0.f));
        UE_LOG(LogTemp, Log, TEXT("우회전 중"));
        break;

    case ECodeBlockType::LeftTurn:
        Luni->AddActorLocalRotation(FRotator(0.f, -90.f, 0.f));
        UE_LOG(LogTemp, Log, TEXT("좌회전 중"));
        break;

    case ECodeBlockType::Jump:
        NewLocation += FVector(0.f, 0.f, Spacing);  // 위로 점프
        NewLocation += Luni->GetActorForwardVector() * Spacing;  // 앞으로 이동
        UE_LOG(LogTemp, Log, TEXT("점프 중: NewLocation = %s"), *NewLocation.ToString());
        break;

    case ECodeBlockType::DownJump:
        NewLocation += Luni->GetActorForwardVector() * Spacing;  // 앞으로 이동
        NewLocation -= FVector(0.f, 0.f, Spacing);  // 아래로 점프
        UE_LOG(LogTemp, Log, TEXT("하강 중: NewLocation = %s"), *NewLocation.ToString());
        break;

    default:
        UE_LOG(LogTemp, Warning, TEXT("유효하지 않은 코드 블록 타입입니다."));
        return;
    }

    // 위치를 먼저 업데이트한 후에 충돌 검사 및 처리
    Luni->SetActorLocation(NewLocation);

    FCollisionQueryParams CollisionParams;
    const float CollisionRadius = Spacing * 0.4f;
    TArray<FOverlapResult> Overlaps;

    if (GetWorld()->OverlapMultiByChannel(Overlaps, NewLocation, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(CollisionRadius), CollisionParams))
    {
        for (auto& Overlap : Overlaps)
        {
            AStaticMeshActor* HitActor = Cast<AStaticMeshActor>(Overlap.GetActor());

            if (HitActor)
            {
                UStaticMesh* HitMesh = HitActor->GetStaticMeshComponent()->GetStaticMesh();

                if (HitMesh == CoinMesh)
                {
                    UE_LOG(LogTemp, Log, TEXT("루니가 코인을 먹었습니다."));
                    CreatedCoins.Remove(HitActor);
                    HitActor->Destroy();
                }

                if (HitMesh == ObstacleBlock || HitMesh == TransparentObstacleBlock)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Luni가 장애물과 충돌했습니다."));
                    return;
                }
                else if (HitMesh == EndBlock)
                {
                    if (CreatedCoins.Num() > 0)
                    {
                        UE_LOG(LogTemp, Warning, TEXT("모든 코인을 먹기 전까지 맵을 클리어할 수 없습니다."));
                        return;
                    }

                    UE_LOG(LogTemp, Log, TEXT("Luni가 EndBlock에 도달했습니다."));
                    FinishMagic();
                    return;
                }
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Luni의 새 위치: %s"), *NewLocation.ToString());
}

// Clear Map
void ACAlgorithmQuestion::ClearMap()
{
    for (AStaticMeshActor* Actor : CreatedActors)
    {
        if (Actor)
        {
            Actor->Destroy();
        }
    }
    CreatedActors.Empty();

    for (AStaticMeshActor* Coin : CreatedCoins)
    {
        if (Coin)
        {
            Coin->Destroy();
        }
    }
    CreatedCoins.Empty();


    UE_LOG(LogTemp, Log, TEXT("맵이 클리어되었습니다."));
}
