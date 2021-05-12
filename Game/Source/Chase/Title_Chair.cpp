//------------------------------------------------------------------
//クラス名：Title_Chair.cpp
//概要	  ：タイトルの椅子の動き制御
//作成日　：2021/05/11
//作成者　：19CU0228 野田八雲
//概要	　：2021/05/11 クラス作成
//------------------------------------------------------------------

//インクルード
#include "Title_Chair.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


//コンストラクタ
ATitle_Chair::ATitle_Chair()
	:m_movetime_(0.f)
	,m_visibletime_(0.f)
	,m_pboxcomponent_(NULL)
	,m_pstaticmeshcomp_(NULL)
{
 	//毎フレーム、このクラスのTick()を呼ぶかどうかを決めるフラグ。
	//必要に応じて、パフォーマンス向上のために、切ることもできる。
	PrimaryActorTick.bCanEverTick = true;

	m_pbase_ = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = m_pbase_;

	m_pboxcomponent_ = CreateDefaultSubobject<UBoxComponent>(TEXT("CollsionComp"));
	m_pboxcomponent_->SetupAttachment(RootComponent);

	m_pstaticmeshcomp_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticComp"));
	m_pstaticmeshcomp_->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void ATitle_Chair::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATitle_Chair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_visibletime_ += DeltaTime;


	if (m_visibletime_ < m_visibletimemax_)
	{
		m_pstaticmeshcomp_->SetVisibility(false);
	}
	else
	{
		m_pstaticmeshcomp_->SetVisibility(true);
		MoveChair(DeltaTime);
	}

}

void ATitle_Chair::MoveChair(float deltaTime_)
{

	//移動用に新しく座標を設定
	FVector v_newactorlocation_ = GetActorLocation();

	FRotator v_newactorrotation_ = GetActorRotation();

	//繰り返し運動
	float move_ = -(FMath::Sin(move_ + deltaTime_ * 8.f) - FMath::Sin(deltaTime_));

	//UE_LOG(LogTemp, Warning, TEXT("move_ = %f"), move_);

	//X軸に運動の速さを設定
	v_newactorlocation_.X += move_ * 500.f;

	v_newactorrotation_.Yaw += move_ * 3.0f;

	++m_chaircnt_;

	//UE_LOG(LogTemp, Warning, TEXT("m_chaircnt = %f"), m_chaircnt_);

	//m_movetime_ -= deltaTime_;

	//座標呼び出し
	SetActorLocation(FVector(v_newactorlocation_));

	SetActorRotation(FRotator(v_newactorrotation_));

	if (m_visibletime_ > m_visibletimemax_ + m_stopchairtime_)
	{
		v_newactorlocation_.X = m_location_x_;

		//座標呼び出し
		SetActorLocation(FVector(v_newactorlocation_));

		if (m_chaircnt_ >= m_chaircntmax_)
		{
			m_pstaticmeshcomp_->SetVisibility(false);

			v_newactorlocation_.X = 2650.f;

			//座標呼び出し
			SetActorLocation(FVector(v_newactorlocation_));

			m_visibletime_ = 0.f;

			m_chaircnt_ = 0.0f;
		}
	}
}

