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
//--------------------------------------------------------------

#include "Chair.h"

// Sets default values
AChair::AChair()
	: m_proot_(NULL)
	, m_first_player_spin_input_flag_(true)
	, m_player_rotation_(0.f)
	, m_player_location_(0.f)
	, m_player_spin_value_(0.f)
	, m_player_spin_angle_(0.f)
	, m_preb_player_spin_input_(0.f)
	, m_first_player_spin_input_angle_(0.f)
	, m_player_spin_cnt_(0)
	, m_input_value_(FVector2D::ZeroVector)
	, m_phase_cnt_(1)
	, m_def_maxspeed(0.f)
	, m_debugmode_(false)
	, m_is_movement_(false)
	, m_phase_(EPhase::kStay)
	, m_input_speed_scale_(0.f)
	, m_input_rotation_scale_(0.f)
	, m_input_spin_scale_(0.f)
	, m_input_slip_scale_(0.f)
	, m_hitstop_scale_(0.f)
	, m_is_movement_scale_(0.f)
	, m_name_("")
	, m_floating_pawn_movement_(NULL)
	, m_pplayermesh_(NULL)
	, m_parrow_(NULL)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ルートコンポーネントの設定
	//m_proot_ = CreateDefaultSubobject<USceneComponent>(TEXT("m_proot_"));
	//m_proot_ = RootComponent;

	// 椅子のメッシュの設定
	//m_pplayermesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_->SetupAttachment(RootComponent);

	// ガイドメッシュの設定
	m_parrow_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_parrow_"));
	m_parrow_->SetupAttachment(m_pplayermesh_);

	// 移動関係のコンポーネントの追加
	m_floating_pawn_movement_ = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("m_floating_pawn_movement_"));
};

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();

	// ヒット時の関数のバインド
	m_pplayermesh_->OnComponentHit.AddDynamic(this, &AChair::ComponentHit);

	m_def_maxspeed = m_floating_pawn_movement_->GetMaxSpeed();
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 移動
	if (m_phase_ == EPhase::kMove)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Move")));
		PlayerMove(DeltaTime);
	}
	// 回転
	else if (m_phase_ == EPhase::kRotation)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Rotation")));
		PlayerRotation(DeltaTime);
	}
	else if (m_phase_ == EPhase::kPawerChange)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("PawerChange")));
	}
	else if (m_phase_ == EPhase::kSpin)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Spin")));
		PlayerSpin(DeltaTime);
	}
	// 滑り
	else if (m_phase_ == EPhase::kSlip && !m_is_movement_)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Slip")));
		PlayerSlip(DeltaTime);
	}
	// 行動終了
	else if (m_phase_ == EPhase::kEnd)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("End")));
	}
}

// Called to bind functionality to input
void AChair::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 左右入力と決定キー
	InputComponent->BindAxis("Horizontal", this, &AChair::SetInputValue_X);
	InputComponent->BindAxis("Vertical", this, &AChair::SetInputValue_Y);
	InputComponent->BindAction("Decide", EInputEvent::IE_Pressed, this, &AChair::NextPhase);

	// 力の強さの変更
	InputComponent->BindAction("Switch_Slip_Power_Lv1", EInputEvent::IE_Pressed, this, &AChair::SwitchSlipPowerLv1);
	InputComponent->BindAction("Switch_Slip_Power_Lv2", EInputEvent::IE_Pressed, this, &AChair::SwitchSlipPowerLv2);
	InputComponent->BindAction("Switch_Slip_Power_Lv3", EInputEvent::IE_Pressed, this, &AChair::SwitchSlipPowerLv3);
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
void AChair::ComponentHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 椅子以外の物にぶつかったら return
	if (Cast<AChair>(OtherActor) == false)
	{
	return;
	}

	if (Cast<AChair>(OtherActor)->m_name_ == "P1Chair" || Cast<AChair>(OtherActor)->m_name_ == "P2Chair" || Cast<AChair>(OtherActor)->m_name_ == "Default")
	{
		if (Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity == FVector::ZeroVector)
		{
			UE_LOG(LogTemp, Warning, TEXT("True"));
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

			// 椅子に当たった状態に変更
			m_is_movement_ = true;
			m_phase_ = EPhase::kEnd;

			// 当たった椅子に速度を与える(現状前方向ベクトルと速度で計算)
			Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity = m_pplayermesh_->GetForwardVector() * m_floating_pawn_movement_->Velocity * m_is_movement_scale_;

			// 椅子の減速処理(X Y Z のいずれかが0だと計算してくれないっぽい？？？？)
			m_floating_pawn_movement_->Velocity.X /= m_hitstop_scale_;
			m_floating_pawn_movement_->Velocity.Y /= m_hitstop_scale_;
			m_floating_pawn_movement_->Velocity.Z /= m_hitstop_scale_;

			if (m_debugmode_)
			{
				// 当たった椅子の速度
				UE_LOG(LogTemp, Warning, TEXT("hit chair speed = %f, %f, %f, "), Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.X, Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.Y, Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.Z);
				// 椅子の速度
				UE_LOG(LogTemp, Warning, TEXT("this after hit speed = %f, %f, %f, "), m_floating_pawn_movement_->Velocity.X, m_floating_pawn_movement_->Velocity.Y, m_floating_pawn_movement_->Velocity.Z);
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
}

void AChair::NextPhase()
{
	if (m_phase_ == EPhase::kSlip)
	{
		return;
	}

	m_phase_cnt_++;
	m_phase_ = EPhase(m_phase_cnt_);

	if (m_phase_ == EPhase::kSpin)
	{
		//m_player_spin_value_ = m_pplayermesh_->GetRelativeRotationFromWorld().Y;
	}

	// 滑る直前にガイドを消す
	if (m_phase_ == EPhase::kSlip)
	{
		DeleteArrow();
		return;
	}
}

void AChair::PlayerMove(const float _deltatime)
{
	// 現在の位置を取得し、入力値に補正をかけて計算後反映
	FVector nowLocation = GetActorLocation();
	m_player_location_ += (m_input_value_.X * m_input_speed_scale_) * _deltatime;
	nowLocation.Y = m_player_location_;
	SetActorLocation(nowLocation);
}

void AChair::PlayerRotation(const float _deltatime)
{
	// 入力値に補正をかけて角度を設定
	m_player_rotation_ += (m_input_value_.X * m_input_rotation_scale_) * _deltatime;
	SetActorRotation(FRotator(0.f, m_player_rotation_, 0.f));
}

void AChair::PlayerSpin(const float _deltatime)
{
	// 入力されたVector2を角度をに変換度、上入力が0度になるように補正後
	// 上入力 -> 0, 右入力 -> 90, 下入力 -> 180, 左入力 -> 270
	m_player_spin_angle_ = (atan2(-m_input_value_.Y, m_input_value_.X) * 180.f / PI) + b;

	// -180°~ 180°の範囲になっている為、0° ~ 360°に補正するためにマイナス値が入った場合360を加算
	if (m_player_spin_angle_ < 0.f)
	{
		m_player_spin_angle_ += 360;
	}

	// 入力がされていない状態ならば入力角度は0°に
	if (m_input_value_.X == 0.f &&  m_input_value_.Y == 0.f)
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
	else if (m_preb_player_spin_input_ - m_player_spin_angle_ < -270.f + (360 * m_player_spin_cnt_ ))
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
	AddMovementInput(Cast<USceneComponent>(m_pplayermesh_)->GetForwardVector(), m_input_slip_scale_);
	UE_LOG(LogTemp, Warning, TEXT("hit chair speed = %f, %f, %f, "), Cast<USceneComponent>(m_pplayermesh_)->GetForwardVector().X, Cast<USceneComponent>(m_pplayermesh_)->GetForwardVector().Y, Cast<USceneComponent>(m_pplayermesh_)->GetForwardVector().Z);
}

void AChair::SwitchSlipPowerLv1()
{
	if (m_phase_ == EPhase::kMove || m_phase_ == EPhase::kRotation)
	{
		if (m_debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Switch_Slip_Power_Lv1")));
		}
		m_floating_pawn_movement_->MaxSpeed = m_def_maxspeed * 0.5f;
	}
}

void AChair::SwitchSlipPowerLv2()
{
	if (m_phase_ == EPhase::kMove || m_phase_ == EPhase::kRotation)
	{
		if (m_debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Switch_Slip_Power_Lv2")));
		}
		m_floating_pawn_movement_->MaxSpeed = m_def_maxspeed;
	}
}

void AChair::SwitchSlipPowerLv3()
{
	if (m_phase_ == EPhase::kMove || m_phase_ == EPhase::kRotation)
	{
		if (m_debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Switch_Slip_Power_Lv3")));
		}
		m_floating_pawn_movement_->MaxSpeed = m_def_maxspeed * 1.5f;
	}
}