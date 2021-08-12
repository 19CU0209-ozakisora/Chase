// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineCamera.h"

// Sets default values
ASplineCamera::ASplineCamera()
	: m_pcamera_(NULL)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_pcamera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("m_pcamera_"));
	m_pcamera_->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASplineCamera::BeginPlay()
{
	Super::BeginPlay();
	m_prebphase_ = EPhase::kEnd;
}

// Called every frame
void ASplineCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	//m_now_location_ = SetLeapAlpha();

	//FString text = m_goal_location_.ToString();
	//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, text);

	SetActorLocation(SetCameraLocaiton());
	SetActorRotation(SetCameraRotator());

	m_preb_edirection_ = m_edirection_;
}

FVector ASplineCamera::SetGoalLocation()
{
	if (m_pgamemanager_ != NULL)
	{
		///float root = FMath::Sqrt(2);
		float root = 1;
		// Œ»Ý§Œä‚µ‚Ä‚¢‚éˆÖŽq‚ÌÀ•W‚ð•Ô‚·
		FVector ChairLocation = (m_pgamemanager_->m_chairs_[m_pgamemanager_->m_nowroundnum_ - 1])->GetActorLocation();

		switch (m_edirection_)
		{
			case EDirection::kfront:
				ChairLocation += FVector(radius_, 0.f, 0.f);
				ChairLocation.Z += m_offset_location_z;
				return ChairLocation;
				break;
			
			case EDirection::kfrontright:
				ChairLocation += FVector(radius_ * root, radius_ * root, 0.f);
				ChairLocation.Z += m_offset_location_z;
				return ChairLocation;
				break;
				 
			case EDirection::kright:
				ChairLocation += FVector(0.f, radius_, 0.f);
				ChairLocation.Z += m_offset_location_z;
				return ChairLocation;
				break;

			case EDirection::kbackright:
				ChairLocation += FVector(-radius_ * root, radius_ * root, 0.f);
				ChairLocation.Z += m_offset_location_z;
				return ChairLocation;
				break;

			case EDirection::kback:
				ChairLocation += FVector(-radius_, 0.f, 0.f);
				ChairLocation.Z += m_offset_location_z;
				return ChairLocation;
				break;

			case EDirection::kbackleft:
				ChairLocation += FVector(-radius_ * root, -radius_ * root, 0.f);
				ChairLocation.Z += m_offset_location_z;
				return ChairLocation;
				break;
			
			case EDirection::kleft:
				ChairLocation += FVector(0.f, -radius_, 0.f);
				ChairLocation.Z += m_offset_location_z;
				return ChairLocation;
				break;

			case EDirection::kfrontleft:
				ChairLocation += FVector(radius_ * root, -radius_ * root, 0.f);
				ChairLocation.Z += m_offset_location_z;
				return ChairLocation;
				break;

			case EDirection::ktop:
				ChairLocation += FVector(0.f, 0.f, radius_);
				ChairLocation.Z += m_offset_location_z;
				return ChairLocation;
				break;

			case EDirection::kunder:
				ChairLocation += FVector(0.f, 0.f, -radius_);
				ChairLocation.Z += m_offset_location_z;
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
	return UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), (m_pgamemanager_->m_chairs_[m_pgamemanager_->m_nowroundnum_ - 1])->GetActorLocation());
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