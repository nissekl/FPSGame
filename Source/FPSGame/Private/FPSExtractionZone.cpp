// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp-> SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp-> SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp-> SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	OverlapComp-> SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	OverlapComp->SetHiddenInGame(false);
	OverlapComp-> OnComponentBeginOverlap.AddDynamic(this,&AFPSExtractionZone::HandleOverlap);

	DecalComp = CreateAbstractDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp-> DecalSize=FVector(200.0f,200.0f,200.0f);
	DecalComp-> SetupAttachment(RootComponent);
}



void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	

	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
	if (MyPawn == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("nullptr"));
		return;
	}

	if(MyPawn->bIsCarryingObjective)
	{
		AFPSGameMode *GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{
			GM->CompleteMission(MyPawn,true);
			UGameplayStatics::PlaySound2D(this,MissionCompletedSound);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this,ObjectiveMissingSound);
	}
	UE_LOG(LogTemp, Log, TEXT("Overlapped with Extraction Zone"));


}



