// Fill out your copyright notice in the Description page of Project Settings.


#include "Bucket.h"

// Sets default values
ABucket::ABucket()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pbucket_mesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_pbucket_mesh_"));
	RootComponent = m_pbucket_mesh_;

}

// Called when the game starts or when spawned
void ABucket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABucket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABucket::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

