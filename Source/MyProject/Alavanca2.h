// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Alavanca2.generated.h"

UCLASS()
class MYPROJECT_API AAlavanca2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlavanca2();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void OnPressed2();


private:

	UStaticMeshComponent* MeshComp;
	
};
