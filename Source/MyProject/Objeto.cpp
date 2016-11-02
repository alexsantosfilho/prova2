// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Objeto.h"
#include "MyCharacter.h"



// Sets default values
AObjeto::AObjeto()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject
		<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(true);
	MeshComp->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AObjeto::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjeto::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

int AObjeto::Use2() {
	UE_LOG(LogTemp, Warning, TEXT("Use!"));
	return 0;
}

