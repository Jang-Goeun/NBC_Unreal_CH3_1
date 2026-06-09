// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableObject.h"

// Sets default values
AMovableObject::AMovableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
}

// Called when the game starts or when spawned
void AMovableObject::BeginPlay()
{
	Super::BeginPlay();

	// 시작 위치
	StartLocation = GetActorLocation();
	// 왕복 범위
	MaxRange = 1000.0f;
	// 이동 주기
	TeleportTime = 1.0f;
	// 나타났다가 사라지는 주기
	ToggleVisibilityTime = 5.0f;

	// TeleportTime초마다 무작위 위치로 이동
	GetWorld()->GetTimerManager().SetTimer(TeleportTimerHandle, this, &AMovableObject::Teleport, TeleportTime, true);

	// ToggleVisibilityTime초마다 나타났다가 사라졌다가를 반복함
	GetWorld()->GetTimerManager().SetTimer(VisibilityTimerHandle, this, &AMovableObject::ToggleVisibility, ToggleVisibilityTime, true);
}

// 무작위 이동을 위한 함수
void AMovableObject::Teleport()
{
	float RandomYOffset = FMath::RandRange(-MaxRange, MaxRange);
	FVector NewLocation = StartLocation;
	NewLocation.Y += RandomYOffset;
	SetActorLocation(NewLocation);
}

// 나타남/사라짐 함수
void AMovableObject::ToggleVisibility()
{
	bool bIsHidden = IsHidden();
	SetActorHiddenInGame(!bIsHidden);
	SetActorEnableCollision(bIsHidden);
}
