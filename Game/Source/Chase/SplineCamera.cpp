// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineCamera.h"

// Sets default values
ASplineCamera::ASplineCamera()
	: m_pcamera_(NULL)
	, m_pspring_arm_(NULL)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pspring_arm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("m_pspring_arm_"));
	m_pspring_arm_->SetupAttachment(RootComponent);

	m_pcamera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("m_pcamera_"));
	m_pcamera_->SetupAttachment(m_pspring_arm_);
}

// Called when the game starts or when spawned
void ASplineCamera::BeginPlay()
{
	Super::BeginPlay();

	m_prebphase_ = EPhase::kEnd;

	if (m_pspring_arm_ != NULL)
	{
		m_pspring_arm_->bEnableCameraLag = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("m_pspring_arm_ is NULL"));
	}
}

// Called every frame
void ASplineCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 現在の椅子の状態と直前の椅子状態が違う場合
	if (m_prebphase_ != m_pgamemanager_->m_chairs_[m_pgamemanager_->m_nowroundnum_ - 1]->GetPhase())
	{
		m_prebphase_ = m_pgamemanager_->m_chairs_[m_pgamemanager_->m_nowroundnum_ - 1]->GetPhase();
		for (int i = 0; i < m_change_direction_.Num(); ++i)
		{
			if (m_pgamemanager_->m_chairs_[m_pgamemanager_->m_nowroundnum_ - 1]->GetPhase() == m_change_direction_[i].phase_)
			{
				m_edirection_ = m_change_direction_[i].change_direction_;
			}
		}
	}

	if (m_edirection_ != m_preb_edirection_)
	{
		m_leap_alpha_ = 0.f;
		m_before_change_camera_location_ = GetActorLocation();
	}
	else
	{
		m_leap_alpha_ = SetLeapAlpha(DeltaTime);
	}

	m_goal_location_ = SetGoalLocation();
	if (m_goal_location_.Y > outrenze)
	{
		m_goal_location_.Y = outrenze;
	}

	SetActorLocation(SetCameraLocaiton());
	SetActorRotation(SetCameraRotator());

	m_preb_edirection_ = m_edirection_;
}

// 移動先の設定
FVector ASplineCamera::SetGoalLocation()
{
	if (m_pgamemanager_ != NULL)
	{
		///float root = FMath::Sqrt(2);
		float root = 1;
		// 現在制御している椅子の座標を返す
		FVector ChairLocation = (m_pgamemanager_->m_chairs_[m_pgamemanager_->m_nowroundnum_ - 1])->GetActorLocation();

		switch (m_edirection_)
		{
			case EDirection::kfront:
				ChairLocation += FVector(radius_, 0.f, 0.f);
				ChairLocation.Z += m_offset_location_z + m_offset_player_height_;
				return ChairLocation;
				break;
			
			case EDirection::kfrontright:
				ChairLocation += FVector(radius_ * root, radius_ * root, 0.f);
				ChairLocation.Z += m_offset_location_z + m_offset_player_height_;
				return ChairLocation;
				break;
				 
			case EDirection::kright:
				ChairLocation += FVector(0.f, radius_, 0.f);
				ChairLocation.Z += m_offset_location_z + m_offset_player_height_;
				return ChairLocation;
				break;

			case EDirection::kbackright:
				ChairLocation += FVector(-radius_ * root, radius_ * root, 0.f);
				ChairLocation.Z += m_offset_location_z + m_offset_player_height_;
				return ChairLocation;
				break;

			case EDirection::kback:
				ChairLocation += FVector(-radius_, 0.f, 0.f);
				ChairLocation.Z += m_offset_location_z + m_offset_player_height_;
				return ChairLocation;
				break;

			case EDirection::kbackleft:
				ChairLocation += FVector(-radius_ * root, -radius_ * root, 0.f);
				ChairLocation.Z += m_offset_location_z + m_offset_player_height_;
				return ChairLocation;
				break;
			
			case EDirection::kleft:
				ChairLocation += FVector(0.f, -radius_, 0.f);
				ChairLocation.Z += m_offset_location_z + m_offset_player_height_;
				return ChairLocation;
				break;

			case EDirection::kfrontleft:
				ChairLocation += FVector(radius_ * root, -radius_ * root, 0.f);
				ChairLocation.Z += m_offset_location_z + m_offset_player_height_;
				return ChairLocation;
				break;

			case EDirection::ktop:
				ChairLocation += FVector(0.f, 0.f, radius_);
				ChairLocation.Z += m_offset_location_z + m_offset_player_height_;
				return ChairLocation;
				break;

			case EDirection::kunder:
				ChairLocation += FVector(0.f, 0.f, -radius_);
				ChairLocation.Z += m_offset_location_z + m_offset_player_height_;
				return ChairLocation;
				break;
		}

		return FVector::ZeroVector;
	}
	else
	{
		return FVector::ZeroVector;
	}
}

FVector ASplineCamera::SetCameraLocaiton()
{
	if (m_pgamemanager_ != NULL)
	{
		return FMath::Lerp(m_before_change_camera_location_, m_goal_location_, m_leap_alpha_);
	}
	else
	{
		return FVector::ZeroVector;
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("GameManager is NULL (Splinecamera c++)")));
	}
}

FRotator ASplineCamera::SetCameraRotator()
{
	FVector tmp = m_pgamemanager_->m_chairs_[m_pgamemanager_->m_nowroundnum_ - 1]->GetActorLocation();
	tmp.Z += m_offset_player_height_;
	//UKismetSystemLibrary::DrawDebugLine(GetWorld(), GetActorLocation(), tmp, FLinearColor(255, 0, 0, 100), 0, 20);
	return UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), tmp);
}

float ASplineCamera::SetLeapAlpha(float _deltatime)
{
	if (m_leap_alpha_ + _deltatime / m_end_move_time_ > 1.0f)
	{
		return 1.f;
	}
	else
	{
		return m_leap_alpha_ + _deltatime /  m_end_move_time_ ;
	}
}