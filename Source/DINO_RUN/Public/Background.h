// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Background.generated.h"

UCLASS()
class DINO_RUN_API ABackground : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABackground();
    
protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Sprites")
	UPaperSpriteComponent* BackgroundSprite;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Sprites")
	UPaperSpriteComponent* Layer1Sprite;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Sprites")
	UPaperSpriteComponent* Layer2Sprite;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Sprites")
	UPaperSpriteComponent* Layer3Sprite;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Sprites")
	UPaperSpriteComponent* Layer4Sprite;
	
 
};
