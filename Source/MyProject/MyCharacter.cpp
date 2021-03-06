// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyCharacter.h"
#include "ProjectActor.h"
#include "Item.h"
#include "Objeto.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Alavanca.h"
#include "Alavanca2.h"
#include "PontoFinal.h"
#include "AICharacter.h"



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

	CollectCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollectCollision"));
	CollectCollisionComp->InitSphereRadius(200.0f);
	CollectCollisionComp->AttachTo(RootComponent);

	GetCharacterMovement()->MaxWalkSpeed = 400;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetMesh()->OnComponentHit.AddDynamic(this, &AMyCharacter::OnHit);


	ConstructorHelpers::FClassFinder<UUserWidget>
		Widget(TEXT("WidgetBlueprint'/Game/Blueprints/Pause.Pause_C'"));
	if (Widget.Succeeded()) {
		UserWidget = Widget.Class;
	}

	ConstructorHelpers::FObjectFinder<USoundCue>
		SoundCue(TEXT("SoundCue'/Game/Audios/shoot_Cue.shoot_Cue'"));
	if (SoundCue.Succeeded()) {
		FireSound = SoundCue.Object;
	}


	ConstructorHelpers::FObjectFinder<USoundCue>
		Chave1c(TEXT("SoundCue'/Game/Audios/footstep-exemplo-1_Cue.footstep-exemplo-1_Cue'"));
	if (Chave1c.Succeeded()) {
		Chave1 = Chave1c.Object;
	}
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SkeletalMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<UAnimSequence>
		AnimJumpLoad(TEXT("AnimSequence'/Game/AnimStarterPack/Jump_From_Stand.Jump_From_Stand'"));
	if (AnimJumpLoad.Succeeded()) {
		JumpAnim = AnimJumpLoad.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimSequence>
		AnimJumpLoad2(TEXT("AnimSequence'/Game/AnimStarterPack/Crouch_Idle_Rifle_Ironsights.Crouch_Idle_Rifle_Ironsights'"));
	if (AnimJumpLoad2.Succeeded()) {
		JumpAnim2 = AnimJumpLoad2.Object;
	}
	
	AudioComp = CreateDefaultSubobject<UAudioComponent>
		(TEXT("AudioComp"));
	AudioComp->bAutoActivate = false;
	AudioComp->AttachTo(GetMesh());

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

	if (GetMesh()->GetAnimationMode() == EAnimationMode::AnimationSingleNode
		&& GetCharacterMovement()->IsMovingOnGround() && CanCrouch()== true)   { 
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	}

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

	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Crouch", IE_Pressed, this, &AMyCharacter::StartCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AMyCharacter::StopCrouch);

	InputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRun);

	InputComponent->BindAction("Drop", IE_Pressed, this, &AMyCharacter::DropProjectActor);
	InputComponent->BindAction("Collect", IE_Pressed, this, &AMyCharacter::OnCollect);
	InputComponent->BindAction("Collect2", IE_Pressed, this, &AMyCharacter::OnCollect2);
	InputComponent->BindAction("PressChave2", IE_Pressed, this, &AMyCharacter::PressChave2);
	InputComponent->BindAction("PontoFinal", IE_Pressed, this, &AMyCharacter::PontoFinal);



	InputComponent->BindAction("Pause", IE_Pressed, this, &AMyCharacter::Pause);

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



void AMyCharacter::DropProjectActor() {

	FActorSpawnParameters SpawnParameters;
	UWorld* World = GetWorld();

	if (World != nullptr) {
		FRotator Rotator = MeshComp->GetComponentRotation();
		AProjectActor* proj = World->SpawnActor<AProjectActor>(GetActorLocation(), Rotator, SpawnParameters);
		if (proj != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Span ok!"));
			AudioComp->SetSound(FireSound);
			AudioComp->Play();
		}
	}

}

void AMyCharacter::Turn(float Value) {

	//AddControllerYawInput(Value);
	FRotator NewRotation = MeshComp->GetComponentRotation();
	NewRotation.Yaw += Value;
	MeshComp->SetWorldRotation(NewRotation);

}

void AMyCharacter::OnCollect() {

	TArray<AActor*> AtoresColetados;
	CollectCollisionComp->GetOverlappingActors(AtoresColetados);

	for (int i = 0; i < AtoresColetados.Num(); i++) {
		if (AtoresColetados[i]->IsA(AItem::StaticClass())) {
			AItem* ItemColetado = Cast<AItem>(AtoresColetados[i]);
			Inventory.Add(ItemColetado);
			ItemColetado->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("%d"), Inventory.Num());
			AudioComp->SetSound(Chave1);
			AudioComp->Play();
		}
		else if (AtoresColetados[i]->IsA(AAlavanca::StaticClass())) {
			AAlavanca* Alavanca = Cast<AAlavanca>(AtoresColetados[i]);
			Alavanca->OnPressed();
			AudioComp->SetSound(Chave1);
			AudioComp->Play();
		
		}
	}
}

void AMyCharacter::PressChave2() {
	
	TArray<AActor*> AtoresColetados;
	CollectCollisionComp->GetOverlappingActors(AtoresColetados);
	
	for (int i = 0; i < AtoresColetados.Num(); i++) {
		if (AtoresColetados[i]->IsA(AAlavanca2::StaticClass())) {
			AAlavanca2* Alavanca2 = Cast<AAlavanca2>(AtoresColetados[i]);
			Alavanca2->OnPressed2();
			AudioComp->SetSound(Chave1);
			AudioComp->Play();
		}
	}
}

void AMyCharacter::PontoFinal() {

	TArray<AActor*> AtoresColetados;
	CollectCollisionComp->GetOverlappingActors(AtoresColetados);

	for (int i = 0; i < AtoresColetados.Num(); i++) {
		if (AtoresColetados[i]->IsA(APontoFinal::StaticClass())) {
			APontoFinal* PontoFinal = Cast<APontoFinal>(AtoresColetados[i]);
			PontoFinal->OnPressed3();
			AudioComp->SetSound(Chave1);
			AudioComp->Play();
		}
	}
}
void AMyCharacter::OnCollect2() {

	TArray<AActor*> Coletavelb;
	CollectCollisionComp->GetOverlappingActors(Coletavelb);
//	UE_LOG(LogTemp, Warning, TEXT("OnCollect2"));
		for (int i = 0; i < Coletavelb.Num(); i++) {
			//UE_LOG(LogTemp, Warning, TEXT("OnCollect2"));
		if (Coletavelb[i]->IsA(AObjeto::StaticClass())) {
			UE_LOG(LogTemp, Warning, TEXT("OnCollect2"));
			AObjeto* ObColetado = Cast<AObjeto>(Coletavelb[i]);
			Coletavel.Add(ObColetado);
			ObColetado->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("%d"), Coletavel.Num());
			
			
		}
	
	}
}

void AMyCharacter::Pause() {

	UWorld* World = GetWorld();
	if (World != nullptr) {
		APlayerController* PlayerController =
			UGameplayStatics::GetPlayerController(World, 0);
		if (PlayerController != nullptr && UserWidget != NULL) {
			PlayerController->SetPause(true);
			UUserWidget* UserW =
				UWidgetBlueprintLibrary::Create
				(World, UserWidget, PlayerController);
			if (UserW != nullptr) {
				UserW->AddToViewport();
				PlayerController->bShowMouseCursor = true;
			}
		}
	}
}

void AMyCharacter::Jump() {

	Super::Jump();

	if (JumpAnim != nullptr) {
		GetMesh()->PlayAnimation(JumpAnim, false);
	}
}

void AMyCharacter::Crouch(bool bClientSimulation) {

	Super::Crouch();
	if (JumpAnim2 != nullptr) {
		GetMesh()->PlayAnimation(JumpAnim2, false);
	}
}

void AMyCharacter::StartCrouch()
{
	Crouch();
}

void AMyCharacter::StopCrouch()
{
	UnCrouch();

}

void AMyCharacter::OnDeath() {
	
	UWorld* World = GetWorld();

	if (Life <= 0) {
		Life;
		UE_LOG(LogTemp, Warning, TEXT("OnDeath no char"));
		UGameplayStatics::OpenLevel(World, "NewMap4");
	}
}

void AMyCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult &Hit) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->IsA(AAICharacter::StaticClass()))) {
		AAICharacter* AICharacter = Cast<AAICharacter>(OtherActor);
	
		UE_LOG(LogTemp, Warning, TEXT("OnHit"));

	}
}