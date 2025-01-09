// Fill out your copyright notice in the Description page of Project Settings.


#include "MyListener.h"
#include "MyActor.h"

// Sets default values
AMyListener::AMyListener() : bActorFound{ false }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	// import static mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/diamond/source/diamond.diamond"));
	if (!MeshAsset.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("gem_ruby: Mesh failed to load."));
		return;
	}

	StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	UE_LOG(LogTemp, Log, TEXT("gem_ruby: Mesh loaded successfully."));

	StaticMeshComponent->SetWorldScale3D(FVector(50.f, 50.f, 50.f));

	// import material
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialInstance(TEXT("/Game/diamond/material/gem_ruby.gem_ruby"));
	if (!MaterialInstance.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("gem_ruby: Material failed to load."));
		return;
	}

	StaticMeshComponent->SetMaterial(0, MaterialInstance.Object);
}

// Called when the game starts or when spawned
void AMyListener::BeginPlay()
{
	Super::BeginPlay();
	
	

}

// Called every frame
void AMyListener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bActorFound == false)
	{
		AMyActor* MyActor = Cast<AMyActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyActor::StaticClass()));
		if (MyActor)
		{
			bActorFound = true;
			UE_LOG(LogTemp, Log, TEXT("gem_ruby: MyActor found!"));
			MyActor->OnCustomEvent.AddDynamic(this, &AMyListener::HandleCustomEvent);
			MyActor->Move();
		}
	}
}
	

// Custom event handler
void AMyListener::HandleCustomEvent()
{
	UE_LOG(LogTemp, Log, TEXT("gem_ruby: Custom event received!"));
}