// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
//#include <iostream>

// Sets default values
AMyActor::AMyActor() : vMoveHistory{ FVector2D(0, 0) }, iEventCnt{ 0 }
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	// 스태틱 메시 불러오기
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/diamond/source/diamond.diamond"));
	if (!MeshAsset.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("gem_emerald: Mesh failed to load."));
		return;
	}

	StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	UE_LOG(LogTemp, Log, TEXT("gem_emerald: Mesh loaded successfully."));

	StaticMeshComponent->SetWorldScale3D(FVector(50.f, 50.f, 50.f));

	// 머터리얼 불러오기
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialInstance(TEXT("/Game/diamond/material/gem_emerald.gem_emerald"));
	if (!MaterialInstance.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("gem_emerald: Material failed to load."));
		return;
	}

	StaticMeshComponent->SetMaterial(0, MaterialInstance.Object);

}

void AMyActor::Step()
{
	FVector CurrentLocation = GetActorLocation();

	float Speed = 30.f;

	double xDiff = FMath::RandRange(-1, 1);
	double yDiff = FMath::RandRange(-1, 1);

	FVector NewLocation = FVector(CurrentLocation.X + xDiff, CurrentLocation.Y + yDiff, CurrentLocation.Z);
	SetActorLocation(NewLocation);
}

float AMyActor::getDistance(int iHistoryIdx) {
	float result = 0;

	FVector2D currentLocation = FVector2D(GetActorLocation().X, GetActorLocation().Y);
	FVector2D historyLocation = vMoveHistory[iHistoryIdx];

	result = FVector2D::Distance(currentLocation, historyLocation);

	return result;
}

void AMyActor::Move() {
	for (int i = 0; i < 10; i++)
	{
		Step();
		FVector CurrentLocation = GetActorLocation();
		UE_LOG(LogTemp, Log, TEXT("gem_emerald: New Location: %f %f"), CurrentLocation.X, CurrentLocation.Y);
		UE_LOG(LogTemp, Log, TEXT("gem_emerald: Distance from previous location: %f"), getDistance(vMoveHistory.Num() - 1));

		vMoveHistory.Add(FVector2D(CurrentLocation.X, CurrentLocation.Y));

		bool bEventOccured = bool(FMath::RandRange(0, 1));
		if (bEventOccured)
		{
			iEventCnt++;
			TriggerCustomEvent();
		}
		//std::cout << '\n';

		UE_LOG(LogTemp, Log, TEXT("\n"));
	}

	UE_LOG(LogTemp, Log, TEXT("gem_emerald: Total number of events: %d"), iEventCnt);
	UE_LOG(LogTemp, Log, TEXT("gem_emerald: Total moved distance : % f"), getDistance(0));
}



// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Step();

}

void AMyActor::TriggerCustomEvent()
{
	UE_LOG(LogTemp, Log, TEXT("gem_emerald: Custom event triggered!"));
	OnCustomEvent.Broadcast();
}