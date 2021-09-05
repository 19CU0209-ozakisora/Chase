// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_proot_ = CreateDefaultSubobject<USceneComponent>(TEXT("m_proot_"));
	RootComponent = m_proot_;

	m_pdoor_mesh_right_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pdoor_mesh_right_"));
	m_pdoor_mesh_right_->SetupAttachment(RootComponent);

	m_pdoor_mesh_left_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pdoor_mesh_left_"));
	m_pdoor_mesh_left_->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

