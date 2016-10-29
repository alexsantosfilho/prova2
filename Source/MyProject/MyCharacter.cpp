// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyCharacter.h"
#include "ProjectActor.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->bGenerateOverlapEvents = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoColission");
	MeshComp->AttachTo(GetCapsuleComponent());

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraBoom = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	PlayerCamera->AttachTo(CameraBoom);

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetHiddenInGame(false);
	ArrowComp->ArrowSize = 2.0f;
	ArrowComp->AttachTo(MeshComp);


	GetCharacterMovement()->MaxWalkSpeed = 400;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &AMyCharacter::Turn);



	InputComponent->BindAxis("MouseX", this, &AMyCharacter::RotacionarEmZ);
	InputComponent->BindAxis("MouseY", this, &AMyCharacter::RotacionarEmX);


	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRun);

	InputComponent->BindAction("Drop", IE_Pressed, this, &AMyCharacter::DropProjectActor);

	 


}

void AMyCharacter::MoveForward(float value) {

	FVector Forward(1, 0, 0);
	AddMovementInput(Forward, value);




}
void AMyCharacter::MoveRight(float value) {

	FVector Right(0, 1, 0);
	AddMovementInput(Right, value);




}

void AMyCharacter::RotacionarEmZ(float eixoHorizontal) {
	FRotator rotAtual = GetActorRotation();
	FRotator eixoZ = FRotator::MakeFromEuler(FVector(0, 0, 1));
	SetActorRotation(rotAtual + (eixoZ * eixoHorizontal *velocidadeDeRotacao));
}

void AMyCharacter::RotacionarEmX(float eixoHorizontal) {
	FRotator rotAtual = GetActorRotation();
	FRotator eixoX = FRotator::MakeFromEuler(FVector(0, 1, 0));
	SetActorRotation(rotAtual + (eixoX * eixoHorizontal *velocidadeDeRotacao));
}



void AMyCharacter::StartRun() {
	GetCharacterMovement()->MaxWalkSpeed = 800;

}
void AMyCharacter::StopRun() {
	GetCharacterMovement()->MaxWalkSpeed = 400;

}

void AMyCharacter::SetLife(int NewLife) {
	Life = NewLife;

}
int AMyCharacter::GetLife() {
	return Life;
}

void AMyCharacter::OnDeath() {
	if (Life <= 0) {
		FVector InitialLocation(-60.0f, 30.0f, 350.0f);
		Life = 100;
		SetActorLocation(InitialLocation);
	}
}


void AMyCharacter::DropProjectActor() {

	FActorSpawnParameters SpawnParameters;
	UWorld* World = GetWorld();

	if (World != nullptr) {
		FRotator Rotator = MeshComp->GetComponentRotation();
		AProjectActor* proj = World->SpawnActor<AProjectActor>(GetActorLocation(), Rotator, SpawnParameters);
		if (proj != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Span ok!"));
		}
	}

}

void AMyCharacter::Turn(float Value) {
	//AddControllerYawInput(Value);
	FRotator NewRotation = MeshComp->GetComponentRotation();
	NewRotation.Yaw += Value;
	MeshComp->SetWorldRotation(NewRotation);


}