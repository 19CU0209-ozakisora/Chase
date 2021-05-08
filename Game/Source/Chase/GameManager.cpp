// Fill out your copyright notice in the Description page of Project Settings.


//インクルード
#include "GameManager.h"
#include "Chair.h"

//コンストラクタ
AGameManager::AGameManager()
	: maxroundnum_(10)
	,m_teamPoint1P(0)
	,m_teamPoint2P(0)
	,m_thisLocation(FVector::ZeroVector)
	,m_bFunctionCheck(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

//ゲームスタート時、または生成時に呼ばれる処理
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	//ハウスの中心座標を格納
	m_thisLocation = GetActorLocation();

	TSubclassOf<APlayerchara> findClass;
	findClass = APlayerchara::StaticClass();
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, temp);

	for (int i = 0; i < temp.Num(); ++i)
	{
		players_.Add(Cast<APlayerchara>(temp[i]));
	}

	//探したいクラスを検索
	TSubclassOf<AChair> AChairfindClass;
	AChairfindClass = AChair::StaticClass();
	TArray<AActor*> AActortemp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChairfindClass, AActortemp);

	for (int i = 0; i < AActortemp.Num(); ++i)
	{
		m_pAChair[i] = Cast<AChair>(AActortemp[i]);
		/*if (m_pAChair[i] != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("isu addless is Not NULL "));
		}*/
	}

	StopChair();

	players_[0]->CreateChair();
	chairs_.Add(players_[0]->control_chair_);
	++nowroundnum_;
}

//毎フレーム更新処理
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nowroundnum_ % 2 == 1)
	{
		if (players_[0]->control_chair_->phase_ == EPhase::kEnd)
		{
			if (TimeCheck(DeltaTime))
			{
				players_[1]->CreateChair();
				
				chairs_.Add(players_[0]->control_chair_);
				++nowroundnum_;
			}
		}
	}
	else if (nowroundnum_ % 2 == 0)
	{
		if (players_[1]->control_chair_->phase_ == EPhase::kEnd)
		{
			if (TimeCheck(DeltaTime))
			{
				players_[0]->CreateChair();
				chairs_.Add(players_[0]->control_chair_);
				++nowroundnum_;
			}
		}
	}

	//ラウンドが10になったら
	/*if (nowroundnum_ > 10)
	{
		//椅子が10個止まった時の処理
		StopChair();
	}*/

}

bool AGameManager::TimeCheck(float _deltatime)
{
	time_cnt_ += _deltatime;

	if (time_cnt_ <= chair_create_time)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < chairs_.Num(); i++)
		{
			chairs_[i]->m_floating_pawn_movement_->Velocity = FVector::ZeroVector;
		}
		time_cnt_ = 0.f;
		return true;
	}
}

//椅子が止まった時の処理
void AGameManager::StopChair()
{
	//見つかった椅子のオブジェクト、座標を取得
	for (int i = 0; i < 10; ++i)
	{
		m_ChairDistance[i] = sqrt(((m_thisLocation.X - m_pAChair[i]->GetActorLocation().X) * (m_thisLocation.X - m_pAChair[i]->GetActorLocation().X))
			+ ((m_thisLocation.Y - m_pAChair[i]->GetActorLocation().Y) * (m_thisLocation.Y - m_pAChair[i]->GetActorLocation().Y)));
	}

	//ログ確認用
	for (int n = 0; n < 10; ++n)
	{
		//FString name = (chairs[n].chair_obj_)->GetName();
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, name);
		UE_LOG(LogTemp, Warning, TEXT("kyori before = %f"), m_ChairDistance[n]);

		if (m_pAChair[n]->m_PlayerNumberName == "P1Chair")
		{
			UE_LOG(LogTemp, Warning, TEXT("P1Chair"));
		}
		else if (m_pAChair[n]->m_PlayerNumberName == "P2Chair")
		{
			UE_LOG(LogTemp, Warning, TEXT("P2Chair"));
		}
	}

	//椅子の近さをソート
	ChairSort();
	//得点計算
	SetPoint();
}

//椅子の近い順にソート
void AGameManager::ChairSort()
{
	//変数宣言
	//交換用変数
	AChair* tmp;
	//配列番号用変数
	int dataCount01;
	int dataCount02;

	//2点間の距離でソ－トをかける
	for (dataCount01 = 0; dataCount01 < 10; ++dataCount01)
	{
		for (dataCount02 = 0; dataCount02 < 9 - dataCount01; ++dataCount02)
		{
			if (m_ChairDistance[dataCount02 + 1]< m_ChairDistance[dataCount02])
			{
				tmp = m_pAChair[dataCount02 + 1];
				m_pAChair[dataCount02 + 1] = m_pAChair[dataCount02];
				m_pAChair[dataCount02] = tmp;
				float ftmp = m_ChairDistance[dataCount02 + 1];
				m_ChairDistance[dataCount02 + 1] = m_ChairDistance[dataCount02];
				m_ChairDistance[dataCount02] = ftmp;
			}
		}
	}
	//ログで確認用
	for (int n = 0; n < 10; ++n)
	{
		UE_LOG(LogTemp, Warning, TEXT("kyori after = %f"), m_ChairDistance[n]);
		if (m_pAChair[n]->m_PlayerNumberName == "P1Chair")
		{
			UE_LOG(LogTemp, Warning, TEXT("P1Chair"));
		}
		else if (m_pAChair[n]->m_PlayerNumberName == "P2Chair")
		{
			UE_LOG(LogTemp, Warning, TEXT("P2Chair"));
		}
	}
}

//得点計算
void AGameManager::SetPoint()
{
	int i = 0;
	for (; i < 10; ++i)
	{
		if (m_pAChair[0]->m_PlayerNumberName == m_pAChair[i + 1]->m_PlayerNumberName)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	if(m_pAChair[0]->m_PlayerNumberName == "P1Chair")
	{
		//  そのタグにポイントを入れる
		m_teamPoint1P = i + 1 + m_teamPoint1P;
	}
	else if (m_pAChair[0]->m_PlayerNumberName == "P2Chair")
	{
		m_teamPoint2P = i + 1 + m_teamPoint2P;
	}
	UE_LOG(LogTemp, Warning, TEXT("P1Point %d"), m_teamPoint1P);
	UE_LOG(LogTemp, Warning, TEXT("P2Point %d"), m_teamPoint2P);

	//得点計算後、Tick()を無効にする
	PrimaryActorTick.SetTickFunctionEnable(false);
}
