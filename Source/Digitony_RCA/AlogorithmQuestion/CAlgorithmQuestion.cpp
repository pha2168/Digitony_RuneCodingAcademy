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
//    UE_LOG(LogTemp, Log, TEXT("ACAlgorithmQuestion::BeginPlay() 호출됨"));
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

                // 이동성을 Movable로 설정
                NewMesh->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
                NewMesh->GetStaticMeshComponent()->SetWorldScale3D(FVector(0.1f));

                // 생성된 액터를 배열에 추가
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

    // Luni를 StartBlock의 위치로 이동하고 초기 회전을 설정
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
        UE_LOG(LogTemp, Log, TEXT("코드 블록 실행: %d"), CurrentCodeBlockIndex);
        MoveLuni(MagicCircle->CodeBlocks[CurrentCodeBlockIndex].CodeBlockType);
        CurrentCodeBlockIndex++;
    }
    else
    {
        // 모든 코드 블록 실행 완료 시 타이머 정지
        GetWorldTimerManager().ClearTimer(CodeBlockTimerHandle);
        //UE_LOG(LogTemp, Log, TEXT("모든 코드 블록 실행 완료"));
    }
}

// Move Luni
void ACAlgorithmQuestion::MoveLuni(ECodeBlockType InCodeBlockType)
{
    static int32 RepeatCount = 0;
    static int32 RepeatStartIndex = 0;
    static bool bInRepetition = false;

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

    case ECodeBlockType::Repetition:
        RepeatStartIndex = CurrentCodeBlockIndex;
        bInRepetition = true;
        break;

    case ECodeBlockType::Number_2:
    case ECodeBlockType::Number_3:
    case ECodeBlockType::Number_4:
        if (bInRepetition)
        {
            RepeatCount = static_cast<int32>(InCodeBlockType) - static_cast<int32>(ECodeBlockType::Number_2) + 2;
            bInRepetition = false;
            UE_LOG(LogTemp, Log, TEXT("반복 횟수 설정: %d"), RepeatCount);
            
            // Repetition 블록 처리
            if (!bInRepetition && RepeatCount > 0)
            {
                if (CurrentCodeBlockIndex >= MagicCircle->CodeBlocks.Num() - 1)
                {
                    RepeatCount--;
                    CurrentCodeBlockIndex = RepeatStartIndex;

                    if (RepeatCount <= 0)
                    {
                        CurrentCodeBlockIndex++;
                        return;
                    }
                }
            }
        }
        break;

    default:
        UE_LOG(LogTemp, Warning, TEXT("유효하지 않은 코드 블록 타입입니다."));
        return;
    }

    

    // 충돌 검사
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
                    return;
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

    // 충돌이 없다면 위치 업데이트
    Luni->SetActorLocation(NewLocation);
    UE_LOG(LogTemp, Log, TEXT("Luni의 새 위치: %s"), *NewLocation.ToString());
}






// Clear Map
void ACAlgorithmQuestion::ClearMap()
{
    // Clear the array of created actors
    for (AStaticMeshActor* Actor : CreatedActors)
    {
        if (Actor) // Check if the actor is valid
        {
            Actor->Destroy(); // Mark the actor for deletion
        }
    }
    CreatedActors.Empty(); // Clear the array to prevent further access

    // Destroy Luni
    if (Luni)
    {
        Luni->Destroy();
        Luni = nullptr;
    }

    UE_LOG(LogTemp, Log, TEXT("맵이 클리어되었습니다."));

}
