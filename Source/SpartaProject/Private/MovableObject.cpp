// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableObject.h"

// Sets default values
AMovableObject::AMovableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	// Static Mesh를 코드에서 설정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Stairs.SM_Stairs"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	// Material을 코드에서 설정
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	// 시작 위치
	StartLocation = GetActorLocation();
	// 이동 속도
	MoveSpeed = 100.0f;
	// 왕복 범위
	MaxRange = 1000.0f;
}

// Called when the game starts or when spawned
void AMovableObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMovableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 현재 위치
	FVector CurrentLocation = GetActorLocation();

	// 위치 이동 계산
	CurrentLocation.Y += MoveSpeed * DeltaTime;

	// 현재 위치가 범위를 벗어나면 방향 변경
	float MovedDistance = FMath::Abs(CurrentLocation.Y - StartLocation.Y);
	if (MovedDistance >= MaxRange)
	{
		MoveSpeed *= -1;

		if (CurrentLocation.Y > StartLocation.Y)
		{
			CurrentLocation.Y = StartLocation.Y + MaxRange;
		}
		else
		{
			CurrentLocation.Y = StartLocation.Y - MaxRange;
		}
	}


	// 새로운 위치 설정
	SetActorLocation(CurrentLocation);
}

