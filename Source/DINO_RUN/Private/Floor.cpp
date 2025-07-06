// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxObstacle"));
	Box->SetupAttachment(RootComponent);
	Arrow0 = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow0"));
	Arrow0->SetupAttachment(RootComponent);
	Arrow1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow1"));
	Arrow1->SetupAttachment(RootComponent);
	Arrow2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow2"));
	Arrow2->SetupAttachment(RootComponent);
	Arrow3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow3"));
	Arrow3->SetupAttachment(RootComponent);
	Arrow4 = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow4"));
	Arrow4->SetupAttachment(RootComponent);
	Box->SetGenerateOverlapEvents(true);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AFloor::OnBoxBeginOverlap);
	

}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	if (AEndlessRunnerGameMode* EndlessRunnerGameMode = Cast<AEndlessRunnerGameMode>(GameMode))
	{
		AsEndlessRunnerGameMode = EndlessRunnerGameMode;
	}

	
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (OtherActor == Cast<AActor>(PlayerCharacter))
	{
		AsEndlessRunnerGameMode->FloorSpawner(true);
		Destroy();
	}
}

