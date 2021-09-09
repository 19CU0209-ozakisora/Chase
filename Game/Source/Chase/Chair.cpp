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
//			2021/05/09 ���葓�� �R���X�g���N�^�̂��Y����C��
//			2021/05/11 ���葓�� ������������m_name_�̌����ɁuDefault�v��ǉ�
//			2021/05/12 ���葓�� �e�ϐ���m_��ǉ�
//			2021/05/16 ���葓�� �������L�[�ɂ���ăp���[�̕ύX���ł���悤�ɕύX
//			2021/05/20 ���葓�� �X�s�������̒ǉ�
//			2021/05/21 ���葓�� �X�s���ɍő�p�x��ݒ�(forward_vec�ł̃`�F�b�N)
//			2021/05/22 ��c���_ BGM/SE�̏�����ǉ�
//			2021/05/24 ��c���_ ���ꕔ�ϐ����C��
//			2021/05/24 ���葓�� ���ˏ����̉��쐬(���i�K�ł͖�����)
//			2021/05/26 ���葓�� �X�s���̏����ŏ������̕ύX�E������͂̏����̕ύX�E��������DeltaTime���g���Ă��Ȃ����̏C��
//			2021/05/28 ���葓�� �����@�\�̍쐬�E�X�E�B�[�v�@�\�̍쐬
//			2021/06/01 ���葓�� �Q�[���t���[���ς�����׈ꕔ�g�݂Ȃ���
//			2021/06/03 ���葓�� ���̖ڕW�n�_�̒ǉ�
//			2021/06/03 ��c���_ �T�E���h�ǉ��i�Ԃ��鉹�ǉ��j
//			2021/06/07 ���葓�� ����������w��̍ۂ̈ʒu�̕s��C��
//			2021/06/18 ���葓�� �ڕW�n�_�̃��b�V���̓����蔻��𖳌��ɂ���֐��̒ǉ�
//			2021/06/28 ���葓�� ���d�l�̒ǉ��E����Ȃ��Ȃ���State�̃R�����g��
//			2021/07/02 ���葓�� �͂̎d�l�ύX(UI�ɑΉ�)�ׂ̈̏����ύX
//			2021/07/05 ���葓�� ���ϐ����̖����K���ɏ]���Ă��Ȃ������׏C��
//			2021/07/16 ���葓�� ���_�̎d�l�ύX�ɂ��overrap�ɏ����̒ǉ�
//			2021/07/20 ���葓�� �A�j���[�V�����̎����ׂ̈�SetPlayerSweepFlag�֐��̒ǉ�
//			2021/07/28 ���葓�� �X�s���̍č쐬(��x�d�l�������������)
//			2021/08/11 ���葓�� ���͉\�t���O�̒ǉ�
// 			2021/08/20 ���葓�� m_parrow_�̍폜
//			2021/08/27 ���葓�� ���x���w�肵�����x�܂œ��B���Ȃ��s��̏C��
//								�s�v�ȕϐ��̍폜
//			2021/09/02 ���葓�� �s���I�����Ɉ֎q�̉�]���x�����񂾂񉺂��鏈����ǉ�
//								m_player_spin_value_��+m_max_spin_add_rotation_value_���傫��������-m_max_spin_add_rotation_value_�����������ꍇ�ɓK�؂Ȓl���������Ă��Ȃ��������̏C��
//			2021/09/03 �n粗��� �ǁiComponentTag��Wall�̂��́j�ɂ����������ɔ��˂���悤�ɏ����̒ǉ�
// 			2021/09/06 ���葓�� EPhase��kRotation�̍폜
//			2021/09/07 ���葓�� �j�����ꂽ�f�[�^�̕����ƌ���
//			2021/09/08 ���葓�� EPhase��kEntrance��kSlip���폜�����׊Y�������̍폜
//								����L�[�̍폜
//								�v��Ȃ��֐��̍폜
//								�FDeleteArrow()
//								, PlayerEntrance(const float _deltatime)
//								, PlayerRotation(const float _deltatime)
//								, PlayerPowerChange(const float _deltatime)
//			2021/09/09 ���葓�� , m_pplayer_mesh_��UStaticMeshComponent*����USkeltalMeshComponent*�ɕύX
//--------------------------------------------------------------

#include "Chair.h"

//�T�E���h�n�C���N���[�h
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "ActiveSound.h"
// Sets default values
AChair::AChair()
// private
	: m_is_input_add_slip_power_(false)
	, m_hit_wall_(false)
	, m_is_sweep_(false)
	, m_phase_(EPhase::kStay)
	, m_wall_time(0.f)
	, m_player_spin_value_(0.f)
	, m_before_slip_rotation_(0.f)
	, m_stick_slide_time_(0.f)
	, m_forward_vec_(FVector::ZeroVector)
	//, m_target_point_location_(FVector::ZeroVector)
	, m_audiocomponent_(NULL)
// public
	, m_pscore_obj_()
	, m_debugmode_(false)
	, m_is_jumpanimation_end_(true)
	, m_ishit_(false)
	, m_can_input_(true)
	, m_default_speed_(0.f)
	, m_deceleration_val_(0.f)
	, m_sweep_scale_(0.f)
	, m_hitstop_scale_(0.f)
	, m_is_movement_scale_(0.f)
	, m_def_player_posX_(0.f)
	, m_max_spin_add_rotation_value_(0.f)
	, input_spin_scale_(0.f)
	, m_hit_wall_reflection_power_(0.f)
	, m_max_stick_slide_time_(0.f)
	, m_input_value_(FVector2D::ZeroVector)
	, m_name_("")
	, m_pplayermesh_(NULL)
	, m_parrow_(NULL)
	, m_target_point_mesh_(NULL)
	, m_floating_pawn_movement_(NULL)
	, m_deside_sound_(NULL)
	, m_chair_roll_sound_(NULL)
	, m_chair_collide_sound_(NULL)
	//����������������������������������������������
	, FrameCountStart(false)
	, f7(false)
	//����������������������������������������������
{

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �֎q�̃��b�V���̐ݒ�

	m_pplayermesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_->SetupAttachment(RootComponent);


	// �ړ��֌W�̃R���|�[�l���g�̒ǉ�
	m_floating_pawn_movement_ = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("m_floating_pawn_movement_"));

	m_target_point_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_target_point_mesh_"));
	m_target_point_mesh_->SetupAttachment(m_pplayermesh_);

	//���̉����Đ����邩���p�X�Ŏw��A����������I�u�W�F�N�g�ɓ����
	//�p�X�̏������́A"/Game/Music/BGM or SE/�T�E���h�̖��O"�iContent�͏ȗ����邱�Ɓj
	//���艹
	static ConstructorHelpers::FObjectFinder<USoundBase> find_sound_deside_(TEXT("/Game/Music/SE/deside"));

	if (find_sound_deside_.Succeeded())
	{
		m_deside_sound_ = find_sound_deside_.Object;
	}
	//�֎q���]���鉹
	static ConstructorHelpers::FObjectFinder<USoundBase> find_sound_chair_(TEXT("/Game/Music/SE/Move"));
	if (find_sound_chair_.Succeeded())
	{
		m_chair_roll_sound_ = find_sound_chair_.Object;
	}
	//�Ԃ��������̉�
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

	// �q�b�g���̊֐��̃o�C���h
	m_pplayermesh_->OnComponentHit.AddDynamic(this, &AChair::ComponentHit);
	m_pplayermesh_->OnComponentBeginOverlap.AddDynamic(this, &AChair::OverlapBegin);

	// m_floating_pawn_movement_ �̍ő呬�x���i�[
	m_forward_vec_ = FVector::ForwardVector;

	m_default_speed_ = m_floating_pawn_movement_->GetMaxSpeed();

	//����������������������������������������������������������������������������
	// m_pMesh�̏������W��ێ�
	//PlayerLocation = GetActorLocation();

	// m_pMesh��X���W�̕ێ�
	//LocationX = PlayerLocation.X;
	//����������������������������������������������������������������������������
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_wall_time += DeltaTime;

	// ��
	// UE_LOG(LogTemp, Warning, TEXT("m_player_spin_value_ = %f"), m_player_spin_value_);
	// ��

	//fvec�̃��C
	//UKismetSystemLibrary::DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + FVector(m_forward_vec_.X, m_forward_vec_.Y, 0.f) * 500.f, FLinearColor(255, 0, 0, 100), 0, 20);

	// �p���[����
	if (m_phase_ == EPhase::kPowerChange)
	{
		SetSlipPower(DeltaTime);
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("PowerChange")));
	}
	// ����
	else if (m_phase_ == EPhase::kSlip)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Slip")));

		PlayerSpin(DeltaTime);
		PlayerSlip(DeltaTime);
		if (!m_is_sweep_)
		{
			Deceleration(DeltaTime);
		}
		else if(m_is_sweep_ == true && m_is_jumpanimation_end_ == true)
		{
			PlayerSweep(DeltaTime);
		}

		//���y�Đ��i�֎q���]���鉹�j
				//����Đ�
		if (m_audiocomponent_ == nullptr)
		{
			m_audiocomponent_ = UGameplayStatics::SpawnSound2D(GetWorld(), m_chair_roll_sound_, 1.0f, 1.0f, 0.0f, nullptr, false, false);
		}
		//����Đ��A�܂��͑O�̃t���[���ŃT�E���h���Đ�������Ȃ��ꍇ�A�����������߂���Đ�����
		else if (!m_audiocomponent_->IsPlaying())
		{
			m_audiocomponent_ = UGameplayStatics::SpawnSound2D(GetWorld(), m_chair_roll_sound_, 1.0f, 1.0f, 0.0f, nullptr, false, false);
		}
	}
	// �s���I��
	else if (m_phase_ == EPhase::kEnd)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("End")));

		if (m_player_spin_value_ > 0.0001f)
		{
			m_player_spin_value_ -= input_spin_scale_ * DeltaTime;

			if (m_player_spin_value_ < 0.f)
			{
				m_player_spin_value_ = 0.f;
			}
		}
		else if (m_player_spin_value_ < 0.0001f)
		{
			m_player_spin_value_ += input_spin_scale_ * DeltaTime;

			if (m_player_spin_value_ > 0.f)
			{
				m_player_spin_value_ = 0.f;
			}
		}

		m_pplayermesh_->AddRelativeRotation(FRotator(0.f, m_player_spin_value_, 0.f));

		//�Ԃ����Ă��]���鉹���Đ��I������܂�SE�������Ȃ��̂ł����œ]���鉹���I��
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

	// ���E���͂ƌ���L�[
	InputComponent->BindAxis("Horizontal", this, &AChair::SetInputValue_X);
	InputComponent->BindAxis("Vertical", this, &AChair::SetInputValue_Y);
	InputComponent->BindAction("Sweep", EInputEvent::IE_Pressed, this, &AChair::SetPlayerSweepFlag);
	InputComponent->BindAction("Sweep", EInputEvent::IE_Released, this, &AChair::SetPlayerSweepFlag);

	InputComponent->BindAction("F7", EInputEvent::IE_Released, this, &AChair::F7);
}

void AChair::SetInputValue_X(const float _axisval)
{
	if (m_can_input_)
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
	else
	{
		m_input_value_.X = 0.f;
	}
}

void AChair::SetInputValue_Y(const float _axisval)
{
	
	if (m_can_input_)
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
	else
	{
		m_input_value_.Y = 0.f;
	}
	
}

// �J�v�Z���R���|�[�l���g���Q�Ƃ��Ă���ד������̂�BP�ɒǉ� -> BP����C++�ɈڐA(2021/04/23 ����)
void AChair::ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector a = m_audiocomponent_->GetComponentLocation();
	if (m_chair_collide_sound_ != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), a.X, a.Y, a.Z);
		//�֎q���Ԃ����������Đ�
		m_audiocomponent_ = UGameplayStatics::SpawnSound2D(GetWorld(), m_chair_collide_sound_, 1.0f, 1.0f, 0.0f, nullptr, false, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL"));
	}

	// �֎q�ɓ��������ꍇ�̏���
	if (Cast<AChair>(OtherActor))
	{
		if (Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity == FVector::ZeroVector)
		{
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

			// �s���I����
			UE_LOG(LogTemp, Warning, TEXT("a"));
			SetPhase(EPhase::kEnd);

			// �֎q�ɓ��Ă�ꂽ��true��
			Cast<AChair>(OtherActor)->m_ishit_ = true;

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

	// �ǂɂ���������
	if (OtherComp->ComponentHasTag("Wall") && m_hit_wall_ == false)
	{
		m_hit_wall_ = true;

		m_player_spin_value_ *= -1.0f;

		FVector reverseVec = m_forward_vec_;
		reverseVec.Y *= -m_hit_wall_reflection_power_;
		m_forward_vec_ = reverseVec;

		/*
		m_pplayermesh_->SetSimulatePhysics(true);
		m_pplayermesh_->SetConstraintMode(EDOFMode::XYPlane);
		*/
	}
}

void AChair::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("ScoreTrigger"))
	{
		m_pscore_obj_[1] = m_pscore_obj_[0];
		m_pscore_obj_[0] = Cast<AAddScoreTrigger>(OtherActor);
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
	*/ // (2021/06/23 �R�����g��)
}

void AChair::SetPhase(const EPhase _phase)
{
	m_phase_ = _phase;
	// �ePhase�ɕύX�����ۂ̏����ݒ�
	if (m_phase_ == EPhase::kPowerChange)
	{
		//m_target_point_location_ = m_target_point_mesh_->GetComponentLocation();
		if (m_parrow_ != NULL)
		{
			Cast<USceneComponent>(m_target_point_mesh_)->DestroyComponent();
		}

		EnableTargetCollision(false);
		m_def_player_posX_ = this->GetActorLocation().X;
	}
	/*
	else if (m_phase_ == EPhase::kSlip)
	{
		if (m_debugmode_)
		{
			UE_LOG(LogTemp, Warning, TEXT("m_floating component before speed = %f"), m_floating_pawn_movement_->GetMaxSpeed());
		}
		//m_floating_pawn_movement_->MaxSpeed *= m_speed_percent_;

		// ���p�[�Z���g�����Ȃ�ꗥ�̃p�[�Z���g��
		if (m_speed_percent_ < m_min_ride_percent_)
		{
			m_speed_percent_ = m_min_ride_percent_;
		}
		// ���p�[�Z���g�ȏ�Ȃ�ꗥ�̃p�[�Z���g��
		else if (m_speed_percent_ >= m_max_ride_percent_)
		{
			m_speed_percent_ = 1.f;
		}

		if (m_debugmode_)
		{
			UE_LOG(LogTemp, Warning, TEXT("percent = %f"), m_speed_percent_);
			UE_LOG(LogTemp, Warning, TEXT("m_floating component after speed = %f"), m_floating_pawn_movement_->GetMaxSpeed());
		}

		m_is_input_ride_ = true;
		m_before_slip_rotation_ = FMath::Atan2(m_target_point_location_.Y - GetActorLocation().Y, m_target_point_location_.X - GetActorLocation().X);// +90.f;
	}
	*/

	//���Đ��i���艹�j
	m_audiocomponent_ = UGameplayStatics::SpawnSound2D(GetWorld(), m_deside_sound_, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void AChair::PlayerSpin(const float _deltatime)
{
	// ���E���͂������Ă�����
	if (FMath::Abs(m_input_value_.X) > 0.001f || m_hit_wall_)
	{
		float test1;
		float rot_x;
		float rot_y;

		FVector test;

		// ���̃t���[���Ԃŉ�]������l�̎擾
		m_player_spin_value_ += m_input_value_.X * _deltatime * input_spin_scale_;
		test1 = FMath::DegreesToRadians(m_before_slip_rotation_ + m_player_spin_value_);

		// �p�x�̌v�Z			 ���݂̑O�����x�N�g�� + ��]��
		rot_x = FMath::Sin(test1);
		rot_y = FMath::Cos(test1);


		if (!m_hit_wall_)
		{
			// ���
			//FVector test = FVector(rot_x, rot_y, 0.f);
			test = FVector(rot_y, rot_x, 0.f);

			m_forward_vec_ = test;
		}
	}

	if (FMath::Abs(m_player_spin_value_) > m_max_spin_add_rotation_value_)
	{
		if (m_player_spin_value_ > 0.f)
		{
			m_player_spin_value_ = m_max_spin_add_rotation_value_;
			m_pplayermesh_->AddRelativeRotation(FRotator(0.f, m_player_spin_value_, 0.f));
		}
		else
		{
			m_player_spin_value_ = m_max_spin_add_rotation_value_ * -1.f;
			m_pplayermesh_->AddRelativeRotation(FRotator(0.f, m_player_spin_value_, 0.f));
		}
	}
	else
	{
		m_pplayermesh_->AddRelativeRotation(FRotator(0.f, m_player_spin_value_, 0.f));
	}

	if (m_debugmode_)
	{
		UE_LOG(LogTemp, Warning, TEXT("m_player_spin_value_ = %f"), m_player_spin_value_);
	}

}

void AChair::PlayerSlip(const float _deltatime)
{
	// �O�����x�N�g���Ɍ������Ĉړ�
	AddMovementInput(m_forward_vec_, 1.f);

	if (m_debugmode_)
	{
		UE_LOG(LogTemp, Warning, TEXT("hit chair speed = %f, %f, %f, "), m_forward_vec_.X, m_forward_vec_.Y, m_forward_vec_.Z);
	}
}

void AChair::Deceleration(const float _deltatime)
{
	if (!m_is_input_add_slip_power_)
	{
		m_floating_pawn_movement_->MaxSpeed -= m_deceleration_val_ * _deltatime;
		if (m_floating_pawn_movement_->MaxSpeed < 0.f && m_phase_ == EPhase::kSlip)
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

void AChair::SetPlayerSweepFlag()
{
	if (m_is_jumpanimation_end_)
	{
		m_is_sweep_ = !m_is_sweep_;
	}
}

void AChair::SetSlipPower(const float _deltatime)
{
	if (!f7)
	{
		// �X�e�B�b�N����Ԃ����܂ň����ꂽ�珈��
		if (m_input_value_.Y < 0.f)
		{
			// UE_LOG(LogTemp, Error, TEXT("%f"), m_input_value_.Y);
			// �J�E���g�X�^�[�g
			FrameCountStart = true;
		}

		//	�J�E���g�X�^�[�g���Ă���X�e�B�b�N���͂����ꒆ�̎�
		if (m_input_value_.Y != -1.f && FrameCountStart)
		{
			// ���Ԃ����Z
			m_stick_slide_time_ += _deltatime;

			// �X�e�B�b�N�̏�����i�ő�j�̎�
			if (m_input_value_.Y == 1.f)
			{
				// ������������/�ő�̎��Ԃ� 1.0f - ��ǉ����邱�ƂŁA�e�������Ԃ��Z���������Ȃ�悤��
				float Alpha = 1.f - (m_stick_slide_time_ / m_max_stick_slide_time_);
				// �������|���Z
				m_floating_pawn_movement_->MaxSpeed *= Alpha;
				SetPhase(EPhase::kSlip);
				FrameCountStart = false;
			}
		}
	}

	if (f7)
	{
		// �X�e�B�b�N����Ԃ����܂ň����ꂽ�珈��
		if (m_input_value_.Y < 0.f)
		{
			// UE_LOG(LogTemp, Error, TEXT("%f"), m_input_value_.Y);
			// �J�E���g�X�^�[�g
			FrameCountStart = true;
		}

		//	�J�E���g�X�^�[�g���Ă���X�e�B�b�N���͂����ꒆ�̎�
		if (m_input_value_.Y != -1.f && FrameCountStart)
		{
			// ���Ԃ����Z
			m_stick_slide_time_ += _deltatime;

			// �X�e�B�b�N�̏�����i�ő�j�̎�
			if (m_input_value_.Y >= 0.f)
			{
				// ������������/�ő�̎��Ԃ� 1.0f - ��ǉ����邱�ƂŁA�e�������Ԃ��Z���������Ȃ�悤��
				float Alpha = 1.f - (m_stick_slide_time_ / m_max_stick_slide_time_);
				// �������|���Z
				m_floating_pawn_movement_->MaxSpeed *= Alpha;
				SetPhase(EPhase::kSlip);
				FrameCountStart = false;
			}
		}
	}
}

void AChair::F7()
{
	if (!FrameCountStart)
		f7 = !f7;

	if (f7) { UE_LOG(LogTemp, Error, TEXT("f7 = true")); }
	else if (!f7) { UE_LOG(LogTemp, Error, TEXT("f7 = false")); }
}