// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "ProjectActor.h"
#include "AICharacter.h"
#include "MyCharacter.h"

// Sets default values
AProjectActor::AProjectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	RootComponent = Root;

	Root->OnComponentBeginOverlap.AddDynamic(this, &AProjectActor::OnOverlapBegin);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -30.0f));
	MeshComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	MeshComp->AttachTo(RootComponent);


	Particle = CreateDefaultSubobject<UParticleSystemComponent>
		(TEXT("Particle"));
	Particle->bAutoActivate = true;
	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		ParticleSystem(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));

	if (ParticleSystem.Succeeded()) {
		Particle->SetTemplate(ParticleSystem.Object);
	
	}
	Particle->SetupAttachment(RootComponent);

	ProjecttileMovement = CreateDefaultSubobject <UProjectileMovementComponent>(TEXT("ProjecttileMovement"));
	ProjecttileMovement->UpdatedComponent = Root;
	ProjecttileMovement->InitialSpeed = 3000.0f;
	ProjecttileMovement->MaxSpeed = 3000.0f;

	InitialLifeSpan = 5.0f;


}

// Called when the game starts or when spawned
void AProjectActor::BeginPlay()
{
	Super::BeginPlay();

	DefaultZ = GetActorLocation().Z;

	
}

// Called every frame
void AProjectActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector Location = GetActorLocation();
	Location.Z = DefaultZ;
	SetActorLocation(Location);

}

void AProjectActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {




	if ((OtherActor != nullptr) && (OtherActor != this) &&
		(OtherComp != nullptr) && (OtherActor->IsA(AAICharacter::StaticClass()))) {
		
		AAICharacter* MyCharacter = Cast<AAICharacter>(OtherActor);
		MyCharacter->SetColetavelLife2(MyCharacter->GetColetavelLife2() - DamageAmount); // DANO NO PERSONAGEM
		MyCharacter->OnDeath2();
		//	MyProject2Character->OnDeath3();


		UE_LOG(LogTemp, Warning, TEXT("bala colidio com o personagem"));

	}

}