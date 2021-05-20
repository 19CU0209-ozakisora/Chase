//--------------------------------------------------------------
//�N���X���FChair.cpp
//�T�v	  �F�֎q�̐���p�N���X
//�쐬���@�F2021/04/22
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/04/22 ���葓�� �쐬
//			2021/04/23 ���葓�� �q�b�g���̏�����BP����C++�ɈڐA
//			2021/04/26 ���葓�� �͂̋�����ς���v���O�����̍쐬
//			2021/05/07 ���葓�� �^�O�ŏ��������Ă���������FString�ɕύX
//								�֎q���֎q�ȊO�̕��ɂԂ��������̃N���b�V���C�� 
//			2021/05/11 ���葓�� ������������m_name_�̌����ɁuDefault�v��ǉ�
//			2021/05/12 ���葓�� �\���̂̒ǉ�
//			2021/05/20 ���葓�� �X�s�������̒ǉ�
//--------------------------------------------------------------

#include "Chair.h"

// Sets default values
AChair::AChair()
	: m_proot_(NULL)
	, m_first_player_spin_input_flag_(true)
	, m_angle_corection_(90.f)
	, m_player_rotation_(0.f)
	, m_player_location_(0.f)
	, m_player_spin_value_(0.f)
	, m_player_spin_angle_(0.f)
	, m_preb_player_spin_input_(0.f)
	, m_first_player_spin_input_angle_(0.f)
	, m_player_spin_cnt_(0)
	, m_power_level_(1)
	, m_forward_vec_(FVector::ZeroVector)
	, m_input_value_(FVector2D::ZeroVector)
	, m_phase_cnt_(1)
	, m_def_maxspeed_(0.f)
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

	// �֎q�̃��b�V���̐ݒ�
	//m_pplayermesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_->SetupAttachment(RootComponent);

	// �K�C�h���b�V���̐ݒ�
	m_parrow_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_parrow_"));
	m_parrow_->SetupAttachment(m_pplayermesh_);

	// �ړ��֌W�̃R���|�[�l���g�̒ǉ�
	m_floating_pawn_movement_ = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("m_floating_pawn_movement_"));
};

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();

	// �q�b�g���̊֐��̃o�C���h
	m_pplayermesh_->OnComponentHit.AddDynamic(this, &AChair::ComponentHit);
	// m_floating_pawn_movement_ �̍ő呬�x���i�[
	m_def_maxspeed_ = m_floating_pawn_movement_->GetMaxSpeed();
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �ړ�
	if (m_phase_ == EPhase::kMove)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Move")));
		PlayerMove(DeltaTime);
	}
	// ��]
	else if (m_phase_ == EPhase::kRotation)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Rotation")));
		PlayerRotation(DeltaTime);
	}
	// �X�s��
	else if (m_phase_ == EPhase::kSpin)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Spin")));
		PlayerSpin(DeltaTime);
	}
	// �͂̕ύX
	else if (m_phase_ == EPhase::kPawerChange)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("PowerChange")));
		m_pplayermesh_->AddRelativeRotation(FRotator(0.f, m_player_spin_value_, 0.f));
	}
	// ����
	else if (m_phase_ == EPhase::kSlip && !m_is_movement_)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Slip")));
		m_pplayermesh_->AddRelativeRotation(FRotator(0.f, m_player_spin_value_, 0.f));
		PlayerSlip(DeltaTime);
	}
	// �s���I��
	else if (m_phase_ == EPhase::kEnd)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("End")));
	}
}

// Called to bind functionality to input
void AChair::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ���E���͂ƌ���L�[
	InputComponent->BindAxis("Horizontal", this, &AChair::SetInputValue_X);
	InputComponent->BindAxis("Vertical", this, &AChair::SetInputValue_Y);
	InputComponent->BindAction("Decide", EInputEvent::IE_Pressed, this, &AChair::NextPhase);

	// �͂̋����̕ύX
	InputComponent->BindAction("Switch_Slip_Power_Lv1", EInputEvent::IE_Pressed, this, &AChair::SwitchSlipPowerLv1);
	InputComponent->BindAction("Switch_Slip_Power_Lv2", EInputEvent::IE_Pressed, this, &AChair::SwitchSlipPowerLv2);
	InputComponent->BindAction("Switch_Slip_Power_Lv3", EInputEvent::IE_Pressed, this, &AChair::SwitchSlipPowerLv3);
	InputComponent->BindAction("Switch_Slip_Power", EInputEvent::IE_Pressed, this, &AChair::SwitchSlipPower);

	// �����Ă���Ƃ��ɋȂ��邩�ۂ�
	InputComponent->BindAction("Slip_Curve", EInputEvent::IE_Pressed, this, &AChair::SetSlipCurve);
	InputComponent->BindAction("Slip_Curve", EInputEvent::IE_Released, this, &AChair::SetSlipCurve);
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

	// ���͂��ꂽ�l���i�[
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

	// ���͂��ꂽ�l���i�[
	m_input_value_.Y = _axisval;
}

void AChair::DeleteArrow()
{
	if (m_parrow_ != NULL)
	{
		Cast<USceneComponent>(m_parrow_)->DestroyComponent();
	}
}

// �J�v�Z���R���|�[�l���g���Q�Ƃ��Ă���ד������̂�BP�ɒǉ� -> BP����C++�ɈڐA(2021/04/23 ����)
void AChair::ComponentHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// �֎q�ȊO�̕��ɂԂ������� return
	if (Cast<AChair>(OtherActor) == false)
	{
	return;
	}

	if (Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity == FVector::ZeroVector)
	{
		UE_LOG(LogTemp, Warning, TEXT("True"));
		if (m_debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Chair Hit")));
			// �֎q�̃��b�V���̑O�����x�N�g��
			UE_LOG(LogTemp, Warning, TEXT("this forwardVector = %f, %f, %f, "), m_pplayermesh_->GetForwardVector().X, m_pplayermesh_->GetForwardVector().Y, m_pplayermesh_->GetForwardVector().Z);
			// floatingpawnmovement�̑��x
			UE_LOG(LogTemp, Warning, TEXT("this component speed = %f, %f, %f, "), m_floating_pawn_movement_->Velocity.X, m_floating_pawn_movement_->Velocity.Y, m_floating_pawn_movement_->Velocity.Z);
		}

		// �����̓��������̐ݒ�
		m_pplayermesh_->SetConstraintMode(EDOFMode::XYPlane);

		// �֎q�ɓ���������ԂɕύX
		m_is_movement_ = true;
		m_phase_ = EPhase::kEnd;

		// ���������֎q�ɑ��x��^����(����O�����x�N�g���Ƒ��x�Ōv�Z)
		Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity = m_pplayermesh_->GetForwardVector() * m_floating_pawn_movement_->Velocity * m_is_movement_scale_;

		// �֎q�̌�������(X Y Z �̂����ꂩ��0���ƌv�Z���Ă���Ȃ����ۂ��H�H�H�H)
		m_floating_pawn_movement_->Velocity.X /= m_hitstop_scale_;
		m_floating_pawn_movement_->Velocity.Y /= m_hitstop_scale_;
		m_floating_pawn_movement_->Velocity.Z /= m_hitstop_scale_;

		Cast<AChair>(OtherActor)->Ragdoll();

		if (m_debugmode_)
		{
			// ���������֎q�̑��x
			UE_LOG(LogTemp, Warning, TEXT("hit chair speed = %f, %f, %f, "), Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.X, Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.Y, Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.Z);
			// �֎q�̑��x
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

void AChair::NextPhase()
{
	if (m_phase_ == EPhase::kSlip || m_phase_ == EPhase::kEnd)
	{
		return;
	}

	m_phase_cnt_++;
	m_phase_ = EPhase(m_phase_cnt_);

	// ��]�̎��Ɍ���L�[����������
	if (m_phase_ == EPhase::kSpin)
	{
		m_forward_vec_ = Cast<USceneComponent>(m_pplayermesh_)->GetForwardVector();
		DeleteArrow();
	}
}

void AChair::PlayerMove(const float _deltatime)
{
	// ���݂̈ʒu���擾���A���͒l�ɕ␳�������Čv�Z�㔽�f
	FVector nowLocation = GetActorLocation();
	m_player_location_ += (m_input_value_.X * m_input_speed_scale_) * _deltatime;
	nowLocation.Y = m_player_location_;
	SetActorLocation(nowLocation);
}

void AChair::PlayerRotation(const float _deltatime)
{
	// ���͒l�ɕ␳�������Ċp�x��ݒ�
	m_player_rotation_ += (m_input_value_.X * m_input_rotation_scale_) * _deltatime;
	SetActorRotation(FRotator(0.f, m_player_rotation_, 0.f));
}

void AChair::PlayerSpin(const float _deltatime)
{
	// ���͂��ꂽVector2���p�x���ɕϊ��x�A����͂�0�x�ɂȂ�悤�ɕ␳��
	// ����� -> 0, �E���� -> 90, ������ -> 180, ������ -> 270
	m_player_spin_angle_ = (atan2(-m_input_value_.Y, m_input_value_.X) * 180.f / PI) + m_angle_corection_;

	// -180��~ 180���͈̔͂ɂȂ��Ă���ׁA0�� ~ 360���ɕ␳���邽�߂Ƀ}�C�i�X�l���������ꍇ360�����Z
	if (m_player_spin_angle_ < 0.f)
	{
		m_player_spin_angle_ += 360;
	}

	// ���͂�����Ă��Ȃ���ԂȂ�Γ��͊p�x��0����
	if (m_input_value_.X == 0.f &&  m_input_value_.Y == 0.f)
	{
		m_player_spin_angle_ = 0.f;
		m_first_player_spin_input_angle_ = 0.f;
		m_first_player_spin_input_flag_ = true;
	}
	// ���͂���Ă��Ȃ���Ԃ�����͂����������A���߂ē��͂��ꂽ���̂ݒl���i�[����
	else
	{
		if (m_first_player_spin_input_flag_)
		{	
			// ���͂��~�߂�܂ł͕ϐ��ɒl�����Ȃ��悤��
			m_first_player_spin_input_flag_ = false;
			m_first_player_spin_input_angle_ = m_player_spin_angle_;
		}
	}

	// ���߂ē��͂��ꂽ�p�x�������āA���߂ē��͂��ꂽ�p�x��0��(�n�_)�ɂȂ�悤�ɏC��
	m_player_spin_angle_ -= m_first_player_spin_input_angle_;

	// �E���ɓ��͂��ꂽ�������ɓ��͂��ꂽ�������m
	if (m_preb_player_spin_input_ - m_player_spin_angle_ > 270.f + (360 * m_player_spin_cnt_))
	{
		++m_player_spin_cnt_;
	}
	else if (m_preb_player_spin_input_ - m_player_spin_angle_ < -270.f + (360 * m_player_spin_cnt_ ))
	{
		--m_player_spin_cnt_;
	}

	// ���v���x���͂������Ă���̂��m�F����p
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
		if (m_player_spin_cnt_ > 0)
		{
			if (m_forward_vec_.X > 0.1f)
			{
				m_forward_vec_.X -= m_input_slip_curve_ * m_player_spin_cnt_;
				m_forward_vec_.Y += m_input_slip_curve_ * m_player_spin_cnt_;
			}
		}
		else if (m_player_spin_cnt_ < 0)
		{
			if (m_forward_vec_.X > 0.1f)
			{
				m_forward_vec_.X += m_input_slip_curve_ * m_player_spin_cnt_;
				m_forward_vec_.Y -= m_input_slip_curve_ * m_player_spin_cnt_;
			}

		}
	}
	AddMovementInput(m_forward_vec_, m_input_slip_scale_);
	//AddMovementInput(GetActorForwardVector(), m_input_slip_scale_);

	UE_LOG(LogTemp, Warning, TEXT("hit chair speed = %f, %f, %f, "),m_forward_vec_.X, m_forward_vec_.Y, m_forward_vec_.Z);
}

void AChair::SwitchSlipPowerLv1()
{
	if (m_phase_ == EPhase::kPawerChange)
	{
		if (m_debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Switch_Slip_Power_Lv1")));
		}
		m_floating_pawn_movement_->MaxSpeed = m_def_maxspeed_ * 0.5f;
	}
}

void AChair::SwitchSlipPowerLv2()
{
	if (m_phase_ == EPhase::kPawerChange)
	{
		if (m_debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Switch_Slip_Power_Lv2")));
		}
		m_floating_pawn_movement_->MaxSpeed = m_def_maxspeed_;
	}
}

void AChair::SwitchSlipPowerLv3()
{
	if (m_phase_ == EPhase::kPawerChange)
	{
		if (m_debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Switch_Slip_Power_Lv3")));
		}
		m_floating_pawn_movement_->MaxSpeed = m_def_maxspeed_ * 1.5f;
	}
}

void AChair::SwitchSlipPower()
{
	if (m_phase_ == EPhase::kPawerChange)
	{

		++m_power_level_;
		m_power_level_ %= 3;

		if (m_power_level_ == 0)
		{
			if (m_debugmode_)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Switch_Slip_Power_Lv1")));
			}
			m_floating_pawn_movement_->MaxSpeed = m_def_maxspeed_ * 0.5f;
		}
		else if (m_power_level_ == 1)
		{
			if (m_debugmode_)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Switch_Slip_Power_Lv2")));
			}
			m_floating_pawn_movement_->MaxSpeed = m_def_maxspeed_;
		}
		else
		{
			if (m_debugmode_)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Switch_Slip_Power_Lv3")));
			}
			m_floating_pawn_movement_->MaxSpeed = m_def_maxspeed_ * 1.5f;
		}
	}
}

void AChair::SetSlipCurve()
{
	m_slip_curve_ = !m_slip_curve_;
}