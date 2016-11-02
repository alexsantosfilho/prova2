// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Objeto.generated.h"

UCLASS()
class MYPROJECT_API AObjeto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjeto();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	FORCEINLINE UStaticMeshComponent* GetMeshComp()
		const {
		return MeshComp;
	}

	virtual int Use2();


private:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;
	
	
};