// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerActor.generated.h"

UCLASS()
class SPARTAPROJECT_API ASpawnerActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnerActor|Spinner")
	TSubclassOf<AActor> SpinnerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnerActor|MovableObject")
	TSubclassOf<AActor> MovableClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning")
	int SpawnCount = 5;
};
