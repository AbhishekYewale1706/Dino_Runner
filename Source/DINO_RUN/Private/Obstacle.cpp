// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "Dino.h"
#include "Kismet/GameplayStatics.h"
#include "EndlessRunnerGameMode.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	ObstaclesFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	ObstaclesFlipbook->SetupAttachment(DefaultSceneRoot);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->SetupAttachment(DefaultSceneRoot);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
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
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (!PlayerCharacter) return;

	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	FVector ObstacleLocation = GetActorLocation();

	float DeltaX = PlayerLocation.X - ObstacleLocation.X;

	if (DeltaX > 1500.0f)
	{
		Destroy();
	}

}

void AObstacle::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (OtherActor == Cast<AActor>(PlayerCharacter))
	{
		AsEndlessRunnerGameMode->AsBPDino->Hit();
		Destroy();
	}
}

