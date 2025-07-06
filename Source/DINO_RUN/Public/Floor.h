// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerGameMode.h"
#include "GameFramework/Actor.h"
#include "PaperTileMapComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Floor.generated.h"

UCLASS()
class DINO_RUN_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();
	//UPROPERTY(VisibleAnywhere)
	//UPaperTileMapComponent* TileMapComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* Arrow0;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* Arrow1;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* Arrow2;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* Arrow3;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* Arrow4;
	UPROPERTY(BlueprintReadOnly)
	AEndlessRunnerGameMode* AsEndlessRunnerGameMode;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						   bool bFromSweep, const FHitResult& SweepResult);
};
