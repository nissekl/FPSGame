// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "FPSPlayerController.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
/*    for(TActorIterator<APawn> It(GetWorld()); It; ++It)
    {
        APawn* Pawn = *It;
        if(Pawn && Pawn->IsLocallyControlled())
        {
            Pawn->DisableInput(nullptr);
        }
    }
*/
    for(FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It;++It)
    {
        AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
        //In the 2 player game. the sever will have 2 controller, 1 is host (local player controller) another is client
        if(PC && PC->IsLocalController())
        {
            PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

            APawn* MyPawn = PC->GetPawn();
            if(MyPawn)
            {
                MyPawn->DisableInput(nullptr);
            }
        }
    }
}