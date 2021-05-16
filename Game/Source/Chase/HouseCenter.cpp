// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseCenter.h"

// Sets default values
AHouseCenter::AHouseCenter()
	: m_pcenter_mesh_(NULL)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pcenter_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pcenter_mesh_"));
	m_pcenter_mesh_->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHouseCenter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHouseCenter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

