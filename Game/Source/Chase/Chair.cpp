// Fill out your copyright notice in the Description page of Project Settings.


#include "Chair.h"

// Sets default values
AChair::AChair()
	: m_proot_(NULL)
	, player_rotation_(0.f)
	, debugmode_(false)
	, m_pplayermesh_(NULL)
	, input_rotation_scale_(0.f)
	, speed_scale_(0.f)
	, m_parrow_(NULL)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ルートコンポーネントの設定
	//m_proot_ = CreateDefaultSubobject<USceneComponent>(TEXT("m_proot_"));
	//m_proot_ = RootComponent;

	// 椅子のメッシュの設定
	//m_pplayermesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_->SetupAttachment(RootComponent);

	// ガイドメッシュの設定
	m_parrow_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_parrow_"));
	m_parrow_->SetupAttachment(m_pplayermesh_);

	//m_parrow_->OnComponentHit.AddDynamic(this, &AChair::ComponentHit);
	//(this, &AChair::ComponentHit);
};

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 移動
	if (phase_ == EPhase::kMove)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Move"), player_rotation_));
		PlayerMove(DeltaTime);
	}
	else if (phase_ == EPhase::kRotation)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Rotation"), player_rotation_));
		PlayerRotation(DeltaTime);
	}
	else if (phase_ == EPhase::kSlip && !hit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Slip"), player_rotation_));
		PlayerSlip(DeltaTime);
	}
	else if (phase_ == EPhase::kEnd)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("End"), player_rotation_));
	}
}

// Called to bind functionality to input
void AChair::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("TurnRate", this, &AChair::SetInputValue);
	InputComponent->BindAction("Decide", EInputEvent::IE_Pressed, this, &AChair::NextPhase);
}

void AChair::SetInputValue(const float _axisval)
{
	if (debugmode_)
	{
		if (_axisval == 0.f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("not input TurnRate"), player_rotation_));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input TurnRate"), player_rotation_));
		}
	}

	input_value_ = _axisval;
}

void AChair::DeleteArrow()
{
	// 条件式の中に本来は入れる
	if (m_parrow_ != NULL)
	{
		Cast<USceneComponent>(m_parrow_)->DestroyComponent();
	}
}

// カプセルコンポーネントを参照している為同じものをBPに追加

void AChair::ComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Stone"))
	{
		if (debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Stone Hit"), player_rotation_));
		}
		slip_scale_ = 0.f;
	}
}

void AChair::NextPhase()
{
	if (phase_ == EPhase::kSlip)
	{
		return;
	}

	phase_cnt_++;
	phase_ = EPhase(phase_cnt_);

	if (phase_ == EPhase::kSlip)
	{
		DeleteArrow();
		return;
	}
}

void AChair::PlayerMove(const float _deltatime)
{
	FVector test = GetActorLocation();
	player_location += (input_value_ * speed_scale_) * _deltatime;
	test.Y = player_location;
	//Cast<USceneComponent>(m_pplayermesh_)->SetWorldLocation(FVector(0.f, player_location, 0.f));
	SetActorLocation(test);
	UE_LOG(LogTemp, Warning, TEXT("%f"), player_rotation_);
}

void AChair::PlayerRotation(const float _deltatime)
{
	player_rotation_ += (input_value_* input_rotation_scale_) * _deltatime;
	Cast<USceneComponent>(m_pplayermesh_)->SetWorldRotation(FRotator(0.f, player_rotation_, 0.f));
	UE_LOG(LogTemp, Warning, TEXT("%f"), player_rotation_);
}

void AChair::PlayerSlip(const float _deltatime)
{
	AddMovementInput(Cast<USceneComponent>(m_pplayermesh_)->GetForwardVector(), slip_scale_);
}