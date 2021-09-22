//--------------------------------------------------------------
//クラス名：TrackingCamera.cpp
//概要	  ：プレイヤーの後ろを追尾するカメラを制御するクラス
//作成日　：2021/09/09
//作成者　：19CU0209 尾崎蒼宙
//更新履歴：2021/0
//--------------------------------------------------------------


#include "TrackingCamera.h"

// Sets default values
ATrackingCamera::ATrackingCamera()
	: m_leap_alpha_(0.f)
	, m_input_tracking_offset_(FVector::ZeroVector)
	, m_temp_(FVector::ZeroVector)
	, m_time_(0.f)
	, m_camera_offset_(FVector::ZeroVector)
	, m_control_chair_(NULL)
	, m_pgamemanager_(NULL)
	, m_pspringarm_component_(NULL)
	, m_pcamera_component_(NULL)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pspringarm_component_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("m_pspringarm_component_"));
	RootComponent = m_pspringarm_component_;

	m_pcamera_component_ = CreateDefaultSubobject<UCameraComponent>(TEXT("m_pcamera_component_"));
	m_pcamera_component_->SetupAttachment(m_pspringarm_component_);
}

// Called when the game starts or when spawned
void ATrackingCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrackingCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_pgamemanager_)
	{
		m_control_chair_ = m_pgamemanager_->m_chairs_[m_pgamemanager_->m_nowroundnum_ - 1];
		FVector ChairLocation = m_control_chair_->GetActorLocation();
		float Inputvalue = m_control_chair_->m_input_value_.Y;

		if (m_control_chair_->GetPhase() == EPhase::kPowerChange)
		{
			if (Inputvalue < 0.f)
			{
				m_input_tracking_offset_.X = m_max_recession_offset_.X * FMath::Abs(Inputvalue);
				m_input_tracking_offset_.Y = m_max_recession_offset_.Y * FMath::Abs(Inputvalue);
				m_input_tracking_offset_.Z = m_max_recession_offset_.Z * FMath::Abs(Inputvalue);
				m_temp_ = m_input_tracking_offset_;
			}
			else
			{
				m_input_tracking_offset_.X = 0.f;
				m_input_tracking_offset_.Y = 0.f;
				m_input_tracking_offset_.Z = 0.f;
			}
		}
		else if (m_control_chair_->GetPhase() == EPhase::kSlip)
		{
			if (!m_switch_)
			{
				UE_LOG(LogTemp, Warning, TEXT("m_switch_ = false"));
				m_advance_time_ += DeltaTime * m_speed_;
				if (m_advance_time_ >= 1.f)
				{
					m_advance_time_ = 1.f;
					m_switch_ = true;
				}
				//float sin = FMath::Sin(m_advance_time_);
				m_input_tracking_offset_ = FMath::Lerp(m_temp_, m_max_advance_offset_, m_padvance_curve_->GetFloatValue(m_advance_time_));
			}
			/*
			else if (m_switch_)
			{
				UE_LOG(LogTemp, Warning, TEXT("m_switch_ = true"));
				m_advance_time_ -= DeltaTime * m_speed_;
				if (m_advance_time_ <= 0.f)
				{
					m_advance_time_ = 0.f;
				}
				m_input_tracking_offset_ = FMath::Lerp(m_temp_, m_max_advance_offset_, FMath::Abs(m_advance_time_));
			}
			*/
		}
		

		SetActorLocation(FVector(ChairLocation.X + m_camera_offset_.X + m_input_tracking_offset_.X, ChairLocation.Y + m_camera_offset_.Y + m_input_tracking_offset_.Y , ChairLocation.Z + m_camera_offset_.Z + m_input_tracking_offset_.Z));

		//FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ChairLocation);
		//SetActorRotation(Rotation);
	}
}

