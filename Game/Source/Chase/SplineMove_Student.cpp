// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineMove_Student.h"

// Sets default values
ASplineMove_Student::ASplineMove_Student()
	: m_spline_length_(0.f)
	, m_is_loop_(false)
	, m_speed_(0.f)
	, m_pchildactorcomponent_(NULL)
	//, m_psplinecomponent_(CreateDefaultSubobject<USplineComponent>(TEXT("m_psplinecomponent_")))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//	なぜかNULLになる
	m_psplinecomponent_ = CreateDefaultSubobject<USplineComponent>(TEXT("m_psplinecomponent_"));
	m_psplinecomponent_->SetupAttachment(RootComponent);

	m_pchildactorcomponent_ = CreateDefaultSubobject<UChildActorComponent>(TEXT("m_pactor_"));
	m_pchildactorcomponent_->SetupAttachment(m_psplinecomponent_);

}

// Called when the game starts or when spawned
void ASplineMove_Student::BeginPlay()
{
	Super::BeginPlay();

	if (m_psplinecomponent_)
	{
		m_spline_length_ = m_psplinecomponent_->GetSplineLength();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("m_psplinecomponent_ is NULL (By SplineMove_Student.cpp)"));
	}
}

// Called every frame
void ASplineMove_Student::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// アクターがセット済みかどうか
	if (m_pchildactorcomponent_)
	{
		// 移動量の計算
		m_movement_ += m_speed_ * DeltaTime;

		// m_movementの値の距離に移動
		// GetLocationAtDistanceAlongSpline->スプラインの長さを取得し、第一引数の場所に移動
		if (m_psplinecomponent_)
		{
			m_pchildactorcomponent_->SetWorldLocation(m_psplinecomponent_->GetLocationAtDistanceAlongSpline(m_movement_, ESplineCoordinateSpace::World));
		}

		// ループ設定がONなら移動が終わった時点でリセット
		if (m_is_loop_)
		{
			if (m_movement_ >= m_spline_length_)
			{
				m_movement_ = 0.f;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("m_pactor_ is NULL (By SplineMove_Student.cpp)"));
	}
}

