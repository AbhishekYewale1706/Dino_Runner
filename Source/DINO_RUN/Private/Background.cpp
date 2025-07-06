// Fill out your copyright notice in the Description page of Project Settings.


#include "Background.h"

// Sets default values
ABackground::ABackground()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
    BackgroundSprite=CreateDefaultSubobject<UPaperSpriteComponent>("BackgroundSprite");
	BackgroundSprite->SetupAttachment(GetRootComponent());
	
	Layer1Sprite=CreateDefaultSubobject<UPaperSpriteComponent>("layerSprite1");
	Layer1Sprite->SetupAttachment(BackgroundSprite);
	
	Layer2Sprite=CreateDefaultSubobject<UPaperSpriteComponent>("layerSprite2");
	Layer2Sprite->SetupAttachment(BackgroundSprite);

	Layer3Sprite=CreateDefaultSubobject<UPaperSpriteComponent>("layerSprite3");
	Layer3Sprite->SetupAttachment(BackgroundSprite);

	Layer4Sprite=CreateDefaultSubobject<UPaperSpriteComponent>("layerSprite4");
	Layer4Sprite->SetupAttachment(BackgroundSprite);
}

// Called when the game starts or when spawned
void ABackground::BeginPlay()
{
	Super::BeginPlay();
	
}
 
// Called every frame
void ABackground::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

