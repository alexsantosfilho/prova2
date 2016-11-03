// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "AICharacter.h"
#include "MyAIController.h"
#include "ProjectActor.h"
#include "MyCharacter.h"



// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//MeshComp->AttachTo(GetCapsuleComponent());
	GetMesh()->SetWorldLocation(FVector(0.0f, 0.0f, -10.0f));
	GetMesh()->SetWorldScale3D(FVector(1.f, 1.f, 1.f));

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::OnOverlapBegin);

	//GetCapsuleComponent()->OnComponentBeginOverlap.
	
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AAICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AAICharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {


	//if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->IsA(AProjectActor::StaticClass()))) {
	//	AProjectActor* AICharacter = Cast<AProjectActor>(OtherActor);
	//	UE_LOG(LogTemp, Warning, TEXT("Destruiu o personagem inimigo!!!!!!"));

//	AICharacter->Destroy();
	//}

}

void AAICharacter::SetColetavelLife2(int NewColetavelLife2) {
	ColetavelLife2 = NewColetavelLife2;

}
int AAICharacter::GetColetavelLife2() {
	return ColetavelLife2;
}

void AAICharacter::OnDeath2() {

	if (ColetavelLife2 <= 0 ) {
		ColetavelLife2;
		Destroy();
		//
		UE_LOG(LogTemp, Warning, TEXT("inimigo perseu vida morreu!"));
		//AAIPatrolPoint* CurrentPoint = false;
		//	AAIPatrolController* AICon = false; // aquiii
		//	TimerManager2();
	}



}

void AAICharacter::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{

	if (OtherActor != nullptr &&
		OtherActor->IsA(AMyCharacter::StaticClass()) &&
		OtherComp != nullptr) {

		AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
		MyCharacter->SetLife(MyCharacter->GetLife() - DamageAmount);
		MyCharacter->OnDeath();
		//UE_LOG(LogTemp, Warning, TEXT("Life = %d"), MyProject2Character->GetColetavelLife());

		Destroy();

		UE_LOG(LogTemp, Warning, TEXT("Encostou"));
	}
}
