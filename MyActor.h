// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyCustomEvent);

UCLASS()
class CPPPROJECT_API AMyActor : public AActor
{
	GENERATED_BODY()

private:
	TArray<FVector2D> vMoveHistory;
	int iEventCnt;
	void Step();

protected:
	UStaticMeshComponent* StaticMeshComponent;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AMyActor();
	float getDistance(int iHistoryIdx);

	void Move();
	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Custom event declaration

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FMyCustomEvent OnCustomEvent;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerCustomEvent();
};
