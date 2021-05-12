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

//ゲームスタート時、または生成時に呼ばれる処理
void ATitle_Chair::BeginPlay()
{
	Super::BeginPlay();
	
}

//毎フレーム更新処理
void ATitle_Chair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//表示可能時間をカウント
	m_visibletime_ += DeltaTime;

	//表示時間が指定した時間を超えるまで非表示
	if (m_visibletime_ < m_visibletimemax_)
	{
		m_pstaticmeshcomp_->SetVisibility(false);
	}
	else
	{
		//指定した時間を超えたらメッシュを表示
		m_pstaticmeshcomp_->SetVisibility(true);
		MoveChair(DeltaTime);
	}

}

//椅子を動かす
void ATitle_Chair::MoveChair(float deltaTime_)
{

	//移動用に新しく座標を設定
	FVector v_newactorlocation_ = GetActorLocation();
	//回転する
	FRotator v_newactorrotation_ = GetActorRotation();

	//繰り返し運動
	float move_ = -(FMath::Sin(move_ + deltaTime_ * 8.f) - FMath::Sin(deltaTime_));

	//UE_LOG(LogTemp, Warning, TEXT("move_ = %f"), move_);

	//X軸に運動の速さを設定
	v_newactorlocation_.X += move_ * 500.f;

	v_newactorrotation_.Yaw += move_ * 3.0f;

	//発射した椅子の時間をカウント
	++m_chaircnt_;

	//UE_LOG(LogTemp, Warning, TEXT("m_chaircnt = %f"), m_chaircnt_);

	//m_movetime_ -= deltaTime_;

	//座標呼び出し
	SetActorLocation(FVector(v_newactorlocation_));

	SetActorRotation(FRotator(v_newactorrotation_));

	//椅子を止める処理
	if (m_visibletime_ > m_visibletimemax_ + m_stopchairtime_)
	{
		//各設定されたX座標を呼び出し
		v_newactorlocation_.X = m_location_x_;

		//座標呼び出し
		SetActorLocation(FVector(v_newactorlocation_));

		//椅子の発車時間が指定した時間を超えたら
		if (m_chaircnt_ >= m_chaircntmax_)
		{
			//メッシュを非表示
			m_pstaticmeshcomp_->SetVisibility(false);

			//スタート座標に椅子を戻す
			v_newactorlocation_.X = 2650.f;

			//座標呼び出し
			SetActorLocation(FVector(v_newactorlocation_));

			//Tick()で足されていた変数の初期化
			m_visibletime_ = 0.f;

			m_chaircnt_ = 0.0f;
		}
	}
}

