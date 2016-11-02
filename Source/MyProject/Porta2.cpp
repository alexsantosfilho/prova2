// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Porta2.h"


// Sets default values
APorta2::APorta2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshDoor(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Door.SM_Door'"));
	if (MeshDoor.Succeeded()) {
		Door->SetStaticMesh(MeshDoor.Object);
	}
	RootComponent = Door;
	StartYaw = Door->GetComponentRotation().Yaw + 180.0f;

}

// Called when the game starts or when spawned
void APorta2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APorta2::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	FRotator Rotation = Door->GetComponentRotation();

	if (Open && (Rotation.Yaw + 180.0f) + 1.0f < (StartYaw + 90.0f)) {
		Rotation.Yaw += 1.0f;
	}
	else if (!Open && (Rotation.Yaw + 180.0f) - 1.0f > StartYaw) {
		Rotation.Yaw -= 1.0f;
	}

	Door->SetWorldRotation(Rotation);

}

