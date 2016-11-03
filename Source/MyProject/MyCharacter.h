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
	
	//FORCEINLINE int GetNewLife() const { return Life; }
	//FORCEINLINE void AMyCharacter::SetNewLife(int NewLife) { Life = NewLife; }
	FORCEINLINE TArray<class AItem*> GetInventory() const { return Inventory; }
	FORCEINLINE TArray<class AObjeto*> GetColetavel() const { return Coletavel; }

	void OnDeath();


	void RotacionarEmZ(float eixoHorizontal);
	void RotacionarEmX(float eixoVertical);
	
	virtual void Jump() override;

	virtual void Crouch(bool bClientSimulation = true) override;

	void StartCrouch();
	void StopCrouch();

//	void OnDeath();

	
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
	int Life = 3;

	USphereComponent* CollectCollisionComp;
	USphereComponent* CollectCollisionComp2;

	TArray<class AItem*> Inventory;
	TArray<class AObjeto*> Coletavel;

	TSubclassOf<class UUserWidget> UserWidget;

	USoundCue* FireSound;
	USoundCue* Chave1;

	UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere)
		UAnimSequence* JumpAnim;

	UPROPERTY(EditAnywhere)
		UAnimSequence* JumpAnim2;

	void MoveForward(float value);
	void MoveRight(float Value);
	
	void StartRun();
	void StopRun();
	void DropProjectActor();
	void Turn(float Value);
	void OnCollect();
	void OnCollect2();
	void PressChave2();
	void PontoFinal();

	void Pause();


	float DamageAmount = 1.0f;


	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult &Hit);



	//UFUNCTION()
	//	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
