#include "EndlessRunnerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Dino.h"
#include "Floor.h"
#include "Obstacle.h"
#include "Coin.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEndlessRunnerGameMode::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (PlayerCharacter)
	{
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		FVector SpawnLocation = PlayerLocation - FVector(700.f, 0.f, 100.f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		SpawnedFloor = GetWorld()->SpawnActor<AFloor>(BP_Floor, SpawnLocation, SpawnRotation);

		if (SpawnedFloor)
		{
			FloorSpawner(false);
		}

		ADino* IsDino = Cast<ADino>(PlayerCharacter);
		if (IsDino)
		{
			AsBPDino = IsDino;
			PlayerStartPoint = AsBPDino->GetActorLocation().X;
		}
	}
}

void AEndlessRunnerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AsBPDino && !AsBPDino->IsDead)
	{
		TimeCounter(DeltaTime);
		DistanceCounter();
	}
}

void AEndlessRunnerGameMode::TimeCounter(float DeltaTime)
{
	Time += DeltaTime;
}

void AEndlessRunnerGameMode::DistanceCounter()
{
	float CurrentX = AsBPDino->GetActorLocation().X;
	DistanceTravel = (CurrentX - PlayerStartPoint) / 100.0;
}

void AEndlessRunnerGameMode::FloorSpawner(bool CanSpawnObstacles)
{
	if (!SpawnedFloor || !SpawnedFloor->Arrow4) return;

	FTransform SpawnTransform = SpawnedFloor->Arrow4->GetComponentTransform();
	AFloor* NewFloor = GetWorld()->SpawnActor<AFloor>(BP_Floor, SpawnTransform);

	if (NewFloor)
	{
		SpawnedFloor = NewFloor;

		if (CanSpawnObstacles)
		{
			ObstaclesSpawner(SpawnedFloor->Arrow1); // jumpable
			ObstaclesSpawner(SpawnedFloor->Arrow2); // jumpable
			ObstaclesSpawner(SpawnedFloor->Arrow3); // jumpable
		}

		
		SpawnBirdChain(SpawnedFloor->Arrow0);
	}
}

void AEndlessRunnerGameMode::ObstaclesSpawner(UArrowComponent* ArrowComponent)
{
	if (!ArrowComponent || ObstaclesCanJump.Num() == 0) return;

	int32 RandomChance = UKismetMathLibrary::RandomIntegerInRange(1, 100);
	if (RandomChance <= 70 && UKismetMathLibrary::RandomBool())
	{
		int32 Index = UKismetMathLibrary::RandomInteger(ObstaclesCanJump.Num());
		TSubclassOf<AActor> ObstacleClass = ObstaclesCanJump[Index];

		if (ObstacleClass)
		{
			FVector SpawnLocation = ArrowComponent->GetComponentLocation();
			FRotator SpawnRotation = FRotator::ZeroRotator;

			FActorSpawnParameters Params;
			GetWorld()->SpawnActor<AActor>(ObstacleClass, SpawnLocation, SpawnRotation, Params);
		}
	}
	else
	{
		// Spawn coin chain
		int32 CoinChance = UKismetMathLibrary::RandomIntegerInRange(1, 100);
		if (CoinChance <= 80 && CoinClass)
		{
			FVector SpawnLocation = ArrowComponent->GetComponentLocation();
			FRotator SpawnRotation = FRotator::ZeroRotator;
			FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation, FVector(1.f));

			FActorSpawnParameters Params;
			ACoin* SpawnedCoin = GetWorld()->SpawnActor<ACoin>(CoinClass, SpawnTransform, Params);
			LastCoinSpawned = SpawnedCoin;

			int32 NumToSpawn = UKismetMathLibrary::RandomIntegerInRange(1, 8);
			for (int32 i = 1; i < NumToSpawn; ++i)
			{
				if (!LastCoinSpawned) break;

				UArrowComponent* ArrowComp = LastCoinSpawned->FindComponentByClass<UArrowComponent>();
				if (!ArrowComp) break;

				FVector NextLoc = ArrowComp->GetComponentLocation();
				FRotator NextRot = ArrowComp->GetComponentRotation();

				ACoin* NewCoin = GetWorld()->SpawnActor<ACoin>(CoinClass, NextLoc, NextRot, Params);
				LastCoinSpawned = NewCoin;
			}
		}
	}
}

void AEndlessRunnerGameMode::SpawnBirdChain(UArrowComponent* StartArrow)
{
	if (!StartArrow || !ObstacleClassBrid) return;

	FVector SpawnLocation = StartArrow->GetComponentLocation();
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AObstacle* FirstBird = GetWorld()->SpawnActor<AObstacle>(ObstacleClassBrid, SpawnLocation, SpawnRotation, Params);
	LastBridSpawn = FirstBird;

	int32 NumToSpawn = UKismetMathLibrary::RandomIntegerInRange(1, 4);
	for (int32 i = 1; i < NumToSpawn; ++i)
	{
		if (!LastBridSpawn) break;

		UArrowComponent* Arrow = LastBridSpawn->FindComponentByClass<UArrowComponent>();
		if (!Arrow) break;

		FVector NextLoc = Arrow->GetComponentLocation();
		FRotator NextRot = Arrow->GetComponentRotation();

		AObstacle* NewBird = GetWorld()->SpawnActor<AObstacle>(ObstacleClassBrid, NextLoc, NextRot, Params);
		if (NewBird)
		{
			LastBridSpawn = NewBird;
		}
	}
}
