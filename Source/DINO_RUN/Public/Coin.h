// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

class UPaperFlipbookComponent;
class USphereComponent;
class UArrowComponent;
class AEndlessRunnerGameMode;

UCLASS()
class DINO_RUN_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USphereComponent* CollisionComponent;
	UPROPERTY()
	AEndlessRunnerGameMode* AsEndlessRunnerGameMode;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						   bool bFromSweep, const FHitResult& SweepResult);
};
