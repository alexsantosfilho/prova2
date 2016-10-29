// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PersonagemMovimentando.generated.h"

UCLASS()
class MYPROJECT_API APersonagemMovimentando : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APersonagemMovimentando();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
