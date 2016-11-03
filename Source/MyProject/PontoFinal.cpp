// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "PontoFinal.h"


// Sets default values
APontoFinal::APontoFinal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>
		AlavancaMesh(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	if (AlavancaMesh.Succeeded()) {
		MeshComp->SetStaticMesh(AlavancaMesh.Object);
	}
	ConstructorHelpers::FObjectFinder<UMaterial>
		Material(TEXT("Material'/Game/Material/DamageMaterial.DamageMaterial'"));
	if (Material.Succeeded()) {
		MeshComp->SetMaterial(0, Material.Object);
	}
	MeshComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	RootComponent = MeshComp;

	AudioComp = CreateDefaultSubobject<UAudioComponent>
		(TEXT("AudioComp"));
	AudioComp->bAutoActivate = false;
	

	ConstructorHelpers::FObjectFinder<USoundCue>
		Chave1c(TEXT("SoundCue'/Game/Audios/footstep-exemplo-1_Cue.footstep-exemplo-1_Cue'"));
	if (Chave1c.Succeeded()) {
		Chave1 = Chave1c.Object;
	}

}

// Called when the game starts or when spawned
void APontoFinal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APontoFinal::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void APontoFinal::OnPressed3() {
	UWorld* World = GetWorld();
	UGameplayStatics::OpenLevel(World, "NewMap5");
	AudioComp->SetSound(Chave1);
	AudioComp->Play();
}
