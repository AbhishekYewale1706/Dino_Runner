// Fill out your copyright notice in the Description page of Project Settings.


#include "Dino.h"
#include "GameFramework/CharacterMovementComponent.h"


ADino::ADino()
{
	
	PrimaryActorTick.bCanEverTick = true;
	Health=5;
	IsDead = false;
	GotHit=false;
	DamageAmount=1;
}

void ADino::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
	SpeedIncreaseTimerHandle,
	this,
	&ADino::SpeedIncrease,
	SpeedIncreaseTime,
	true, 
	0.0f  
	);
}

void ADino::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Direction = GetActorForwardVector();
	AddMovementInput(Direction, 1.0f, false);
	if (UseBigMode==false)
	{
		if (GetCharacterMovement()->IsFalling())
		{
			if (GotHit && RedDinoHit)
			{
				GetSprite()->SetFlipbook(RedDinoHit);
			}
			else if (RedDinoJump)
			{
				GetSprite()->SetFlipbook(RedDinoJump);
			}
		}
		else
		{
			if (GotHit && RedDinoHit)
			{
				GetSprite()->SetFlipbook(RedDinoHit);
			}
			else if (RedDinoRun)
			{
				GetSprite()->SetFlipbook(RedDinoRun);
			}
		}
	}
	
}

void ADino::Sliding()
{
	FVector LaunchVelocity = FVector(0.0f, 0.0f, -600.0f);
	bool bXYOverride = false;
	bool bZOverride = false;
	LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);
}

void ADino::Jumping()
{
	Jump();
}

void ADino::SpeedIncrease()
{
	if (UCharacterMovementComponent* CharacterMovementRef = GetCharacterMovement())
	{
		float CurrentSpeed = CharacterMovementRef->MaxWalkSpeed;
		float NewSpeed = FMath::Clamp(CurrentSpeed + SpeedIncrement, 0.0f, MaxSpeed);
		CharacterMovementRef->MaxWalkSpeed = NewSpeed;
		
	}
}

void ADino::Hit()
{
	if (UseBigMode==false)
	{
		if (Health > 1.0f)
		{
			Health = FMath::Clamp(Health - DamageAmount, 0.0f, Health);
			GotHit = true;
			GetWorldTimerManager().SetTimer(GotHitResetTimerHandle, this, &ADino::ResetGoHit, 0.2f, false);
		
		}   
		else
		{
			IsDead = true;
		
		}
	}
}

void ADino::ResetGoHit()
{
	GotHit = false;
}


