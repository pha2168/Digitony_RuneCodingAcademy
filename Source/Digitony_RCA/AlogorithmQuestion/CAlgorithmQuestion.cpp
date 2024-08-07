#include "AlogorithmQuestion/CAlgorithmQuestion.h"
#include "Engine/StaticMeshActor.h"
#include "TimerManager.h"

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
//    UE_LOG(LogTemp, Log, TEXT("ACAlgorithmQuestion::BeginPlay() ȣ���"));
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
//    UE_LOG(LogTemp, Log, TEXT("CreateMap() ȣ���"));

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

                // �̵����� Movable�� ����
                NewMesh->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
                NewMesh->GetStaticMeshComponent()->SetWorldScale3D(FVector(0.1f));

                CreatedActors.Add(NewMesh); // ������ ���͸� �迭�� �߰�

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

    // Luni�� StartBlock�� ��ġ�� �̵�
    if (Luni && !StartBlockLocation.IsZero())
    {
        Luni->SetActorLocation(StartBlockLocation);
        UE_LOG(LogTemp, Log, TEXT("Luni�� ���� ��ġ�� �̵��Ǿ����ϴ�."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("StartBlock�� ��ġ�� �������� �ʾҽ��ϴ�."));
    }

    // �ڵ� ��� �ε��� �ʱ�ȭ
    CurrentCodeBlockIndex = 0;

    // Ÿ�̸� ���� (TimerInterval�� ����Ͽ� Ÿ�̸� ���� ����)
    GetWorldTimerManager().SetTimer(CodeBlockTimerHandle, this, &ACAlgorithmQuestion::ExecuteCodeBlock, TimerInterval, true);
}

// Execute Code Block
void ACAlgorithmQuestion::ExecuteCodeBlock()
{
    if (CurrentCodeBlockIndex < MagicCircle->CodeBlocks.Num())
    {
        UE_LOG(LogTemp, Log, TEXT("�ڵ� ��� ����: %d"), CurrentCodeBlockIndex);
        MoveLuni(MagicCircle->CodeBlocks[CurrentCodeBlockIndex].CodeBlockType);
        CurrentCodeBlockIndex++;
    }
    else
    {
        // ��� �ڵ� ��� ���� �Ϸ� �� Ÿ�̸� ����
        GetWorldTimerManager().ClearTimer(CodeBlockTimerHandle);
        //UE_LOG(LogTemp, Log, TEXT("��� �ڵ� ��� ���� �Ϸ�"));
    }
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
    FVector OriginalLocation = NewLocation;  // ���� ��ġ ����

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
        NewLocation += FVector(0.f, 0.f, Spacing);
        NewLocation += Luni->GetActorForwardVector() * Spacing;
        UE_LOG(LogTemp, Log, TEXT("���� ��: NewLocation = %s"), *NewLocation.ToString());
        break;
    case ECodeBlockType::Repetition:
        break;
    case ECodeBlockType::Number:
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("��ȿ���� ���� �ڵ� ��� Ÿ���Դϴ�."));
        return;
    }

    // �浹 �˻� ���� ����
    FCollisionQueryParams CollisionParams;
    const float CollisionRadius = Spacing * 0.4f;  // �浹 �ݰ� ����
    TArray<FOverlapResult> Overlaps;

    if (GetWorld()->OverlapMultiByChannel(Overlaps, NewLocation, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(CollisionRadius), CollisionParams))
    {
        for (auto& Overlap : Overlaps)
        {
            AStaticMeshActor* HitActor = Cast<AStaticMeshActor>(Overlap.GetActor());

            if (HitActor)
            {
                UStaticMesh* HitMesh = HitActor->GetStaticMeshComponent()->GetStaticMesh();

                // ��ֹ��� �浹���� ���
                if (HitMesh == ObstacleBlock)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Luni�� ��ֹ��� �浹�߽��ϴ�."));
                    return; // �浹 �� �̵� �ߴ�
                }
                // EndBlock�� �������� ���
                else if (HitMesh == EndBlock)
                {
                    UE_LOG(LogTemp, Log, TEXT("Luni�� EndBlock�� �����߽��ϴ�."));
                    FinishMagic(); // EndBlock�� �����ϸ� FinishMagic ȣ��
                    return;
                }
            }
        }
    }

    // �浹�� ���ٸ� ��ġ ������Ʈ
    Luni->SetActorLocation(NewLocation);
    UE_LOG(LogTemp, Log, TEXT("Luni�� �� ��ġ: %s"), *NewLocation.ToString());
}

// Clear Map
void ACAlgorithmQuestion::ClearMap()
{
//    UE_LOG(LogTemp, Log, TEXT("ClearMap() ȣ���"));

    // ������ ��� ���� ����
    for (AStaticMeshActor* Actor : CreatedActors)
    {
        if (Actor)
        {
            Actor->Destroy();
        }
    }
    CreatedActors.Empty();

    // Luni ����
    if (Luni)
    {
        Luni->Destroy();
        Luni = nullptr;
    }

    UE_LOG(LogTemp, Log, TEXT("���� Ŭ����Ǿ����ϴ�."));
}
