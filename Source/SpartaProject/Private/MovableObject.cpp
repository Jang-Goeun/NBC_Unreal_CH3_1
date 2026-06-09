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

	// 기본값 설정
	MaxRange = 300.0f;
	TeleportTime = 1.0f;
	ToggleVisibilityTime = 5.0f;
}

// Called when the game starts or when spawned
void AMovableObject::BeginPlay()
{
	Super::BeginPlay();

	// 시작 위치 저장
	StartLocation = GetActorLocation();

	// 타이머 설정
	GetWorld()->GetTimerManager().SetTimer(TeleportTimerHandle, this, &AMovableObject::Teleport, TeleportTime, true);
	GetWorld()->GetTimerManager().SetTimer(VisibilityTimerHandle, this, &AMovableObject::ToggleVisibility, ToggleVisibilityTime, true);
}

#if WITH_EDITOR
void AMovableObject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	// 에디터에서 TeleportTime을 수정하면 즉시 타이머를 갱신
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMovableObject, TeleportTime))
	{
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(TeleportTimerHandle, this, &AMovableObject::Teleport, TeleportTime, true);
		}
	}

	// 에디터에서 ToggleVisibilityTime을 수정하면 즉시 타이머를 갱신
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMovableObject, ToggleVisibilityTime))
	{
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(VisibilityTimerHandle, this, &AMovableObject::ToggleVisibility, ToggleVisibilityTime, true);
		}
	}
}
#endif

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
