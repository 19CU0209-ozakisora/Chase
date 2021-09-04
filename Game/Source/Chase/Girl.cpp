// Fill out your copyright notice in the Description page of Project Settings.


#include "Girl.h"

// Sets default values
AGirl::AGirl()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pgirl_mesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_pgirl_mesh_"));
	RootComponent = m_pgirl_mesh_;

	/*
	m_pbucket_mesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_pbucket_mesh_"));
	m_pbucket_mesh_->SetupAttachment(m_pbucket_mesh_);
	*/
}

// Called when the game starts or when spawned
void AGirl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGirl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGirl::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

