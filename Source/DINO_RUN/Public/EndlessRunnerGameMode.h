// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"

class ADino;
class AFloor;
class ACoin;
UCLASS()
class DINO_RUN_API AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

	public:
	       AEndlessRunnerGameMode();
	       UPROPERTY(BlueprintReadWrite, Category = "Debug")
	       ADino* AsBPDino;

	       UPROPERTY(BlueprintReadWrite, Category = "Debug")
	       float PlayerStartPoint;

	       UPROPERTY(BlueprintReadWrite, Category = "Debug")
	       float DistanceTravel;

	       UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
	       float Time = 0.0;
	
	       UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
	       int Coin = 0;

	       UPROPERTY(EditAnywhere, Category = "Spawning")
	       TSubclassOf<class AFloor> BP_Floor;
	
	       UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "References")
	        AFloor* SpawnedFloor;
	
	protected:
	       virtual void BeginPlay() override;
	
	public:
	      virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void TimeCounter(float DealtTime);
	UFUNCTION(BlueprintCallable)
	void DistanceCounter();

	UFUNCTION(BlueprintCallable, Category = "Floor")
	void FloorSpawner(bool CanSpawnObstacles);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<TSubclassOf<AActor>> ObstaclesCanJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> ObstacleClassBrid;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	AActor* LastBridSpawn;
	
	UFUNCTION(BlueprintCallable)
	void ObstaclesSpawner(UArrowComponent* ArrowComponent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<ACoin> CoinClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "Spawn")
	ACoin* LastCoinSpawned;
	void SpawnBirdChain(UArrowComponent* StartArrow);
};
