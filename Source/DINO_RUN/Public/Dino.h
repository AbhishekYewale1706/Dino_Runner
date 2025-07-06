// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Dino.generated.h"

/**
 * 
 */
UCLASS()
class DINO_RUN_API ADino : public APaperCharacter
{
	GENERATED_BODY()
	
public:
       ADino();
       //Variables
       UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomVariables")
       float DamageAmount;
       
       UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomVariables")
       float Health;

       UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomVariables")
       bool IsDead;

       UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomVariables")
       bool GotHit;

       UPROPERTY(EditDefaultsOnly, Category = "Animations")
       UPaperFlipbook* RedDinoJump;

       UPROPERTY(EditDefaultsOnly, Category = "Animations")
       UPaperFlipbook* RedDinoHit;

       UPROPERTY(EditDefaultsOnly, Category = "Animations")
       UPaperFlipbook* RedDinoRun;

       FTimerHandle SpeedIncreaseTimerHandle;
       FTimerHandle GotHitResetTimerHandle;
       
       UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed")
       float SpeedIncrement = 10.f;
       
       UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed")
       float MaxSpeed = 600.f;
       
       UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed")
       float SpeedIncreaseTime = 5.f;

       UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed")
       bool BigMode=false;
       UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed")
       bool UseBigMode=false;
    
       
protected:
       virtual void BeginPlay() override;
public:
       virtual void Tick(float DeltaTime) override;
      //Function
       UFUNCTION(BlueprintCallable, Category="Custom")
       void Sliding();
       UFUNCTION(BlueprintCallable, Category="Custom")
       void Jumping();
       UFUNCTION(BlueprintCallable)
       void SpeedIncrease();
       UFUNCTION(BlueprintCallable)
       void Hit();
       UFUNCTION(BlueprintCallable)
       void ResetGoHit();
     
};
