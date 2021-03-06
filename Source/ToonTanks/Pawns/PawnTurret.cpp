// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

void APawnTurret::HandleDestruction() 
{
    Super::HandleDestruction();
    Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (PlayerPawn && ReturnDistanceToPlayer() <= FireRange)
    {
        RotateTurret(PlayerPawn->GetActorLocation());
    }
}

void APawnTurret::CheckFireCondition()
{
    if (!PlayerPawn)
    {
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("Player exist"));
    if (ReturnDistanceToPlayer() <= FireRange)
    {
        Fire();
    }
}

float APawnTurret::ReturnDistanceToPlayer()
{
    if (PlayerPawn)
    {
        return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
    }
    return 0.0f;
}
