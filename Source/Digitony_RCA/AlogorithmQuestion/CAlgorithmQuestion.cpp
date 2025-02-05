#include "AlogorithmQuestion/CAlgorithmQuestion.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Containers/Array.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"


// ������
ACAlgorithmQuestion::ACAlgorithmQuestion()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentCodeBlockIndex = 0; // �ε��� �ʱ�ȭ
}

// Begin Play
void ACAlgorithmQuestion::BeginPlay()
{
    Super::BeginPlay();
    LoadMapData();
}

// Tick �Լ�
void ACAlgorithmQuestion::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Load Map Data
void ACAlgorithmQuestion::LoadMapData()
{
    if (!MapData.DataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("MapData DataTable�� �������� �ʾҽ��ϴ�."));
        return;
    }

    FAlgorithmQuestionMapData* Row = MapData.DataTable->FindRow<FAlgorithmQuestionMapData>(MapData.RowName, TEXT(""));

    if (!Row)
    {
        UE_LOG(LogTemp, Warning, TEXT("MapData ���� ã�� �� �����ϴ�."));
        return;
    }

    ID = Row->ID;
    Width = Row->Width;
    Height = Row->Height;
    Depth = Row->Depth;
    Map = Row->Map;

    UE_LOG(LogTemp, Log, TEXT("�� ������ �ε� �Ϸ�: Width=%d, Height=%d, Depth=%d"), Width, Height, Depth);

    // �� ���� ������ �񵿱������� ó��
    AsyncTask(ENamedThreads::GameThread, [this]()
        {
            CreateMap();
        });
}

// Create Map
void ACAlgorithmQuestion::CreateMap()
{
    StartBlockLocation = FVector::ZeroVector; // ���� ��ġ �ʱ�ȭ

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
                    UE_LOG(LogTemp, Warning, TEXT("�� �ε����� ��ȿ���� �ʽ��ϴ�: %d"), Index);
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
                    UE_LOG(LogTemp, Error, TEXT("�� �޽� ���� ������ �����߽��ϴ�."));
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
                        StartBlockLocation = NewLocation; // ���� ��ġ ����
                        UE_LOG(LogTemp, Log, TEXT("StartBlock ��ġ: %s"), *StartBlockLocation.ToString());
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
                        CreatedCoins.Add(NewMesh);  // ������ �迭�� �߰�
                        UE_LOG(LogTemp, Log, TEXT("���� ��ȯ: ��ġ = %s"), *NewLocation.ToString());
                    }
                    break;

                default:
                    UE_LOG(LogTemp, Warning, TEXT("��ȿ���� ���� �� ������: %c"), MapValue);
                    break;
                }
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("CreateMap() �Ϸ��"));
}

// Start Magic
void ACAlgorithmQuestion::StartMagic()
{
    if (!MagicCircle)
    {
        UE_LOG(LogTemp, Warning, TEXT("MagicCircle�� �������� �ʾҽ��ϴ�."));
        return;
    }

    // �� �缳�� �� ���� �����
    ClearMap();
    LoadMapData();

    if (Luni && !StartBlockLocation.IsZero())
    {
        Luni->SetActorLocation(StartBlockLocation);
        Luni->SetActorRotation(InitialLuniRotation);  // �ʱ� ȸ�� ����
        UE_LOG(LogTemp, Log, TEXT("Luni�� ���� ��ġ�� �̵��Ǿ����� �ʱ� ȸ���� �����Ǿ����ϴ�."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("StartBlock�� ��ġ�� �������� �ʾҽ��ϴ�."));
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
                bIsRepetitionActive = false;  // �ݺ� ����
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
                RepetitionBlocks.Empty();  // ���� �ݺ� ����� �ʱ�ȭ
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

    // Ÿ�̸Ӹ� ���� �ݺ� ����� ���������� ó��
    int32 CurrentIndex = 0;

    GetWorldTimerManager().SetTimer(CodeBlockTimerHandle, [this, Blocks, RepeatCount, CurrentIndex]() mutable
        {
            // ����� ���������� ����
            MoveLuni(Blocks[CurrentIndex]);
            CurrentIndex++;

            // ������ ��� ó�� �� �ݺ� ó��
            if (CurrentIndex >= Blocks.Num())
            {
                CurrentIndex = 0;
                RepeatCount--;

                if (RepeatCount <= 0)
                {
                    GetWorldTimerManager().ClearTimer(CodeBlockTimerHandle); // ��� �ݺ��� ������ Ÿ�̸� ����
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
        UE_LOG(LogTemp, Warning, TEXT("Luni�� �������� �ʾҽ��ϴ�."));
        return;
    }

    FVector NewLocation = Luni->GetActorLocation();

    switch (InCodeBlockType)
    {
    case ECodeBlockType::Forward:
        NewLocation += Luni->GetActorForwardVector() * Spacing;
        UE_LOG(LogTemp, Log, TEXT("���� ��: NewLocation = %s"), *NewLocation.ToString());
        break;

    case ECodeBlockType::RightTurn:
        Luni->AddActorLocalRotation(FRotator(0.f, 90.f, 0.f));
        UE_LOG(LogTemp, Log, TEXT("��ȸ�� ��"));
        break;

    case ECodeBlockType::LeftTurn:
        Luni->AddActorLocalRotation(FRotator(0.f, -90.f, 0.f));
        UE_LOG(LogTemp, Log, TEXT("��ȸ�� ��"));
        break;

    case ECodeBlockType::Jump:
        NewLocation += FVector(0.f, 0.f, Spacing);  // ���� ����
        NewLocation += Luni->GetActorForwardVector() * Spacing;  // ������ �̵�
        UE_LOG(LogTemp, Log, TEXT("���� ��: NewLocation = %s"), *NewLocation.ToString());
        break;

    case ECodeBlockType::DownJump:
        NewLocation += Luni->GetActorForwardVector() * Spacing;  // ������ �̵�
        NewLocation -= FVector(0.f, 0.f, Spacing);  // �Ʒ��� ����
        UE_LOG(LogTemp, Log, TEXT("�ϰ� ��: NewLocation = %s"), *NewLocation.ToString());
        break;

    default:
        UE_LOG(LogTemp, Warning, TEXT("��ȿ���� ���� �ڵ� ��� Ÿ���Դϴ�."));
        return;
    }

    // ��ġ�� ���� ������Ʈ�� �Ŀ� �浹 �˻� �� ó��
    Luni->SetActorLocation(NewLocation);

    FCollisionQueryParams CollisionParams;
    const float CollisionRadius = Spacing * 0.4f;
    TArray<FOverlapResult> Overlaps;

    if (GetWorld()->OverlapMultiByChannel(Overlaps, NewLocation, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(CollisionRadius), CollisionParams))
    {
        for (const FOverlapResult& Overlap : Overlaps)
        {
            // GetActor() ȣ�� �� ��ȿ�� �˻�
            if (AActor* OverlapActor = Overlap.GetActor())
            {
                AStaticMeshActor* HitActor = Cast<AStaticMeshActor>(OverlapActor);
                if (HitActor)
                {
                    UStaticMesh* HitMesh = HitActor->GetStaticMeshComponent()->GetStaticMesh();

                    if (HitMesh == CoinMesh)
                    {
                        UE_LOG(LogTemp, Log, TEXT("��ϰ� ������ �Ծ����ϴ�."));
                        CreatedCoins.Remove(HitActor);
                        HitActor->Destroy();
                    }

                    if (HitMesh == ObstacleBlock || HitMesh == TransparentObstacleBlock)
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Luni�� ��ֹ��� �浹�߽��ϴ�."));
                        return;
                    }
                    else if (HitMesh == EndBlock)
                    {
                        if (CreatedCoins.Num() > 0)
                        {
                            UE_LOG(LogTemp, Warning, TEXT("��� ������ �Ա� ������ ���� Ŭ������ �� �����ϴ�."));
                            return;
                        }

                        UE_LOG(LogTemp, Log, TEXT("Luni�� EndBlock�� �����߽��ϴ�."));
                        FinishMagic();
                        return;
                    }
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("��ȿ���� ���� OverlapActor�Դϴ�."));
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Luni�� �� ��ġ: %s"), *NewLocation.ToString());
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


    UE_LOG(LogTemp, Log, TEXT("���� Ŭ����Ǿ����ϴ�."));
}
