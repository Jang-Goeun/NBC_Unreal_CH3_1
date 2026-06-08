// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spinner.generated.h"

UCLASS()
class SPARTAPROJECT_API ASpinner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpinner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 루트 컴포넌트
	USceneComponent* SceneRoot;
	// Static Mesh Component 포인터
	UStaticMeshComponent* StaticMeshComp;

	// 회전 속도를 나타내는 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Obstacle|Rotate")
	float RotationSpeed;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
