// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "PersonagemMovimentando.h"


// Sets default values
APersonagemMovimentando::APersonagemMovimentando()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APersonagemMovimentando::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APersonagemMovimentando::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

