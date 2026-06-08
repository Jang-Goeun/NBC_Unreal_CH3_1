// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovableObject.generated.h"

UCLASS()
class SPARTAPROJECT_API AMovableObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 루트 컴포넌트
	USceneComponent* SceneRoot;
	// Static Mesh Component 포인터
	UStaticMeshComponent* StaticMeshComp;

	// 시작 위치 저장/기준점으로 사용할 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Obstacle|Move")
	FVector StartLocation;
	// 이동 속도를 나타내는 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Obstacle|Move")
	float MoveSpeed;
	// 왕복 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Obstacle|Move")
	float MaxRange;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
