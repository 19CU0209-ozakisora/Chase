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
	:m_getPoint(500)
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
	// 2021/04/29 尾崎：一時的にコメント化
	//2021/05/02　野田：コメント解除
	//StopChair();
}

//椅子が止まった時の処理
void AHouseCenter::StopChair()
{

	//探したいクラスを検索
	TSubclassOf<AChair> findClass;
	findClass = AChair::StaticClass();
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, temp);

	//見つかった椅子のオブジェクト、座標を取得
	for (int i = 0; i < temp.Num(); ++i)
	{
		AChair* chair = Cast<AChair>(temp[i]);
		FChair tmp;
		tmp.chair_obj_ = chair;
		tmp.location_ = chair->GetActorLocation();
		//中心から椅子の距離を計算し、椅子の情報に保存
		_Vector[i] = sqrt(((m_thisLocation.X - tmp.location_.X) * (m_thisLocation.X - tmp.location_.X))
			+ ((m_thisLocation.Y - tmp.location_.Y) * (m_thisLocation.Y - tmp.location_.Y)));
		chairs.Add(tmp);
	}

	ChairSort(_Vector);

	SetPoint(_Vector);

	//ログ確認用
	for (int n = 0; n < chairs.Num(); ++n)
	{
		//FString name = (chairs[n].chair_obj_)->GetName();
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, name);
		//UE_LOG(LogTemp, Warning, TEXT("座標： X : %f , Y : %f, Z : %f"), chairs[n].location_.X, chairs[n].location_.Y, chairs[n].location_.Z);
		//UE_LOG(LogTemp, Warning, TEXT("kyori= %f"), _Vector[n]);
	}

}

//椅子の距離ソート用(バブルソート)
void AHouseCenter::ChairSort(float _Vector[])
{
	float tmp;

	int dataCount01;
	int dataCount02;

	//2点間の距離でソ－トをかける
	for (dataCount01 = 0; dataCount01 < 9; ++dataCount01)
	{
		for (dataCount02 = 0; dataCount02 < 10 - dataCount01; ++dataCount02)
		{
			if (_Vector[dataCount02 + 1] < _Vector[dataCount02])
			{
				tmp = _Vector[dataCount02];
				_Vector[dataCount02] = _Vector[dataCount02 + 1];
				_Vector[dataCount02 + 1] = tmp;
			}
		}
	}
	for (int n = 0; n < 10; ++n)
	{
		UE_LOG(LogTemp, Warning, TEXT("kyori= %f"), _Vector[n]);
	}
}

void AHouseCenter::SetPoint(float _Vector[])
{
	for (int i = 0; i < 10; ++i)
	{
		if (_Vector[i])
		{
			UE_LOG(LogTemp, Warning, TEXT("point: %d"), m_getPoint);

			if (m_getPoint > 0)
			{
				m_getPoint -= 100;
			}
		}
	}
}

