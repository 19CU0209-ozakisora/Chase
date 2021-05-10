// Fill out your copyright notice in the Description page of Project Settings.


//�C���N���[�h
#include "GameManager.h"
#include "Chair.h"

//�R���X�g���N�^
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

//�Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	//�n�E�X�̒��S���W���i�[
	m_thisLocation = GetActorLocation();

	TSubclassOf<APlayerchara> findClass;
	findClass = APlayerchara::StaticClass();
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, temp);

	for (int i = 0; i < temp.Num(); ++i)
	{
		players_.Add(Cast<APlayerchara>(temp[i]));
	}

	//�T�������N���X������
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

//���t���[���X�V����
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

	//���E���h��10�ɂȂ�����
	/*if (nowroundnum_ > 10)
	{
		//�֎q��10�~�܂������̏���
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

//�֎q���~�܂������̏���
void AGameManager::StopChair()
{
	//���������֎q�̃I�u�W�F�N�g�A���W���擾
	for (int i = 0; i < 10; ++i)
	{
		m_ChairDistance[i] = sqrt(((m_thisLocation.X - m_pAChair[i]->GetActorLocation().X) * (m_thisLocation.X - m_pAChair[i]->GetActorLocation().X))
			+ ((m_thisLocation.Y - m_pAChair[i]->GetActorLocation().Y) * (m_thisLocation.Y - m_pAChair[i]->GetActorLocation().Y)));
	}

	//���O�m�F�p
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
				tmp = m_pAChair[dataCount02 + 1];
				m_pAChair[dataCount02 + 1] = m_pAChair[dataCount02];
				m_pAChair[dataCount02] = tmp;
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

//���_�v�Z
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
		//  ���̃^�O�Ƀ|�C���g������
		m_teamPoint1P = i + 1 + m_teamPoint1P;
	}
	else if (m_pAChair[0]->m_PlayerNumberName == "P2Chair")
	{
		m_teamPoint2P = i + 1 + m_teamPoint2P;
	}
	UE_LOG(LogTemp, Warning, TEXT("P1Point %d"), m_teamPoint1P);
	UE_LOG(LogTemp, Warning, TEXT("P2Point %d"), m_teamPoint2P);

	//���_�v�Z��ATick()�𖳌��ɂ���
	PrimaryActorTick.SetTickFunctionEnable(false);
}
