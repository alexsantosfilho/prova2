// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "InimigoC.h"
#include "MyCharacter.h"
#include "AICharacter.h"


// Sets default values
AInimigoC::AInimigoC()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("BlockAllDynamic");
	ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}
	MeshComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	MeshComp->OnComponentHit.AddDynamic(this, &AInimigoC::OnHit);
	MeshComp->AttachTo(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = Root;
	ProjectileMovement->InitialSpeed = 700.0f;
	ProjectileMovement->MaxSpeed = 900.0f;

}

// Called when the game starts or when spawned
void AInimigoC::BeginPlay()
{
	Super::BeginPlay();

	DefaultZ = GetActorLocation().Z;
}

// Called every frame
void AInimigoC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector Location = GetActorLocation();
	Location.Z = DefaultZ;
	SetActorLocation(Location);

	RunningTime += DeltaTime;
	float DestroyTime = 1.5f * RunningTime;
	if (DestroyTime > 2.f) {
		Destroy();
	}
}

void AInimigoC::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor != nullptr &&
		OtherActor->IsA(AMyCharacter::StaticClass()) &&
		OtherComp != nullptr) {

		AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
		MyCharacter->SetLife(MyCharacter->GetLife() - DamageAmount);
		MyCharacter->OnDeath();
		Destroy();

		UE_LOG(LogTemp, Warning, TEXT("Encostou"));
	}
}
