// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Obstacle.generated.h"

class AEndlessRunnerGameMode;
UCLASS()
class DINO_RUN_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperFlipbookComponent* ObstaclesFlipbook;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* CollisionBox;
	UPROPERTY()
	AEndlessRunnerGameMode* AsEndlessRunnerGameMode;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp,
						   AActor* OtherActor,
						   UPrimitiveComponent* OtherComp,
						   int32 OtherBodyIndex,
						   bool bFromSweep,
						   const FHitResult& SweepResult);

};
