//--------------------------------------------------------------
//クラス名：Chair.cpp
//概要	  ：椅子の制御用クラス
//作成日　：2021/04/22
//作成者　：19CU0209 尾崎蒼宙
//更新履歴：2021/04/22 尾崎蒼宙 作成
//			2021/04/23 尾崎蒼宙 ヒット時の処理をBPからC++に移植
//			2021/04/26 尾崎蒼宙 力の強さを変えるプログラムの作成
//			2021/05/07 尾崎蒼宙 タグで処理させていた部分をFStringに変更
//								椅子が椅子以外の物にぶつかった時のクラッシュ修正 
//			2021/05/11 尾崎蒼宙 当たった時のm_name_の検索に「Default」を追加
//			2021/05/12 尾崎蒼宙 構造体の追加
//			2021/05/20 尾崎蒼宙 スピン処理の追加
//			2021/05/24 野田八雲 サウンド追加（一部変数名修正）
//			2021/05/24 尾崎蒼宙 反射処理の仮作成(現段階では未実装)
//			2021/05/26 尾崎蒼宙 スピンの処理で条件式の変更・投げる力の処理の変更
//			2021/05/28 尾崎蒼宙 助走機能の作成・スウィープ機能の作成
//			2021/06/01 尾崎蒼宙 ゲームフローが変わった為一部組みなおし
//			2021/06/03 尾崎蒼宙 仮の目標地点の追加
//			2021/06/03 野田八雲 サウンド追加（ぶつかる音追加）
//--------------------------------------------------------------

#include "Chair.h"

//サウンド系インクルード
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "ActiveSound.h"

// Sets default values
AChair::AChair()
	: m_is_input_add_slip_power_(false)
	, m_first_player_spin_input_flag_(false)
	, m_slip_curve_(false)
	, is_hit_wall_(false)
	, m_is_sweep_(false)
	, m_phase_(EPhase::kStay)
	, m_wall_time(0.f)
	, m_angle_corection_(90.f)
	, m_player_rotation_(0.f)
	, m_player_location_(0.f)
	, m_player_spin_value_(0.f)
	, m_player_spin_angle_(0.f)
	, m_preb_player_spin_input_(0.f)
	, m_first_player_spin_input_angle_(0.f)
	, m_player_spin_cnt_(0)
	, m_forward_vec_(FVector::ZeroVector)
	, m_target_point_location_(FVector::ZeroVector)
	, m_input_value_(FVector2D::ZeroVector)
	, m_audiocomponent_(NULL)

	, m_debugmode_(false)
	, m_ishit_(false)
	, is_entrance_(false)

	, m_input_speed_scale_(0.f)
	, m_input_rotation_scale_(0.f)
	, m_max_speed_(0.f)
	, m_min_speed_(0.f)
	, m_input_add_speed_val_(0.f)
	, m_deceleration_val_(0.f)
	, m_sweep_scale_(0.f)
	, m_pummeled_frame_(0.f)
	, m_input_spin_scale_(0.f)
	, m_input_slip_curve_(0.f)
	, m_hitstop_scale_(0.f)
	, m_is_movement_scale_(0.f)
	, m_name_("")
	, m_pplayermesh_(NULL)
	, m_parrow_(NULL)
	, m_target_point_mesh_(NULL)
	, m_floating_pawn_movement_(NULL)
	, m_deside_sound_(NULL)
	, m_chair_roll_sound_(NULL)
	, m_chair_collide_sound_(NULL)
	, m_speed_percent_(0.f)
{

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 椅子のメッシュの設定
	//m_pplayermesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_->SetupAttachment(RootComponent);

	// ガイドメッシュの設定
	m_parrow_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_parrow_"));
	m_parrow_->SetupAttachment(m_pplayermesh_);

	// 移動関係のコンポーネントの追加
	m_floating_pawn_movement_ = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("m_floating_pawn_movement_"));

	m_target_point_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_target_point_mesh_"));
	m_target_point_mesh_->SetupAttachment(m_pplayermesh_);

	//m_wall_time = 5.f;

	//何の音を再生するかをパスで指定、見つかったらオブジェクトに入れる
	//パスの書き方は、"/Game/Music/BGM or SE/サウンドの名前"（Contentは省略すること）
	//決定音
	static ConstructorHelpers::FObjectFinder<USoundBase> find_sound_deside_(TEXT("/Game/Music/SE/deside"));

	if (find_sound_deside_.Succeeded())
	{
		m_deside_sound_ = find_sound_deside_.Object;
	}
	//椅子が転がる音
	static ConstructorHelpers::FObjectFinder<USoundBase> find_sound_chair_(TEXT("/Game/Music/SE/Move"));
	if (find_sound_chair_.Succeeded())
	{
		m_chair_roll_sound_ = find_sound_chair_.Object;
	}
	//ぶつかった時の音
	static ConstructorHelpers::FObjectFinder<USoundBase> find_sound_chair_collide_(TEXT("/Game/Music/SE/Collide01_"));
	if (find_sound_chair_collide_.Succeeded())
	{
		m_chair_collide_sound_ = find_sound_chair_collide_.Object;
	}

};

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();

	// ヒット時の関数のバインド
	m_pplayermesh_->OnComponentHit.AddDynamic(this, &AChair::ComponentHit);
	m_pplayermesh_->OnComponentBeginOverlap.AddDynamic(this, &AChair::OverlapBegin);

	// m_floating_pawn_movement_ の最大速度を格納
	m_forward_vec_ = FVector::ForwardVector;
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_wall_time += DeltaTime;

	/*
	// 移動
	if (m_phase_ == EPhase::kMove)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Move")));
		PlayerMove(DeltaTime);
	}
	*/
	// 向きの変更
	if (m_phase_ == EPhase::kRotation)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Rotation")));
		PlayerRotation(DeltaTime);
	}
	// パワー調整
	else if (m_phase_ == EPhase::kPowerChange)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("PowerChange")));
		PlayerPowerChange(DeltaTime);
	}
	// 助走
	else if (m_phase_ == EPhase::kEntrance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Entrance")));
		PlayerEntrance(DeltaTime);
	}
	/*
	else if (m_phase_ == EPhase::kSpin)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("kSpin")));
		PlayerSpin(DeltaTime);
		AddMovementInput(m_forward_vec_, 1.f);
	}
	*/  //(2021/06/23 コメント化

	else if (m_phase_ == EPhase::kRide)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Ride")));
		AddMovementInput(m_forward_vec_, 1.f);
	}
	// 滑り
	else if (m_phase_ == EPhase::kSlip)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Slip")));
		PlayerSlip(DeltaTime);
		if (!m_is_sweep_)
		{
			Deceleration(DeltaTime);
		}
		else
		{
			PlayerSweep(DeltaTime);
		}
		m_pplayermesh_->AddRelativeRotation(FRotator(0.f, m_player_spin_value_, 0.f));

		//音楽再生（椅子が転がる音）
				//初回再生
		if (m_audiocomponent_ == nullptr)
		{
			m_audiocomponent_ = UGameplayStatics::SpawnSound2D(GetWorld(), m_chair_roll_sound_, 1.0f, 1.0f, 0.0f, nullptr, false, false);
		}
		//初回再生、または前のフレームでサウンドが再生中じゃない場合、同じ音を初めから再生する
		else if (!m_audiocomponent_->IsPlaying())
		{
			m_audiocomponent_ = UGameplayStatics::SpawnSound2D(GetWorld(), m_chair_roll_sound_, 1.0f, 1.0f, 0.0f, nullptr, false, false);
		}
	}
	// 行動終了
	else if (m_phase_ == EPhase::kEnd)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("End")));

		//ぶつかっても転がる音が再生終了するまでSEが消えないのでここで転がる音を終了
		if (m_audiocomponent_->IsPlaying())
		{
			m_audiocomponent_->Stop();
		}
	}

	m_is_input_add_slip_power_ = false;
}

// Called to bind functionality to input
void AChair::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 左右入力と決定キー
	InputComponent->BindAxis("Horizontal", this, &AChair::SetInputValue_X);
	InputComponent->BindAxis("Vertical", this, &AChair::SetInputValue_Y);
	InputComponent->BindAction("Decide", EInputEvent::IE_Pressed, this, &AChair::InputDecide);
	InputComponent->BindAction("Add_Slip_Power", EInputEvent::IE_Pressed, this, &AChair::PlayerhSlipPower);
	InputComponent->BindAction("Slip_Curve", EInputEvent::IE_Pressed, this, &AChair::SetSlipCurve);
	InputComponent->BindAction("Slip_Curve", EInputEvent::IE_Released, this, &AChair::SetSlipCurve);
	InputComponent->BindAction("Sweep", EInputEvent::IE_Pressed, this, &AChair::SetPlayerSweepFlag);
	InputComponent->BindAction("Sweep", EInputEvent::IE_Released, this, &AChair::SetPlayerSweepFlag);
}

void AChair::SetInputValue_X(const float _axisval)
{
	if (m_debugmode_)
	{
		if (_axisval == 0.f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("not input Horizontal")));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Horizontal")));
		}
	}

	// 入力された値を格納
	m_input_value_.X = _axisval;
}

void AChair::SetInputValue_Y(const float _axisval)
{
	if (m_debugmode_)
	{
		if (_axisval == 0.f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("not input Vertical")));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Vertical")));
		}
	}

	// 入力された値を格納
	m_input_value_.Y = _axisval;
}

void AChair::DeleteArrow()
{
	if (m_parrow_ != NULL)
	{
		Cast<USceneComponent>(m_parrow_)->DestroyComponent();
	}
}

// カプセルコンポーネントを参照している為同じものをBPに追加 -> BPからC++に移植(2021/04/23 尾崎)
void AChair::ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector a = m_audiocomponent_->GetComponentLocation();
	if (m_chair_collide_sound_ != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), a.X, a.Y, a.Z);
		//椅子がぶつかった音を再生
		m_audiocomponent_ = UGameplayStatics::SpawnSound2D(GetWorld(), m_chair_collide_sound_, 1.0f, 1.0f, 0.0f, nullptr, false, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL"));
	}

	// 椅子に当たった場合の処理
	if (Cast<AChair>(OtherActor))
	{
		if (Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity == FVector::ZeroVector)
		{
			if (m_debugmode_)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Chair Hit")));
				// 椅子のメッシュの前方向ベクトル
				UE_LOG(LogTemp, Warning, TEXT("this forwardVector = %f, %f, %f, "), m_pplayermesh_->GetForwardVector().X, m_pplayermesh_->GetForwardVector().Y, m_pplayermesh_->GetForwardVector().Z);
				// floatingpawnmovementの速度
				UE_LOG(LogTemp, Warning, TEXT("this component speed = %f, %f, %f, "), m_floating_pawn_movement_->Velocity.X, m_floating_pawn_movement_->Velocity.Y, m_floating_pawn_movement_->Velocity.Z);
			}

			// 物理の働く向きの設定
			m_pplayermesh_->SetConstraintMode(EDOFMode::XYPlane);

			// 行動終了に
			UE_LOG(LogTemp, Warning, TEXT("a"));
			SetPhase(EPhase::kEnd);

			// 椅子に当てられた為trueに
			Cast<AChair>(OtherActor)->m_ishit_ = true;

			// 当たった椅子に速度を与える(現状前方向ベクトルと速度で計算)
			Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity = m_pplayermesh_->GetForwardVector() * m_floating_pawn_movement_->Velocity * m_is_movement_scale_;

			// 椅子の減速処理(X Y Z のいずれかが0だと計算してくれないっぽい？？？？)
			m_floating_pawn_movement_->Velocity.X /= m_hitstop_scale_;
			m_floating_pawn_movement_->Velocity.Y /= m_hitstop_scale_;
			m_floating_pawn_movement_->Velocity.Z /= m_hitstop_scale_;

			Cast<AChair>(OtherActor)->Ragdoll();

			if (m_debugmode_)
			{
				// 当たった椅子の速度
				UE_LOG(LogTemp, Warning, TEXT("hit chair speed = %f, %f, %f, "), Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.X, Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.Y, Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.Z);
				// 椅子の速度
				UE_LOG(LogTemp, Warning, TEXT("this after hit speed = %f, %f, %f,"), m_floating_pawn_movement_->Velocity.X, m_floating_pawn_movement_->Velocity.Y, m_floating_pawn_movement_->Velocity.Z);
			}
		}
		else
		{
			if (m_debugmode_)
			{
				FVector vec = Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity;
				UE_LOG(LogTemp, Warning, TEXT("false(X = %f, Y = %f, Z = %f)"), vec.X, vec.Y, vec.Z);
			}
		}

	}
	/*
	else if(OtherActor->ActorHasTag("ReflectionWall"))
	{
		if (m_wall_time > 5.f)
		{
			FVector OtherActorForwadVecter;
			OtherActorForwadVecter.X = OtherActor->GetActorRotation().Roll;
			OtherActorForwadVecter.Y = OtherActor->GetActorRotation().Pitch;

			OtherActorForwadVecter = OtherActorForwadVecter.GetSafeNormal();
			OtherActorForwadVecter.Z = 0.f;

			FVector scale;
			scale = (m_forward_vec_ * OtherActorForwadVecter) * -1.f;

			FVector RefrectionVecter;
			RefrectionVecter = m_forward_vec_ + 2.f * scale * OtherActorForwadVecter;
			RefrectionVecter = RefrectionVecter.GetSafeNormal();
			m_forward_vec_ = RefrectionVecter;

			m_wall_time = 0.f;
			UE_LOG(LogTemp, Warning, TEXT("otherVec = %f :: %f :: %f"), OtherActorForwadVecter.X, OtherActorForwadVecter.Y, OtherActorForwadVecter.Z);
			UE_LOG(LogTemp, Warning, TEXT("hansya = %f :: %f :: %f"), RefrectionVecter.X, RefrectionVecter.Y, RefrectionVecter.Z);

			元
						FVector OtherActorForwadVecter;
			OtherActorForwadVecter.X = OtherActor->GetActorRotation().Roll;
			OtherActorForwadVecter.Y = OtherActor->GetActorRotation().Pitch;

			OtherActorForwadVecter = OtherActorForwadVecter.GetSafeNormal();
			OtherActorForwadVecter.Z = 0.f;


			FVector RefrectionVecter;
			//RefrectionVecter = m_forward_vec_ + (2.f * (m_forward_vec_ * OtherActorForwadVecter) * OtherActorForwadVecter);
			RefrectionVecter = m_forward_vec_ + OtherActorForwadVecter;
			RefrectionVecter = RefrectionVecter.GetSafeNormal();
			m_forward_vec_ = RefrectionVecter;

			m_wall_time = 0.f;
			UE_LOG(LogTemp, Warning, TEXT("otherVec = %f :: %f :: %f"), OtherActorForwadVecter.X, OtherActorForwadVecter.Y, OtherActorForwadVecter.Z);
			UE_LOG(LogTemp, Warning, TEXT("hansya = %f :: %f :: %f"), RefrectionVecter.X, RefrectionVecter.Y, RefrectionVecter.Z);


		}


		//m_floating_pawn_movement_->Velocity.X = m_floating_pawn_movement_->Velocity.X * (1.f / m_floating_pawn_movement_->Velocity.X) * (-1.f);
		//m_floating_pawn_movement_->Velocity.Y = m_floating_pawn_movement_->Velocity.Y * (1.f / m_floating_pawn_movement_->Velocity.Y) * (-1.f);
	}
	*/
}

void AChair::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag("ChangeRide"))
	{
		SetPhase(EPhase::kRide);
	}
	/*
		if (OtherActor->ActorHasTag("ChangeSlip"))
	{
		SetPhase(EPhase::kSlip);
	}
	else if (OtherActor->ActorHasTag("ChangeSpin"))
	{
		SetPhase(EPhase::kSpin);
	}
	*/ // (2021/06/23 コメント化)
}

void AChair::SetPhase(const EPhase _phase)
{
	m_phase_ = _phase;
	if (m_phase_ == EPhase::kPowerChange)
	{
		m_target_point_location_ = m_target_point_mesh_->GetComponentLocation();
		if (m_parrow_ != NULL)
		{
			Cast<USceneComponent>(m_target_point_mesh_)->DestroyComponent();
		}

		EnableTargetCollision(false);

	}
	else if (m_phase_ == EPhase::kEntrance)
	{
		m_forward_vec_ = Cast<USceneComponent>(m_pplayermesh_)->GetForwardVector();
		m_forward_vec_.Z = 0.f; // 上に行ってしまう問題があるため0.fで初期化
		DeleteArrow();
		is_entrance_ = true;
	}
	else if (m_phase_ == EPhase::kSlip)
	{
		if (m_debugmode_)
		{
			UE_LOG(LogTemp, Warning, TEXT("m_floating b = %f"), m_floating_pawn_movement_->GetMaxSpeed());
		}

		m_floating_pawn_movement_->MaxSpeed *= m_speed_percent_;

		if (m_debugmode_)
		{
			UE_LOG(LogTemp, Warning, TEXT("m_floating a = %f"), m_speed_percent_);
			UE_LOG(LogTemp, Warning, TEXT("m_floating a = %f"), m_floating_pawn_movement_->GetMaxSpeed());
		}

		m_is_input_ride_ = true;
	}

	//音再生（決定音）
	m_audiocomponent_ = UGameplayStatics::SpawnSound2D(GetWorld(), m_deside_sound_, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void AChair::PlayerMove(const float _deltatime)
{
	// 現在の位置を取得し、入力値に補正をかけて計算後反映
	FVector nowLocation = GetActorLocation();
	m_player_location_ += (m_input_value_.X * m_input_speed_scale_) * _deltatime;
	nowLocation.Y = m_player_location_;
	SetActorLocation(nowLocation, true);
}

void AChair::PlayerRotation(const float _deltatime)
{
	// 現在の位置を取得し、入力値に補正をかけて計算後反映
	FVector nowLocation = m_target_point_mesh_->GetComponentLocation();
	m_player_location_ = (m_input_value_.X * m_input_speed_scale_) * _deltatime;
	m_target_point_mesh_->SetWorldLocation(FVector(nowLocation.X, nowLocation.Y + m_player_location_, nowLocation.Z), true);
}

void AChair::PlayerEntrance(const float _deltatime)
{
	// 前方向ベクトルに向かって移動
	AddMovementInput(m_forward_vec_, 1.f);

	m_floating_pawn_movement_->MaxSpeed += m_input_add_speed_val_ * _deltatime;

	if (m_floating_pawn_movement_->MaxSpeed > m_max_speed_)
	{
		m_floating_pawn_movement_->MaxSpeed = m_max_speed_;
	}

	if (m_debugmode_)
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxSpeed = %f"), m_floating_pawn_movement_->GetMaxSpeed());
	}
}

void AChair::PlayerSpin(const float _deltatime)
{
	// 入力されたVector2を角度をに変換度、上入力が0度になるように補正後
	// 上入力 -> 0, 右入力 -> 90, 下入力 -> 180, 左入力 -> 270
	m_player_spin_angle_ = (atan2(-m_input_value_.Y, m_input_value_.X) * 180.f / PI) + m_angle_corection_;

	// -180°~ 180°の範囲になっている為、0° ~ 360°に補正するためにマイナス値が入った場合360を加算
	if (m_player_spin_angle_ < 0.f)
	{
		m_player_spin_angle_ += 360;
	}

	// 入力がされていない状態ならば入力角度は0°に
	if (m_input_value_.X == 0.f && m_input_value_.Y == 0.f)
	{
		m_player_spin_angle_ = 0.f;
		m_first_player_spin_input_angle_ = 0.f;
		m_first_player_spin_input_flag_ = true;
	}
	// 入力されていない状態から入力が入った時、初めて入力された時のみ値を格納する
	else
	{
		if (m_first_player_spin_input_flag_)
		{
			// 入力を止めるまでは変数に値を入れないように
			m_first_player_spin_input_flag_ = false;
			m_first_player_spin_input_angle_ = m_player_spin_angle_;
		}
	}

	// 初めて入力された角度を引いて、初めて入力された角度が0°(始点)になるように修正
	m_player_spin_angle_ -= m_first_player_spin_input_angle_;

	// 右回りに入力されたか左回りに入力されたかを検知
	if (m_preb_player_spin_input_ - m_player_spin_angle_ > 270.f + (360 * m_player_spin_cnt_))
	{
		++m_player_spin_cnt_;
	}
	else if (m_preb_player_spin_input_ - m_player_spin_angle_ < -270.f + (360 * m_player_spin_cnt_))
	{
		--m_player_spin_cnt_;
	}

	// 合計何度入力が入っているのか確認する用
	m_player_spin_angle_ += 360 * m_player_spin_cnt_;

	m_player_spin_value_ = m_input_spin_scale_ * m_player_spin_cnt_ * _deltatime;
	m_pplayermesh_->AddRelativeRotation(FRotator(0.f, m_player_spin_value_, 0.f));

	if (m_debugmode_)
	{
		UE_LOG(LogTemp, Warning, TEXT("player_spin_cnt = %d"), m_player_spin_cnt_);
		UE_LOG(LogTemp, Warning, TEXT("player_spin_angle = %f"), m_player_spin_angle_);
		UE_LOG(LogTemp, Warning, TEXT("m_player_spin_value_ = %f"), m_player_spin_value_);
	}
	m_preb_player_spin_input_ = m_player_spin_angle_;

}

void AChair::PlayerSlip(const float _deltatime)
{
	if (m_slip_curve_)
	{
		if (m_player_spin_cnt_ != 0)
		{
			if (m_forward_vec_.Y + m_input_slip_curve_ * m_player_spin_cnt_ <= 1.f && m_forward_vec_.Y + m_input_slip_curve_ * m_player_spin_cnt_ >= -1.f)
			{
				//m_forward_vec_.X -= m_input_slip_curve_ * m_player_spin_cnt_;
				m_forward_vec_.Y += m_input_slip_curve_ * m_player_spin_cnt_;
			}
		}
	}

	// 前方向ベクトルに向かって移動
	AddMovementInput(m_forward_vec_, 1.f);

	if (m_debugmode_)
	{
		UE_LOG(LogTemp, Warning, TEXT("hit chair speed = %f, %f, %f, "), m_forward_vec_.X, m_forward_vec_.Y, m_forward_vec_.Z);
	}
}

void AChair::PlayerhSlipPower()
{
	if (m_phase_ != EPhase::kEntrance)
	{
		return;
	}

	m_is_input_add_slip_power_ = true;
}

void AChair::Deceleration(const float _deltatime)
{
	if (!m_is_input_add_slip_power_)
	{
		m_floating_pawn_movement_->MaxSpeed -= m_deceleration_val_ * _deltatime;
		if (m_floating_pawn_movement_->MaxSpeed < m_min_speed_ && m_phase_ == EPhase::kEntrance)
		{
			m_floating_pawn_movement_->MaxSpeed = m_min_speed_;
		}
		else if (m_floating_pawn_movement_->MaxSpeed < 0.f && m_phase_ == EPhase::kSlip)
		{
			SetPhase(EPhase::kEnd);
		}

		if (m_debugmode_)
		{
			UE_LOG(LogTemp, Warning, TEXT("Deceleration/  MaxSpeed = %f"), m_floating_pawn_movement_->GetMaxSpeed());
		}
	}
}

void AChair::PlayerSweep(const float _deltatime)
{
	m_is_sweep_ = true;

	m_floating_pawn_movement_->MaxSpeed -= (m_deceleration_val_ / m_sweep_scale_) * _deltatime;

	if (m_floating_pawn_movement_->MaxSpeed < 0.f && m_phase_ == EPhase::kSlip)
	{
		SetPhase(EPhase::kEnd);
	}

	if (m_debugmode_)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sweep/  MaxSpeed = %f"), m_floating_pawn_movement_->GetMaxSpeed());
	}
}

void AChair::PlayerPowerChange(const float _deltatime)
{
	FVector nowLocation = GetActorLocation();
	m_player_location_ = (m_input_value_.Y * m_input_speed_scale_) * _deltatime;
	this->SetActorLocation(FVector(nowLocation.X + m_player_location_, nowLocation.Y, nowLocation.Z), true);

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), m_target_point_location_));
}

void AChair::InputDecide()
{
	if (m_in_ride_flag_)
	{
		if (m_phase_ == EPhase::kRide)
		{
			SetPhase(EPhase((int)m_phase_ + 1));
		}
	}
	else
	{
		if (m_phase_ >= EPhase(3))
		{
			return;
		}
		else
		{
			SetPhase(EPhase((int)m_phase_ + 1));
		}
	}
}

void AChair::EnableTargetCollision(bool _flag)
{
	if (_flag)
	{
		m_target_point_mesh_->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		m_target_point_mesh_->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}