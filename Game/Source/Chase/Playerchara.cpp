// Fill out your copyright notice in the Description page of Project Settings.


#include "Playerchara.h"

// Sets default values
APlayerchara::APlayerchara()
	: player_number_(1)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	chair_spawner_ = CreateDefaultSubobject<USceneComponent>(TEXT("chair_spawner_"));

}

// Called when the game starts or when spawned
void APlayerchara::BeginPlay()
{
	Super::BeginPlay();

	/* ‚±‚ñ‚ÈŠ´‚¶‚Å‚â‚è‚½‚©‚Á‚½
	FName tagname = "Player" + player_number_;
	Tags.Add(tagname); */
}

// Called every frame
void APlayerchara::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerchara::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}