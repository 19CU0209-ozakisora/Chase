//--------------------------------------------------------------
//クラス名：HousePoint.cpp
//概要	  ：椅子の距離によって、得点をつけるクラス（Chairクラスの継承クラス）
//作成日　：2021/04/29
//作成者　：19CU0228 野田八雲
//更新履歴：2021/04/29 作成
//--------------------------------------------------------------

//インクルード
#include "HouseCenter.h"
#include "Chair.h"

AHouseCenter::AHouseCenter()
	:m_getPoint(0)
	, m_thisLocation(FVector::ZeroVector)
	, m_ChairLocation(FVector::ZeroVector)
	, m_differenceLocation(0.f)
{
	//毎フレーム、このActor()がTickを呼ぶかどうかを決めるフラグ。必要に応じて、パフォーマンス向上のために切ることもできる。
	PrimaryActorTick.bCanEverTick = true;

	//確認用スタティックメッシュ用コンポーネント作成
	m_pConfirmMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("House Central"));
	m_pConfirmMesh->SetupAttachment(RootComponent);

}

//ゲームスタート時、または生成時に呼ばれる処理。
void AHouseCenter::BeginPlay()
{
	Super::BeginPlay();

	//ハウスの中心座標を格納
	m_thisLocation = GetActorLocation();


	//ハウスの中心点の座標確認用
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("X %f"), m_thisLocation.X));
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Y %f"), m_thisLocation.Y));
}

//毎フレーム更新処理
void AHouseCenter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//椅子が止まった時の処理
	StopChair();

}

//椅子が止まった時の処理
void AHouseCenter::StopChair()
{
	//ここまで通る

	//ここから先が通らない
	//継承しているためphase_でも適用するはずだと思ってたんですが・・・
	//椅子の状態が行動終了になったら（のつもり）
	if (AChair::phase_ == EPhase::kEnd)
	{
		//椅子の座標を格納（してるつもり）
		m_ChairLocation = AChair::GetActorLocation();

		//ハウスの中心座標と椅子の座標の距離の差を格納（のつもり）
		m_differenceLocation = m_ChairLocation.X * m_ChairLocation.Y;

		//これを見て通ってないことを確認してます。
		UE_LOG(LogTemp, Warning, TEXT("m_d %f"), m_differenceLocation);

	}

}

