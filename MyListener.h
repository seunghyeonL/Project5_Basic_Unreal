// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyListener.generated.h"

UCLASS()
class CPPPROJECT_API AMyListener : public AActor
{
	GENERATED_BODY()
	
private:
	UStaticMeshComponent* StaticMeshComponent;
	bool bActorFound;

public:	
	// Sets default values for this actor's properties
	AMyListener();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void HandleCustomEvent();

};
