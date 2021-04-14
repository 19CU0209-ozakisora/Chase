// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
	: m_proot_(NULL)
	, actionend_(false)
	, is_rotation_(true)
	, player_rotation_ (0.f)
	, debugmode_(false)
	//, m_pplayermesh_(NULL)
	, input_rotation_scale_(0.f)
	, speed_scale_(0.f)
	, m_parrow_(NULL)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_proot_ = CreateDefaultSubobject<USceneComponent>(TEXT("m_proot_"));
	m_proot_ = RootComponent;
	
	//m_pplayermesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_->SetupAttachment(m_proot_);

	m_parrow_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_parrow_"));
	m_parrow_->SetupAttachment(m_pplayermesh_);

	//m_parrow_->OnComponentHit.AddDynamic(this, &APlayerCharacter::ComponentHit);
	//(this, &APlayerCharacter::ComponentHit);
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
		
	if (!is_rotation_ && !hit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Move"), player_rotation_));
		AddMovementInput(Cast<USceneComponent>(m_pplayermesh_)->GetForwardVector(), speed_scale_);
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
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("not input"), player_rotation_));
		return;
	}

	player_rotation_ += (_axisval * input_rotation_scale_);
	Cast<USceneComponent>(m_pplayermesh_)->SetWorldRotation(FRotator(0.f, player_rotation_, 0.f));
	UE_LOG(LogTemp, Warning, TEXT("%f"), player_rotation_);

	if (debugmode_)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Rotation input"), player_rotation_));
	}
}

void APlayerCharacter::DeleteArrow()
{
	// 条件式の中に本来は入れる
	is_rotation_ = false;
	if (m_parrow_ != NULL)
	{
		Cast<USceneComponent>(m_parrow_)->DestroyComponent();
	}
}

// カプセルコンポーネントを参照している為同じものをBPに追加

void APlayerCharacter::ComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Stone"))
	{
		if (debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Stone Hit"), player_rotation_));
		}
		speed_scale_ = 0.f;
	}
}