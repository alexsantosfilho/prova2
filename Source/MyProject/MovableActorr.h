// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MovableActorr.generated.h"

UCLASS()
class MYPROJECT_API AMovableActorr : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovableActorr();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:
	UPROPERTY(EditAnyWhere)
		UShapeComponent* Root;

	UPROPERTY(EditAnyWhere)
		UStaticMeshComponent*MeshComp;

	
};
