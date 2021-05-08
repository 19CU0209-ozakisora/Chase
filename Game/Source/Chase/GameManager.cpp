//--------------------------------------------------------------
//クラス名：GameManager.cpp
//概要	  ：椅子の制御用クラス
//作成日　：2021/04/22
//作成者　：19CU0209 尾崎蒼宙
//更新履歴：2021/04/26 尾崎蒼宙 作成
//			2021/04/23 尾崎蒼宙 ヒット時の処理をBPからC++に移植
//			2021/05/04 尾崎蒼宙 現在のターン・どちらの番か・椅子の生成などを追加
//			2021/05/07 尾崎蒼宙 GameManagerの修正
//--------------------------------------------------------------
#include "GameManager.h"

// Sets default values
AGameManager::AGameManager()
	: nowroundnum_(0)
	, time_cnt_(0.f)
	, maxroundnum_(10)
	, control_chair_(NULL)
	, chair_create_time(0.f)
	, players_()
	, chairs_()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	// レベル上に配置しているPlayerの検索及び格納
	TSubclassOf<APlayerchara> findClass;
	findClass = APlayerchara::StaticClass();
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, temp);

	for (int i = 0; i < temp.Num(); ++i)
	{
		players_.Add(Cast<APlayerchara>(temp[i]));
	}

	// ゲームの最大ラウンド数 / 2 (for分の中でPlayer1とPlayer2の椅子の生成を同時に行うため、maxroundnum_ / 2にしています)
	for (int n = 0; n < maxroundnum_ / 2; ++n)
	{
		// 椅子の生成及び位置の指定、管理するために配列に格納
		players_[0]->CreateChair();
		players_[0]->control_chair_->SetActorLocation(FVector(players_[0]->chair_stack_->GetComponentLocation().X, players_[0]->chair_stack_->GetComponentLocation().Y + n * 250, players_[0]->chair_stack_->GetComponentLocation().Z), false, nullptr, ETeleportType::TeleportPhysics);
		chairs_.Add(players_[0]->control_chair_);

		players_[1]->CreateChair();
		players_[1]->control_chair_->SetActorLocation(FVector(players_[1]->chair_stack_->GetComponentLocation().X, players_[1]->chair_stack_->GetComponentLocation().Y + n * 250, players_[1]->chair_stack_->GetComponentLocation().Z), false, nullptr, ETeleportType::TeleportPhysics);
		chairs_.Add(players_[1]->control_chair_);
	}

	// Player[0]が管理している椅子の視点に変更
	players_[0]->GetOperate();
	++nowroundnum_;
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 奇数ターンの時(Player1の番)
	if (nowroundnum_ % 2 == 1)
	{
		// NULLチェック
		if (players_[0]->control_chair_ != NULL)
		{
			// 現在操作している椅子が椅子に当たる or 一定ラインまで行ってしまったら
			if (players_[0]->control_chair_->phase_ == EPhase::kEnd)
			{
				// 一定秒数経過後、操作する椅子の変更
				if (TimeCheck(DeltaTime))
				{
					players_[1]->control_chair_ = chairs_[nowroundnum_];
					players_[1]->GetOperate();
					
					// 椅子の配列の個数分だけ椅子のSpawnDefaultController()関数を呼ぶ
					// 本来は操作する椅子の変更後、前まで操作していた椅子だけSpawnDefaultController()関数
					// を使用すれば良い予定だが、処理は通ったものの上手く機能しないためfor文で無理やり行っています。かなりよろしくない
					for (int i = 0; i < chairs_.Num(); ++i)
					{
						chairs_[i]->SpawnDefaultController();
						// chairs_[i]->b();
					}

					// players_[1]->CreateChair();						// 2021/05/08 BeginPlayで生成するように変更
					// chairs_.Add(players_[1]->control_chair_);		

					++nowroundnum_;
				}
			}
		}
	}
	// 奇数ターンの時(Player2の番)
	else if (nowroundnum_ % 2 == 0)
	{
		// NULLチェック
		if (players_[1]->control_chair_ != NULL)
		{
			// 現在操作している椅子が椅子に当たる or 一定ラインまで行ってしまったら
			if (players_[1]->control_chair_->phase_ == EPhase::kEnd)
			{
				// 一定秒数経過後、操作する椅子の変更
				if (TimeCheck(DeltaTime))
				{
					// 上と同じ(長いので割愛)
					players_[0]->control_chair_ = chairs_[nowroundnum_];
					players_[0]->GetOperate();
					for (int i = 0; i < chairs_.Num(); ++i)
					{
						chairs_[i]->SpawnDefaultController();
						//chairs_[i]->b();
					}

					//chairs_[nowroundnum_]->b();

					// players_[0]->CreateChair();						// 2021/05/08 BeginPlayで生成するように変更
					// chairs_.Add(players_[0]->control_chair_);

					++nowroundnum_;
				}
			}
		}
	}
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
