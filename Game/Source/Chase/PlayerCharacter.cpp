// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
	: m_proot_(NULL)
	, is_rotation_(true)
	, player_rotation_ (0.f)
	, debugmode_(false)
	, m_pplayermesh_(NULL)
	, input_rotation_scale_(0.f)
	, m_parrow_(NULL)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_proot_ = CreateDefaultSubobject<USceneComponent>(TEXT("m_proot_"));
	m_proot_ = RootComponent;

	m_pplayermesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_->SetupAttachment(RootComponent);

	m_parrow_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_parrow_"));
	m_parrow_->SetupAttachment(RootComponent);
	//m_parrow_->SetupAttachment(Cast<USceneComponent>(m_pplayermesh_));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!is_rotation_)
	{
		AddMovementInput(Cast<USceneComponent>(m_pplayermesh_)->GetForwardVector(), 10);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("TurnRate", this, &APlayerCharacter::PlayerRotation);
	InputComponent->BindAction("Decide", EInputEvent::IE_Pressed,this, &APlayerCharacter::DeleteArrow);
}

void APlayerCharacter::PlayerRotation(const float _axisval)
{
	if (_axisval == 0.f || !is_rotation_)
	{
		return;
	}
	
	player_rotation_ += (_axisval * input_rotation_scale_);
	Cast<USceneComponent>(m_pplayermesh_) ->SetWorldRotation(FRotator(0.f, player_rotation_, 0.f));

	if (debugmode_)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Rotation input"), player_rotation_));
	}
}

void APlayerCharacter::DeleteArrow()
{
	// èåèéÆÇÃíÜÇ…ñ{óàÇÕì¸ÇÍÇÈ
	is_rotation_ = false;
	if (m_parrow_ != NULL)
	{
		Cast<USceneComponent>(m_parrow_)->DestroyComponent();
	}
}

