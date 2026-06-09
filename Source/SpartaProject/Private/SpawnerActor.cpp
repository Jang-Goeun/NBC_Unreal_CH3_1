// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerActor.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnerActor::ASpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SetRootComponent(SpawnVolume);

	// 영역 크기 설정
	SpawnVolume->SetBoxExtent(FVector(2500.0f, 2500.0f, 500.0f));
}

// Called when the game starts or when spawned
void ASpawnerActor::BeginPlay()
{
	Super::BeginPlay();

	if (!SpinnerClass || !MovableClass) return;

	FVector BoxExtent = SpawnVolume->GetScaledBoxExtent();
	FVector BoxOrigin = SpawnVolume->GetComponentLocation();

	for (int i =0; i < SpawnCount; i++)
	{
		// 1. 박스 영역 내의 랜덤한 위치 계산
        FVector RandomLocation = BoxOrigin + FVector(
           FMath::RandRange(-BoxExtent.X, BoxExtent.X),
           FMath::RandRange(-BoxExtent.Y, BoxExtent.Y),
           FMath::RandRange(-BoxExtent.Z, BoxExtent.Z)
        );

		// 2. 랜덤한 Z축 회전값 생성
		FRotator RandomRotation = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);

		// 3. 월드에 액터 스폰
		TSubclassOf<AActor> ClassToSpawn = FMath::RandBool() ? SpinnerClass : MovableClass;

		GetWorld()->SpawnActor<AActor>(ClassToSpawn, RandomLocation, RandomRotation);
	}
}
