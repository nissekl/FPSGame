// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"
class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState: uint8
{
	Idle,

	Suspicious,

	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category="Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FRotator OriginalRotation;

	FTimerHandle TimerHandle_ResetOrientation;
	UFUNCTION()
	void ResetOrientation();

	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
	EAIState GuardState;
	
	UFUNCTION()
	void OnRep_GuardState();

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChange(EAIState NewState);

	UPROPERTY(EditDefaultsOnly, Category="Sounds1")
	USoundBase* MissionFailedSound;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



protected:
	//Challenge Code
	UPROPERTY(EditInstanceOnly, Category="AI")
	bool bPatrol;

	UPROPERTY(EditInstanceOnly, Category="AI", meta=(EditCondition="bPatrol"))
	TArray<AActor*> PatrolPoints;

	int PatrolIndex=0; 
	AActor* CurrentPatrolPoint;

	void MoveToNextPatrolPoint();
};
