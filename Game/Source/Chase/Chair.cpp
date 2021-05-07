// Fill out your copyright notice in the Description page of Project Settings.


#include "Chair.h"

// Sets default values
AChair::AChair()
	: m_proot_(NULL)
	, player_rotation_(0.f)
	, player_location_(0.f)
	, input_value_(0.f)
	, phase_cnt_(0.f)
	, def_maxspeed(0.f)
	, debugmode_(false)
	, is_movement_(false)
	, phase_(EPhase::kMove)
	, input_speed_scale_(0.f)
	, input_rotation_scale_(0.f)
	, input_slip_scale_(0.f)
	, hitstop_scale_(0.f)
	, m_pplayermesh_(NULL)
	, m_parrow_(NULL)
	, m_floating_pawn_movement_(NULL)
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


	def_maxspeed = m_floating_pawn_movement_->GetMaxSpeed();
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 移動
	if (phase_ == EPhase::kMove)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Move"), player_rotation_));
		PlayerMove(DeltaTime);
	}
	// 回転
	else if (phase_ == EPhase::kRotation)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Rotation"), player_rotation_));
		PlayerRotation(DeltaTime);
	}
	// 滑り
	else if (phase_ == EPhase::kSlip && !is_movement_)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Slip"), player_rotation_));
		PlayerSlip(DeltaTime);
	}
	// 行動終了
	else if (phase_ == EPhase::kEnd)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("End"), player_rotation_));
	}
}

// Called to bind functionality to input
void AChair::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 左右入力と決定キー
	InputComponent->BindAxis("TurnRate", this, &AChair::SetInputValue);
	InputComponent->BindAction("Decide", EInputEvent::IE_Pressed, this, &AChair::NextPhase);

	// 力の強さの変更
	InputComponent->BindAction("Switch_Slip_Power_Lv1", EInputEvent::IE_Pressed, this, &AChair::SwitchSlipPowerLv1);
	InputComponent->BindAction("Switch_Slip_Power_Lv2", EInputEvent::IE_Pressed, this, &AChair::SwitchSlipPowerLv2);
	InputComponent->BindAction("Switch_Slip_Power_Lv3", EInputEvent::IE_Pressed, this, &AChair::SwitchSlipPowerLv3);
}

void AChair::SetInputValue(const float _axisval)
{
	if (debugmode_)
	{
		if (_axisval == 0.f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("not input TurnRate"), player_rotation_));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input TurnRate"), player_rotation_));
		}
	}

	// 入力された値を格納
	input_value_ = _axisval;
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
	// とまっている かつ 当たった対象のタグがPlayerだった時
	if(Cast<AChair>(OtherActor)->name_ == "P1Chair" || Cast<AChair>(OtherActor)->name_ == "P2Chair")
	//if (OtherActor->ActorHasTag("P1Chair") || OtherActor->ActorHasTag("P2Chair") || OtherActor->ActorHasTag("Player")) // Playerはそのうち消します
	{
		if (Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity == FVector::ZeroVector)
		{
			UE_LOG(LogTemp, Warning, TEXT("True"));
			if (debugmode_)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Chair Hit")));
				// 椅子のメッシュの前方向ベクトル
				UE_LOG(LogTemp, Warning, TEXT("this forwardVector = %f, %f, %f, "), m_pplayermesh_->GetForwardVector().X, m_pplayermesh_->GetForwardVector().Y, m_pplayermesh_->GetForwardVector().Z);
				// floatingpawnmovementの速度
				UE_LOG(LogTemp, Warning, TEXT("this component speed = %f, %f, %f, "), m_floating_pawn_movement_->Velocity.X, m_floating_pawn_movement_->Velocity.Y, m_floating_pawn_movement_->Velocity.Z);
			}

			// 物理の働く向きの設定
			//m_pplayermesh_->SetConstraintMode(EDOFMode::XYPlane);

			// 椅子に当たった状態に変更
			//is_movement_ = true;
			//phase_ = EPhase::kEnd;

			// 当たった椅子に速度を与える(現状前方向ベクトルと速度で計算)
			Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity = m_pplayermesh_->GetForwardVector() * m_floating_pawn_movement_->Velocity * is_movement_scale_;

			// 椅子の減速処理(X Y Z のいずれかが0だと計算してくれないっぽい？？？？)
			//m_floating_pawn_movement_->Velocity.X /= hitstop_scale_;
			//m_floating_pawn_movement_->Velocity.Y /= hitstop_scale_;
			//m_floating_pawn_movement_->Velocity.Z /= hitstop_scale_;

			if (debugmode_)
			{
				// 当たった椅子の速度
				UE_LOG(LogTemp, Warning, TEXT("hit chair speed = %f, %f, %f, "), Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.X, Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.Y, Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.Z);
				// 椅子の速度
				UE_LOG(LogTemp, Warning, TEXT("this after hit speed = %f, %f, %f, "), m_floating_pawn_movement_->Velocity.X, m_floating_pawn_movement_->Velocity.Y, m_floating_pawn_movement_->Velocity.Z);
			}
		}
		else
		{
			if (debugmode_)
			{
				FVector a = Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity;
				UE_LOG(LogTemp, Warning, TEXT("false(X = %f, Y = %f, Z = %f)"), a.X, a.Y, a.Z);
			}
		}
	}
}

void AChair::NextPhase()
{
	if (phase_ == EPhase::kSlip)
	{
		return;
	}

	phase_cnt_++;
	phase_ = EPhase(phase_cnt_);

	// 滑る直前にガイドを消す
	if (phase_ == EPhase::kSlip)
	{
		DeleteArrow();
		return;
	}
}

void AChair::PlayerMove(const float _deltatime)
{
	// 現在の位置を取得し、入力値に補正をかけて計算後反映
	FVector nowLocation = GetActorLocation();
	player_location_ += (input_value_ * input_speed_scale_) * _deltatime;
	nowLocation.Y = player_location_;
	SetActorLocation(nowLocation);
}

void AChair::PlayerRotation(const float _deltatime)
{
	// 入力値に補正をかけて角度を設定
	player_rotation_ += (input_value_* input_rotation_scale_) * _deltatime;
	Cast<USceneComponent>(m_pplayermesh_)->SetWorldRotation(FRotator(0.f, player_rotation_, 0.f));
}

void AChair::PlayerSlip(const float _deltatime)
{
	AddMovementInput(Cast<USceneComponent>(m_pplayermesh_)->GetForwardVector(), input_slip_scale_);
}

void AChair::SwitchSlipPowerLv1()
{
	if (phase_ == EPhase::kMove || phase_ == EPhase::kRotation)
	{
		if (debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Switch_Slip_Power_Lv1")));
		}
		m_floating_pawn_movement_->MaxSpeed = def_maxspeed * 0.5f;
	}
}

void AChair::SwitchSlipPowerLv2()
{
	if (phase_ == EPhase::kMove || phase_ == EPhase::kRotation)
	{
		if (debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Switch_Slip_Power_Lv2")));
		}
		m_floating_pawn_movement_->MaxSpeed = def_maxspeed;
	}
}

void AChair::SwitchSlipPowerLv3()
{
	if (phase_ == EPhase::kMove || phase_ == EPhase::kRotation)
	{
		if (debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Switch_Slip_Power_Lv3")));
		}
		m_floating_pawn_movement_->MaxSpeed = def_maxspeed * 1.5f;
	}
}
