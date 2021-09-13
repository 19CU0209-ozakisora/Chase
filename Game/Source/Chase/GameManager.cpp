//--------------------------------------------------------------
//クラス名：GameManager.cpp
//概要	  ：椅子の制御用クラス
//作成日　：2021/04/26
//作成者　：19CU0209 尾崎蒼宙
//更新履歴：2021/04/26 尾崎蒼宙 作成
//			2021/04/23 尾崎蒼宙 ヒット時の処理をBPからC++に移植
//			2021/05/04 尾崎蒼宙 現在のターン・どちらの番か・椅子の生成などを追加
//			2021/05/07 尾崎蒼宙 椅子のNULLチェックの追加
//			2021/05/09 尾崎蒼宙 椅子の操作権の変更処理を追加
//								一定時間後に次のラウンドにする処理の追加
//			2021/05/09 野田八雲 得点計算の処理の追加
//			2021/05/10 尾崎蒼宙 消されたデータの復旧
//								m_PlayerNumberNameをm_name_に変更
//								m_pAchairをm_chairs_に変更(役割の変更)
//			2021/05/16 尾崎蒼宙 HouseCenterクラスのオブジェクトを検索できる処理の追加
//			2021/05/17 尾崎蒼宙 現在のターン数が最大ターン数を超えないように修正
//			2021/05/18 尾崎蒼宙 シーン遷移した際にプレイヤー1と2の取得順が異なる場合があるため配列に入れる際にTag検知を追加
//			2021/05/19 尾崎蒼宙 配列外参照を修正
//								不必要なUE_LOGの削除
//			2021/05/19 野田八雲 得点計算タイミング変更
//			2021/05/21 尾崎蒼宙 椅子の上の人間を消す処理の追加
//			2021/05/21 尾崎蒼宙 消されたデータの復旧
//			2021/07/16 尾崎蒼宙 プレイヤーが止まっているマスに近い側の点数を加算する処理を追加
//			2021/08/30 野田八雲 m_teamPoint1P/2PをInstanceに変更
//			2021/09/07 野田八雲 各椅子がとった得点を計算する変数追加（ウィジェット出力用）
//--------------------------------------------------------------

//インクルード
#include "GameManager.h"
#include "Chair.h"

//コンストラクタ
AGameManager::AGameManager()
	// 尾崎
	// private
	: time_cnt_(0.f)
	// public
	, m_players_()
	, m_chairs_()
	, m_is_event_(false)
	, m_chair_create_time_(0.f)
	, m_switch_level_time(0.f)
	, m_event_cnt_(0)
	, m_nowroundnum_(0)
	, m_maxroundnum_(10)
	, m_event_round_()
	,m_teamPoint1P(0)
	,m_teamPoint2P(0)
	,m_countChair1P(0)
	,m_countChair2P(0)
	,m_thisLocation(FVector::ZeroVector)
	, m_Player1Turn(0)
	, m_Player2Turn(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

//ゲームスタート時、または生成時に呼ばれる処理
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<AHouseCenter> AHouseCenterfindClass;
	AHouseCenterfindClass = AHouseCenter::StaticClass();
	TArray<AActor*> AHouseCentertemp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHouseCenterfindClass, AHouseCentertemp);
	
	for (int i = 0; i < AHouseCentertemp.Num(); ++i)
	{
		//ハウスの中心座標を格納
		m_thisLocation = AHouseCentertemp[0]->GetActorLocation();
	}

	TSubclassOf<APlayerchara> APlayercharafindClass;
	APlayercharafindClass = APlayerchara::StaticClass();
	TArray<AActor*> APlayercharatemp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayercharafindClass, APlayercharatemp);

	for (int i = 0; i < APlayercharatemp.Num(); ++i)
	{
		m_players_.Add(Cast<APlayerchara>(APlayercharatemp[i]));
	}

	if (m_players_[0] != NULL && m_players_.Num() == 2)
	{
		if (m_players_[0]->GetFName() != "BP_Player1")
		{
			APlayerchara* PlayerTemp = m_players_[0];
			m_players_[0] = m_players_[1];
			m_players_[1] = PlayerTemp;
		}
	}

	//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
	// 青木追加
	// GameInstanceの実態を検索している関数の呼び出し
	Instance = UInstance::GetInstance();

	//インスタンスで宣言した変数の初期化
	Instance->m_teamPoint1P = 0;
	Instance->m_teamPoint2P = 0;
	Instance->m_chairEachPoint1P_1 = 0;
	Instance->m_chairEachPoint1P_2 = 0;
	Instance->m_chairEachPoint1P_3 = 0;
	Instance->m_chairEachPoint1P_4 = 0;
	Instance->m_chairEachPoint1P_5 = 0;
	Instance->m_chairEachPoint2P_1 = 0;
	Instance->m_chairEachPoint2P_2 = 0;
	Instance->m_chairEachPoint2P_3 = 0;
	Instance->m_chairEachPoint2P_4 = 0;
	Instance->m_chairEachPoint2P_5 = 0;

	if (Instance)
	{
		//UE_LOG(LogTemp, Error, TEXT("%d"), NumberOfTurns->m_Turn);
		// 別のレベルで設定したターン数を代入
		m_maxroundnum_ = Instance->m_Turn;

		// Player1,Player2のターン数の設定
		m_Player1Turn = m_maxroundnum_ / 2;
		m_Player2Turn = m_Player1Turn;
	}
	//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆

	// ゲームの最大ラウンド数 / 2 (for分の中でPlayer1とPlayer2の椅子の生成を同時に行うため、m_maxroundnum_ / 2にしています)
	for (int i = 0; i < m_maxroundnum_ / 2; ++i)
	{
		// 椅子の生成及び位置の指定、管理するために配列に格納
		m_players_[0]->CreateChair();
		m_players_[0]->control_chair_->SetActorLocation(FVector(m_players_[0]->chair_stack_->GetComponentLocation().X, m_players_[0]->chair_stack_->GetComponentLocation().Y + i * 250, m_players_[0]->chair_stack_->GetComponentLocation().Z), false, nullptr, ETeleportType::TeleportPhysics);
		m_chairs_.Add(m_players_[0]->control_chair_);

		m_players_[1]->CreateChair();
		m_players_[1]->control_chair_->SetActorLocation(FVector(m_players_[1]->chair_stack_->GetComponentLocation().X, m_players_[1]->chair_stack_->GetComponentLocation().Y + i * 250, m_players_[1]->chair_stack_->GetComponentLocation().Z), false, nullptr, ETeleportType::TeleportPhysics);
		m_chairs_.Add(m_players_[1]->control_chair_);
	}

	// 2021/05/10 尾崎 ゲーム開始時に生成させたものを取得している為コメント化(検索する必要なし)
	/*
	//探したいクラスを検索
	TSubclassOf<AChair> AChairfindClass;
	AChairfindClass = AChair::StaticClass();
	TArray<AActor*> AActortemp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChairfindClass, AActortemp);

	for (int i = 0; i < AActortemp.Num(); ++i)
	{
		m_chairs_[i] = Cast<AChair>(AActortemp[i]);
		/*if (m_chairs_[i] != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("isu addless is Not NULL "));
		}
	}
	*/

	//Player[0]が管理している椅子の視点に変更
	m_players_[0]->control_chair_ = m_chairs_[0];
	m_players_[0]->GetOperate();
	++m_nowroundnum_;
}

//毎フレーム更新処理
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 奇数ターンの時(Player1の番)
	if (m_nowroundnum_ % 2 == 1)
	{
		// NULLチェック
		if (m_players_[0]->control_chair_ != NULL)
		{
			// 現在操作している椅子が椅子に当たる or 一定ラインまで行ってしまったら
			if (m_players_[0]->control_chair_->GetPhase() == EPhase::kEnd)
			{
				// 一定秒数経過後、操作する椅子の変更
				if (TimeCheck(DeltaTime))
				{
					//NextRound();
				}
				//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
				// 青木追加::Player1のターン数を減らす
				if (m_Player1Turn == m_Player2Turn)
				{
					m_Player1Turn--;
				}
				//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
			}
		}

	}
	// 奇数ターンの時(Player2の番)
	else if (m_nowroundnum_ % 2 == 0)
	{
		// NULLチェック
		if (m_players_[1]->control_chair_ != NULL)
		{
			// 現在操作している椅子が椅子に当たる or 一定ラインまで行ってしまったら
			if (m_players_[1]->control_chair_->GetPhase() == EPhase::kEnd)
			{
				// 一定秒数経過後、操作する椅子の変更
				if (TimeCheck(DeltaTime))
				{
					//NextRound();
				}
				//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
				// 青木追加::Player2のターン数を減らす
				if (m_Player1Turn < m_Player2Turn)
				{
					m_Player2Turn--;
				}
				//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
			}
		}
	}

	//ラウンドが10になったら
	if (m_nowroundnum_ == m_maxroundnum_ && m_players_[1]->control_chair_->GetPhase() == EPhase::kEnd)
	{
		//椅子が10個止まった時の処理
		//StopChair();
		AddScore();
	}
}

bool AGameManager::TimeCheck(float _deltatime)
{
	time_cnt_ += _deltatime;

	if (time_cnt_ <= m_chair_create_time_)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < m_chairs_.Num(); i++)
		{
			m_chairs_[i]->m_projectile_movement_->Velocity = FVector::ZeroVector;
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
		m_ChairDistance[i] = sqrt(((m_thisLocation.X - m_chairs_[i]->GetActorLocation().X) * (m_thisLocation.X - m_chairs_[i]->GetActorLocation().X))
			+ ((m_thisLocation.Y - m_chairs_[i]->GetActorLocation().Y) * (m_thisLocation.Y - m_chairs_[i]->GetActorLocation().Y)));
	}

	//ログ確認用
	for (int n = 0; n < 10; ++n)
	{
		UE_LOG(LogTemp, Warning, TEXT("kyori before = %f"), m_ChairDistance[n]);

		if (m_chairs_[n]->m_name_ == "P1Chair")
		{
			UE_LOG(LogTemp, Warning, TEXT("P1Chair"));
		}
		else if (m_chairs_[n]->m_name_ == "P2Chair")
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
				tmp = m_chairs_[dataCount02 + 1];
				m_chairs_[dataCount02 + 1] = m_chairs_[dataCount02];
				m_chairs_[dataCount02] = tmp;
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
		if (m_chairs_[n]->m_name_ == "P1Chair")
		{
			UE_LOG(LogTemp, Warning, TEXT("P1Chair"));
		}
		else if (m_chairs_[n]->m_name_ == "P2Chair")
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
		if (m_chairs_[0]->m_name_ == m_chairs_[i + 1]->m_name_)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	if(m_chairs_[0]->m_name_ == "P1Chair")
	{
		//  そのタグにポイントを入れる
		m_teamPoint1P += i + 1 + m_teamPoint1P;
	}
	else if (m_chairs_[0]->m_name_ == "P2Chair")
	{
		m_teamPoint2P += i + 1 + m_teamPoint2P;
	}
	UE_LOG(LogTemp, Warning, TEXT("P1Point %d"), m_teamPoint1P);
	UE_LOG(LogTemp, Warning, TEXT("P2Point %d"), m_teamPoint2P);

	//得点計算後、Tick()を無効にする
	PrimaryActorTick.SetTickFunctionEnable(false);
}

void AGameManager::AddScore()
{
	// 椅子の数だけ繰り返す
	for (int i = 0; i < m_chairs_.Num(); ++i)
	{
		// NULLチェック
		if (m_chairs_[i] != NULL)
		{
			// 椅子とそれぞれのスコアコリジョンの距離を格納するための変数
			float Scoreobj1_Distance = 0.f;
			float Scoreobj2_Distance = 0.f;

			// 参照している椅子にスコアコリジョンが格納されているか確認してから距離を計算
			if (m_chairs_[i]->m_pscore_obj_[0] != NULL)
			{
				Scoreobj1_Distance = FMath::Abs(m_chairs_[i]->GetActorLocation().X - m_chairs_[i]->m_pscore_obj_[0]->GetActorLocation().X);
			}
			if (m_chairs_[i]->m_pscore_obj_[1] != NULL)
			{
				Scoreobj2_Distance = FMath::Abs(m_chairs_[i]->GetActorLocation().X - m_chairs_[i]->m_pscore_obj_[1]->GetActorLocation().X);
			}

			// Scoreobj1_Distanceの方が小さい場合はm_pscore_obj_[0]側に椅子が寄っている為m_pscore_obj_[0]のスコアを加算
			if (Scoreobj1_Distance < Scoreobj2_Distance)
			{
				if (m_chairs_[i]->m_pscore_obj_[0] != NULL)
				{
					if (Instance)
					{
						// Player1か2か判別したのちに得点加算
						if (m_chairs_[i]->m_name_ == "Player1")
						{
							//チームの合計得点を加算
							Instance->m_teamPoint1P += m_chairs_[i]->m_pscore_obj_[0]->m_score_;

							//椅子カウント用変数の値を確認し、その値によって椅子のそれぞれの得点を格納
							switch (m_countChair1P)
							{
							case 0:
								Instance->m_chairEachPoint1P_1 = m_chairs_[i]->m_pscore_obj_[0]->m_score_;								
								break;
							case 1:
								Instance->m_chairEachPoint1P_2 = m_chairs_[i]->m_pscore_obj_[0]->m_score_;							
								break;
							case 2:
								Instance->m_chairEachPoint1P_3 = m_chairs_[i]->m_pscore_obj_[0]->m_score_;
								break;
							case 3:
								Instance->m_chairEachPoint1P_4 = m_chairs_[i]->m_pscore_obj_[0]->m_score_;								
								break;
							case 4:
								Instance->m_chairEachPoint1P_5 = m_chairs_[i]->m_pscore_obj_[0]->m_score_;								
								break;
							default:
								break;
							}
						}
						else
						{
							//チームの合計得点を加算
							Instance->m_teamPoint2P += m_chairs_[i]->m_pscore_obj_[0]->m_score_;

							//椅子カウント用変数の値を確認し、その値によって椅子のそれぞれの得点を格納
							switch (m_countChair2P)
							{
							case 0:
								Instance->m_chairEachPoint2P_1 = m_chairs_[i]->m_pscore_obj_[0]->m_score_;								
								break;
							case 1:
								Instance->m_chairEachPoint2P_2 = m_chairs_[i]->m_pscore_obj_[0]->m_score_;								
								break;
							case 2:
								Instance->m_chairEachPoint2P_3 = m_chairs_[i]->m_pscore_obj_[0]->m_score_;								
								break;
							case 3:
								Instance->m_chairEachPoint2P_4 = m_chairs_[i]->m_pscore_obj_[0]->m_score_;								
								break;
							case 4:
								Instance->m_chairEachPoint2P_5 = m_chairs_[i]->m_pscore_obj_[0]->m_score_;								
								break;
							default:
								break;
							}
						}
					}
				}
			}
			else
			{
				if (Instance)
				{
					if (m_chairs_[i]->m_pscore_obj_[1] != NULL)
					{
						if (m_chairs_[i]->m_name_ == "Player1")
						{
							//チームの合計得点を加算
							Instance->m_teamPoint1P += m_chairs_[i]->m_pscore_obj_[1]->m_score_;

							//椅子カウント用変数の値を確認し、その値によって椅子のそれぞれの得点を格納
							switch (m_countChair1P)
							{
							case 0:
								Instance->m_chairEachPoint1P_1 = m_chairs_[i]->m_pscore_obj_[1]->m_score_;								
								break;
							case 1:
								Instance->m_chairEachPoint1P_2 = m_chairs_[i]->m_pscore_obj_[1]->m_score_;								
								break;
							case 2:
								Instance->m_chairEachPoint1P_3 = m_chairs_[i]->m_pscore_obj_[1]->m_score_;								
								break;
							case 3:
								Instance->m_chairEachPoint1P_4 = m_chairs_[i]->m_pscore_obj_[1]->m_score_;								
								break;
							case 4:
								Instance->m_chairEachPoint1P_5 = m_chairs_[i]->m_pscore_obj_[1]->m_score_;								
								break;
							default:
								break;
							}
						}
						else
						{
							//チームの合計得点を加算
							Instance->m_teamPoint2P += m_chairs_[i]->m_pscore_obj_[1]->m_score_;

							//椅子カウント用変数の値を確認し、その値によって椅子のそれぞれの得点を格納
							switch (m_countChair2P)
							{
							case 0:
								Instance->m_chairEachPoint2P_1 = m_chairs_[i]->m_pscore_obj_[1]->m_score_;								
								break;
							case 1:
								Instance->m_chairEachPoint2P_2 = m_chairs_[i]->m_pscore_obj_[1]->m_score_;								
								break;
							case 2:
								Instance->m_chairEachPoint2P_3 = m_chairs_[i]->m_pscore_obj_[1]->m_score_;								
								break;
							case 3:
								Instance->m_chairEachPoint2P_4 = m_chairs_[i]->m_pscore_obj_[1]->m_score_;								
								break;
							case 4:
								Instance->m_chairEachPoint2P_5 = m_chairs_[i]->m_pscore_obj_[1]->m_score_;								
								break;
							default:
								break;
							}
						}
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("chair[%f] is NULL"), i);
		}

		//椅子が取った得点が0の場合、上の処理が通らないため、結果画面での何投目の椅子が何点
		//取ったがが正しく表示されるように、ここで椅子のカウントを足す。
		if (i % 2 == 0)
		{
			m_countChair1P++;
		}
		else if (i % 2 == 1)
		{
			m_countChair2P++;
		}
	}

	//各椅子の得点、チーム合計得点のログ確認用（ここで出た得点がウィジェットに出力される）

	//UE_LOG(LogTemp, Warning, TEXT("Instance->m_countChair1P %d"), m_countChair1P);
	//UE_LOG(LogTemp, Warning, TEXT("Instance->m_countChair2P %d"), m_countChair2P);
	/*UE_LOG(LogTemp, Warning, TEXT("Instance->1P_1 %d"), Instance->m_chairEachPoint1P_1);
	UE_LOG(LogTemp, Warning, TEXT("Instance->1P_2 %d"), Instance->m_chairEachPoint1P_2);
	UE_LOG(LogTemp, Warning, TEXT("Instance->1P_3 %d"), Instance->m_chairEachPoint1P_3);
	UE_LOG(LogTemp, Warning, TEXT("Instance->1P_4 %d"), Instance->m_chairEachPoint1P_4);
	UE_LOG(LogTemp, Warning, TEXT("Instance->1P_5 %d"), Instance->m_chairEachPoint1P_5);
	UE_LOG(LogTemp, Warning, TEXT("Instance->2P_1 %d"), Instance->m_chairEachPoint2P_1);
	UE_LOG(LogTemp, Warning, TEXT("Instance->2P_2 %d"), Instance->m_chairEachPoint2P_2);
	UE_LOG(LogTemp, Warning, TEXT("Instance->2P_3 %d"), Instance->m_chairEachPoint2P_3);
	UE_LOG(LogTemp, Warning, TEXT("Instance->2P_4 %d"), Instance->m_chairEachPoint2P_4);
	UE_LOG(LogTemp, Warning, TEXT("Instance->2P_5 %d"), Instance->m_chairEachPoint2P_5);*/
	//UE_LOG(LogTemp, Warning, TEXT("Instance->m_teamPoint1P %d"), Instance->m_teamPoint1P);
	//UE_LOG(LogTemp, Warning, TEXT("Instance->m_teamPoint2P %d"), Instance->m_teamPoint2P);

	//得点計算後、Tick()を無効にする
	PrimaryActorTick.SetTickFunctionEnable(false);
}

void AGameManager::NextRound()
{
	// 配列の要素数外の参照をしないかどうか
	if (m_nowroundnum_ <= m_chairs_.Num() - 1)
	{
		if (m_chairs_[m_nowroundnum_] != NULL)
		{
			if (m_nowroundnum_ % 2 == 1)
			{
				m_players_[1]->control_chair_ = m_chairs_[m_nowroundnum_];
				m_players_[1]->GetOperate();
			}
			else
			{
				m_players_[0]->control_chair_ = m_chairs_[m_nowroundnum_];
				m_players_[0]->GetOperate();
			}


			// 椅子の配列の個数分だけ椅子のSpawnDefaultController()関数を呼ぶ
			// 本来は操作する椅子の変更後、前まで操作していた椅子だけSpawnDefaultController()関数
			// を使用すれば良い予定だが、処理は通ったものの上手く機能しないためfor文で無理やり行っています。
			for (int i = 0; i < m_chairs_.Num(); ++i)
			{
				m_chairs_[i]->SpawnDefaultController();
				if (m_chairs_[i]->m_ishit_)
				{
					// NULLチェックは関数内で行います
					m_chairs_[i]->DestroyHuman();
				}
			}

			if (m_nowroundnum_ < m_maxroundnum_)
			{
				++m_nowroundnum_;
			}
		}
	}
}