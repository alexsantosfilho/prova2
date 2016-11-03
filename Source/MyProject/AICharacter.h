// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class MYPROJECT_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* Behavior;

	void SetColetavelLife2(int NewColetavelLife2);
	int GetColetavelLife2();
	
	virtual void OnDeath2();

private:

	UPROPERTY(VisibleAnywhere, Category = Tick)
		float RunningTime;
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	float DamageAmount = 1.0f;

	int ColetavelLife2 = 3;


	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};