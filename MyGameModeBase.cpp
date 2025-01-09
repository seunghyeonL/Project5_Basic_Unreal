// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyActor.h"
#include "MyListener.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	FVector SpawnLocation1 = FVector(0.f, 0.f, 100.f);
	FVector SpawnLocation2 = FVector(0.f, 200.f, 100.f);
	FRotator SpawnRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;

	GetWorld()->SpawnActor<AMyListener>(AMyListener::StaticClass(), SpawnLocation2, SpawnRotation, SpawnParams);
	GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), SpawnLocation1, SpawnRotation, SpawnParams);
	

}