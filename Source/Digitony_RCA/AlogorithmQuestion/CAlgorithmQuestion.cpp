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
	// 0 일경우 빈 공간
	// 1 일경우 장애물 생성
	// 2일 경우 시작지점
	// 3일 경우 도착 지점
}

