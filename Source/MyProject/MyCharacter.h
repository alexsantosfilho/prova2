// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	float velocidadeDeRotacao;
	
	void SetLife(int NewLife);
	int GetLife();
	void OnDeath();


	void RotacionarEmZ(float eixoHorizontal);
	void RotacionarEmX(float eixoVertical);
	
	
private: 
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
		UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowComp;
	UPROPERTY(EditAnywhere)
	int Life = 100;



	void MoveForward(float value);
	void MoveRight(float Value);
	
	void StartRun();
	void StopRun();
	void DropProjectActor();
	void Turn(float Value);



	
};