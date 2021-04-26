//--------------------------------------------------------------
//クラス名：HousePoint.cpp
//概要	  ：椅子の距離によって、得点をつけるクラス
//作成日　：2021/04/23
//作成者　：19CU0228 野田八雲
//更新履歴：2021/04/23 作成
//--------------------------------------------------------------

//インクルード
#include "HousePoint.h"
#include"Chair.h"

//コンストラクタ
AHousePoint::AHousePoint()
	:m_getPoint(0)
	,m_thisLocation(FVector::ZeroVector)
	,m_ChairLocation(FVector::ZeroVector)
	,m_prevdifferenceLocation(FVector::ZeroVector)
	,m_differenceLocation(FVector::ZeroVector)
{
 	//毎フレーム、このActor()がTickを呼ぶかどうかを決めるフラグ。必要に応じて、パフォーマンス向上のために切ることもできる。
	PrimaryActorTick.bCanEverTick = true;

	//確認用スタティックメッシュ用コンポーネント作成
	m_pConfirmMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("House Central"));
	m_pConfirmMesh->SetupAttachment(RootComponent);

}

//ゲームスタート時、または生成時に呼ばれる処理。
void AHousePoint::BeginPlay()
{
	Super::BeginPlay();
	
	//ハウスの中心座標を格納
	m_thisLocation = GetActorLocation();

	//椅子の座標を格納
	m_ChairLocation = FVector::ZeroVector;

	//ハウスの中心座標と椅子の座標の距離の差を格納(発射前)
	m_prevdifferenceLocation = m_ChairLocation - m_thisLocation;

	//ハウスの中心点の座標確認用
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("X %f"), m_thisLocation.X));
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Y %f"), m_thisLocation.Y));
}

//毎フレーム更新処理
void AHousePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHousePoint::StopChair()
{
	//椅子の座標を格納
	m_ChairLocation = FVector::ZeroVector;

	//ハウスの中心座標と椅子の座標の距離の差を格納
	m_differenceLocation = m_ChairLocation - m_thisLocation;

}

