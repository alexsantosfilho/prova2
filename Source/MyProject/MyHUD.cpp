// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyHUD.h"
#include "Engine/Font.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"

AMyHUD::AMyHUD() {
	static ConstructorHelpers::FObjectFinder<UFont>
		Font(TEXT("Font'/Engine/EngineFonts/RobotoDistanceField.RobotoDistanceField'"));
	if (Font.Succeeded()) {
		HUDFont = Font.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		Texture(TEXT("Texture2D'/Game/Green_Texture.Green_Texture'"));
	if (Texture.Succeeded()) {
		MyTexture = Texture.Object;
	}
	ConstructorHelpers::FObjectFinder<UTexture2D>
		PotionTexture(TEXT("Texture2D'/Game/Textures/potion.potion'"));
	if (PotionTexture.Succeeded()) {
		Potion = PotionTexture.Object;
	}
}

void AMyHUD::DrawHUD() {
	Super::DrawHUD();

	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX,
		Canvas->SizeY);

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(
		UGameplayStatics::GetPlayerPawn(this, 0));
/*
	FString LifeString = FString::Printf(TEXT("Life: %d"),
		MyCharacter->GetLife());
	DrawText(LifeString, FColor::Red, 50, 50, HUDFont);

	FString PotionAmount = FString::Printf(TEXT("Chave: %d"), MyCharacter->GetInventory().Num());
	DrawText(PotionAmount, FColor::Green, 50, 100, HUDFont);


	FString PotionAmount2 = FString::Printf(TEXT("Obejeto: %d"), MyCharacter->GetColetavel().Num());
	DrawText(PotionAmount2, FColor::Blue, 50, 150, HUDFont);


		*/
	
}

