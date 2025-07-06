// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "PaperFlipbook.h"
#include "Kismet/GameplayStatics.h"
#include "Dino.h"
#include "EndlessRunnerGameMode.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	FlipbookComponent->SetupAttachment(RootComponent);
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnBoxBeginOverlap);
	

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this);
	AEndlessRunnerGameMode* RunnerGamemode = Cast<AEndlessRunnerGameMode>(GameModeBase);
	if (RunnerGamemode)
	{
		AsEndlessRunnerGameMode = RunnerGamemode;
	}
	
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (!PlayerCharacter) return;

	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	FVector CoinLocation = GetActorLocation();

	float DeltaX = PlayerLocation.X - CoinLocation.X;

	if (DeltaX > 1500.0f)
	{
		Destroy();
	}

}

void ACoin::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (OtherActor == Cast<AActor>(PlayerCharacter))
	{
		AsEndlessRunnerGameMode->Coin++;
		Destroy();
	}
}
