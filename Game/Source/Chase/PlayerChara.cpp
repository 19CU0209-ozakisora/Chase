// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChara.h"

// Sets default values
APlayerChara::APlayerChara()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_pcamera_ = CreateDefaultSubobject<USceneComponent>(TEXT("Camera"));

	acceleration_val_ = 1.05f;
	max_acceleration_val_ = 1.05f;
}

// Called when the game starts or when spawned
void APlayerChara::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerChara::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector a = GetActorLocation();
	if (is_accelerator_)
	{
		acceleration_val_ *= 1.05f;
		now_acceleration_ = acceleration_val_;
		a.X += now_acceleration_;

		SetActorLocation(a);
		//UE_LOG(LogTemp, Warning, TEXT("%f"), move_input_.X);
		
	}
	else
	{
		now_acceleration_ = max_acceleration_val_;
	}
}

// Called to bind functionality to input
void APlayerChara::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Accelerator", IE_Pressed, this, &APlayerChara::SwitchAccelerator);
	InputComponent->BindAction("Accelerator", IE_Released, this, &APlayerChara::SwitchAccelerator);
}

void APlayerChara::SwitchAccelerator()
{
	is_accelerator_ = !is_accelerator_;
}

