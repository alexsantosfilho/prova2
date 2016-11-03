// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "AICharacter.h"
#include "MyAIController.h"
#include "ProjectActor.h"
#include "MyCharacter.h"
#include "InimigoC.h"
#include "Item.h"




// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ConstructorHelpers::FObjectFinder<USkeletalMesh>SkeletalMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	GetMesh()->SetWorldLocation(FVector(0.0f, 0.0f, -10.0f));
	GetMesh()->SetWorldScale3D(FVector(1.f, 1.f, 1.f));

	
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



	RunningTime += DeltaTime;
	float ShootTime = 1.f * RunningTime;
	if (ShootTime > 3.5f) {
		FActorSpawnParameters SpawnParameters;
		UWorld* World = GetWorld();
		if (World != nullptr) {  // add dano do personagem sem o inimigo c
			FRotator Rotation = MeshComp->GetComponentRotation();
			AInimigoC* Proj = World->SpawnActor<AInimigoC>
				(GetActorLocation(), Rotation, SpawnParameters);
			if (Proj != nullptr) {

				RunningTime = 0.2f;
			}

		}

	}
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}



void AAICharacter::SetColetavelLife2(int NewColetavelLife2) {
	ColetavelLife2 = NewColetavelLife2;

}
int AAICharacter::GetColetavelLife2() {
	return ColetavelLife2;
}

void AAICharacter::OnDeath2() {
	
	FActorSpawnParameters SpawnParameters;
	UWorld* World = GetWorld();
	if (ColetavelLife2 <= 0 ) {
		ColetavelLife2;
		Destroy();
		
	
		UE_LOG(LogTemp, Warning, TEXT("inimigo morreu!"));
	
	}
	if (ColetavelLife2 <= 9) {

		ColetavelLife2;
		FVector InitialLocation(-7823.0f, -1839.0f, 20.0f);
		SetActorLocation(InitialLocation);
		FRotator Rotation = GetMesh()->GetComponentRotation();
		AItem* Proj = World->SpawnActor<AItem>
			(GetActorLocation(), Rotation,
				SpawnParameters);
	}


}

void AAICharacter::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{

	if (OtherActor != nullptr &&
		OtherActor->IsA(AMyCharacter::StaticClass()) &&
		OtherComp != nullptr) {

		UE_LOG(LogTemp, Warning, TEXT("Encostou"));
	}
}
