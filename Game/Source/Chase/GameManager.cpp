//--------------------------------------------------------------
//�N���X���FGameManager.cpp
//�T�v	  �F�֎q�̐���p�N���X
//�쐬���@�F2021/04/22
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/04/26 ���葓�� �쐬
//			2021/04/23 ���葓�� �q�b�g���̏�����BP����C++�ɈڐA
//			2021/05/04 ���葓�� ���݂̃^�[���E�ǂ���̔Ԃ��E�֎q�̐����Ȃǂ�ǉ�
//			2021/05/07 ���葓�� GameManager�̏C��
//			2021/05/10 ���葓�� �����ꂽ�f�[�^�̕���
//								m_PlayerNumberName��m_name_�ɕύX
//								m_pAchair��m_chairs_�ɕύX(�����̕ύX)
//			2021/05/21 ���葓�� �֎q�̏�̐l�Ԃ����������̒ǉ�
//			2021/05/21 ���葓�� �����ꂽ�f�[�^�̕���
//--------------------------------------------------------------

//�C���N���[�h
#include "GameManager.h"
#include "Chair.h"

//�R���X�g���N�^
AGameManager::AGameManager()
	// ����
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
	,m_thisLocation(FVector::ZeroVector)
	, m_Player1Turn(0)
	, m_Player2Turn(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

//�Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<AHouseCenter> AHouseCenterfindClass;
	AHouseCenterfindClass = AHouseCenter::StaticClass();
	TArray<AActor*> AHouseCentertemp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHouseCenterfindClass, AHouseCentertemp);
	
	for (int i = 0; i < AHouseCentertemp.Num(); ++i)
	{
		//�n�E�X�̒��S���W���i�[
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

	//����������������������������������������������������������������������������
	// �ؒǉ�
	// GameInstance�̎��Ԃ��������Ă���֐��̌Ăяo��
	Instance = UInstance::GetInstance();

	Instance->m_teamPoint1P = 0;
	Instance->m_teamPoint2P = 0;

	if (Instance)
	{
		//UE_LOG(LogTemp, Error, TEXT("%d"), NumberOfTurns->m_Turn);
		// �ʂ̃��x���Őݒ肵���^�[��������
		m_maxroundnum_ = Instance->m_Turn;

		// Player1,Player2�̃^�[�����̐ݒ�
		m_Player1Turn = m_maxroundnum_ / 2;
		m_Player2Turn = m_Player1Turn;
	}
	//����������������������������������������������������������������������������

	// �Q�[���̍ő僉�E���h�� / 2 (for���̒���Player1��Player2�̈֎q�̐����𓯎��ɍs�����߁Am_maxroundnum_ / 2�ɂ��Ă��܂�)
	for (int i = 0; i < m_maxroundnum_ / 2; ++i)
	{
		// �֎q�̐����y�шʒu�̎w��A�Ǘ����邽�߂ɔz��Ɋi�[
		m_players_[0]->CreateChair();
		m_players_[0]->control_chair_->SetActorLocation(FVector(m_players_[0]->chair_stack_->GetComponentLocation().X, m_players_[0]->chair_stack_->GetComponentLocation().Y + i * 250, m_players_[0]->chair_stack_->GetComponentLocation().Z), false, nullptr, ETeleportType::TeleportPhysics);
		m_chairs_.Add(m_players_[0]->control_chair_);

		m_players_[1]->CreateChair();
		m_players_[1]->control_chair_->SetActorLocation(FVector(m_players_[1]->chair_stack_->GetComponentLocation().X, m_players_[1]->chair_stack_->GetComponentLocation().Y + i * 250, m_players_[1]->chair_stack_->GetComponentLocation().Z), false, nullptr, ETeleportType::TeleportPhysics);
		m_chairs_.Add(m_players_[1]->control_chair_);
	}

	// 2021/05/10 ���� �Q�[���J�n���ɐ������������̂��擾���Ă���׃R�����g��(��������K�v�Ȃ�)
	/*
	//�T�������N���X������
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

	//Player[0]���Ǘ����Ă���֎q�̎��_�ɕύX
	m_players_[0]->control_chair_ = m_chairs_[0];
	m_players_[0]->GetOperate();
	++m_nowroundnum_;
}

//���t���[���X�V����
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ��^�[���̎�(Player1�̔�)
	if (m_nowroundnum_ % 2 == 1)
	{
		// NULL�`�F�b�N
		if (m_players_[0]->control_chair_ != NULL)
		{
			// ���ݑ��삵�Ă���֎q���֎q�ɓ����� or ��胉�C���܂ōs���Ă��܂�����
			if (m_players_[0]->control_chair_->GetPhase() == EPhase::kEnd)
			{
				// ���b���o�ߌ�A���삷��֎q�̕ύX
				if (TimeCheck(DeltaTime))
				{
					//NextRound();
				}
				//������������������������������������������
				// �ؒǉ�::Player1�̃^�[���������炷
				if (m_Player1Turn == m_Player2Turn)
				{
					m_Player1Turn--;
				}
				//������������������������������������������
			}
		}

	}
	// ��^�[���̎�(Player2�̔�)
	else if (m_nowroundnum_ % 2 == 0)
	{
		// NULL�`�F�b�N
		if (m_players_[1]->control_chair_ != NULL)
		{
			// ���ݑ��삵�Ă���֎q���֎q�ɓ����� or ��胉�C���܂ōs���Ă��܂�����
			if (m_players_[1]->control_chair_->GetPhase() == EPhase::kEnd)
			{
				// ���b���o�ߌ�A���삷��֎q�̕ύX
				if (TimeCheck(DeltaTime))
				{
					//NextRound();
				}
				//������������������������������������������
				// �ؒǉ�::Player2�̃^�[���������炷
				if (m_Player1Turn < m_Player2Turn)
				{
					m_Player2Turn--;
				}
				//������������������������������������������
			}
		}
	}

	//���E���h��10�ɂȂ�����
	if (m_nowroundnum_ == 10 && m_players_[1]->control_chair_->GetPhase() == EPhase::kEnd)
	{
		//�֎q��10�~�܂������̏���
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
			m_chairs_[i]->m_floating_pawn_movement_->Velocity = FVector::ZeroVector;
		}
		time_cnt_ = 0.f;
		return true;
	}
}

//�֎q���~�܂������̏���
void AGameManager::StopChair()
{
	//���������֎q�̃I�u�W�F�N�g�A���W���擾
	for (int i = 0; i < 10; ++i)
	{
		m_ChairDistance[i] = sqrt(((m_thisLocation.X - m_chairs_[i]->GetActorLocation().X) * (m_thisLocation.X - m_chairs_[i]->GetActorLocation().X))
			+ ((m_thisLocation.Y - m_chairs_[i]->GetActorLocation().Y) * (m_thisLocation.Y - m_chairs_[i]->GetActorLocation().Y)));
	}

	//���O�m�F�p
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

	//�֎q�̋߂����\�[�g
	ChairSort();
	//���_�v�Z
	SetPoint();
}

//�֎q�̋߂����Ƀ\�[�g
void AGameManager::ChairSort()
{
	//�ϐ��錾
	//�����p�ϐ�
	AChair* tmp;
	//�z��ԍ��p�ϐ�
	int dataCount01;
	int dataCount02;

	//2�_�Ԃ̋����Ń\�|�g��������
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
	//���O�Ŋm�F�p
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

//���_�v�Z
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
		//  ���̃^�O�Ƀ|�C���g������
		m_teamPoint1P += i + 1 + m_teamPoint1P;
	}
	else if (m_chairs_[0]->m_name_ == "P2Chair")
	{
		m_teamPoint2P += i + 1 + m_teamPoint2P;
	}
	UE_LOG(LogTemp, Warning, TEXT("P1Point %d"), m_teamPoint1P);
	UE_LOG(LogTemp, Warning, TEXT("P2Point %d"), m_teamPoint2P);

	//���_�v�Z��ATick()�𖳌��ɂ���
	PrimaryActorTick.SetTickFunctionEnable(false);
}

void AGameManager::AddScore()
{
	// �֎q�̐������J��Ԃ�
	for (int i = 0; i < m_chairs_.Num() - 1; ++i)
	{
		// NULL�`�F�b�N
		if (m_chairs_[i] != NULL)
		{
			// �֎q�Ƃ��ꂼ��̃X�R�A�R���W�����̋������i�[���邽�߂̕ϐ�
			float Scoreobj1_Distance = 0.f;
			float Scoreobj2_Distance = 0.f;

			// �Q�Ƃ��Ă���֎q�ɃX�R�A�R���W�������i�[����Ă��邩�m�F���Ă��狗�����v�Z
			if (m_chairs_[i]->m_pscore_obj_[0] != NULL)
			{
				Scoreobj1_Distance = FMath::Abs(m_chairs_[i]->GetActorLocation().X - m_chairs_[i]->m_pscore_obj_[0]->GetActorLocation().X);
			}
			if (m_chairs_[i]->m_pscore_obj_[1] != NULL)
			{
				Scoreobj2_Distance = FMath::Abs(m_chairs_[i]->GetActorLocation().X - m_chairs_[i]->m_pscore_obj_[1]->GetActorLocation().X);
			}

			// Scoreobj1_Distance�̕����������ꍇ��m_pscore_obj_[0]���Ɉ֎q������Ă����m_pscore_obj_[0]�̃X�R�A�����Z
			if (Scoreobj1_Distance < Scoreobj2_Distance)
			{
				if (m_chairs_[i]->m_pscore_obj_[0] != NULL)
				{
					if (Instance)
					{
						// Player1��2�����ʂ����̂��ɓ��_���Z
						if (m_chairs_[i]->m_name_ == "Player1")
						{
							Instance->m_teamPoint1P += m_chairs_[i]->m_pscore_obj_[0]->m_score_;
						}
						else
						{
							Instance->m_teamPoint2P += m_chairs_[i]->m_pscore_obj_[0]->m_score_;
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
							Instance->m_teamPoint1P += m_chairs_[i]->m_pscore_obj_[1]->m_score_;
						}
						else
						{
							Instance->m_teamPoint2P += m_chairs_[i]->m_pscore_obj_[1]->m_score_;
						}
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("chair[%f] is NULL"), i);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Instance->m_teamPoint1P %d"), Instance->m_teamPoint1P);
	UE_LOG(LogTemp, Warning, TEXT("Instance->m_teamPoint2P %d"), Instance->m_teamPoint2P);
	GetPoint1P();
	GetPoint2P();
		//���_�v�Z��ATick()�𖳌��ɂ���
	PrimaryActorTick.SetTickFunctionEnable(false);
}

void AGameManager::NextRound()
{
	// �z��̗v�f���O�̎Q�Ƃ����Ȃ����ǂ���
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


			// �֎q�̔z��̌��������֎q��SpawnDefaultController()�֐����Ă�
			// �{���͑��삷��֎q�̕ύX��A�O�܂ő��삵�Ă����֎q����SpawnDefaultController()�֐�
			// ���g�p����Ηǂ��\�肾���A�����͒ʂ������̂̏�肭�@�\���Ȃ�����for���Ŗ������s���Ă��܂��B
			for (int i = 0; i < m_chairs_.Num(); ++i)
			{
				m_chairs_[i]->SpawnDefaultController();
				if (m_chairs_[i]->m_ishit_)
				{
					// NULL�`�F�b�N�͊֐����ōs���܂�
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