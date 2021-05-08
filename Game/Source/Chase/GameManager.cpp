//--------------------------------------------------------------
//�N���X���FGameManager.cpp
//�T�v	  �F�֎q�̐���p�N���X
//�쐬���@�F2021/04/22
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/04/26 ���葓�� �쐬
//			2021/04/23 ���葓�� �q�b�g���̏�����BP����C++�ɈڐA
//			2021/05/04 ���葓�� ���݂̃^�[���E�ǂ���̔Ԃ��E�֎q�̐����Ȃǂ�ǉ�
//			2021/05/07 ���葓�� GameManager�̏C��
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

	// ���x����ɔz�u���Ă���Player�̌����y�ъi�[
	TSubclassOf<APlayerchara> findClass;
	findClass = APlayerchara::StaticClass();
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, temp);

	for (int i = 0; i < temp.Num(); ++i)
	{
		players_.Add(Cast<APlayerchara>(temp[i]));
	}

	// �Q�[���̍ő僉�E���h�� / 2 (for���̒���Player1��Player2�̈֎q�̐����𓯎��ɍs�����߁Amaxroundnum_ / 2�ɂ��Ă��܂�)
	for (int n = 0; n < maxroundnum_ / 2; ++n)
	{
		// �֎q�̐����y�шʒu�̎w��A�Ǘ����邽�߂ɔz��Ɋi�[
		players_[0]->CreateChair();
		players_[0]->control_chair_->SetActorLocation(FVector(players_[0]->chair_stack_->GetComponentLocation().X, players_[0]->chair_stack_->GetComponentLocation().Y + n * 250, players_[0]->chair_stack_->GetComponentLocation().Z), false, nullptr, ETeleportType::TeleportPhysics);
		chairs_.Add(players_[0]->control_chair_);

		players_[1]->CreateChair();
		players_[1]->control_chair_->SetActorLocation(FVector(players_[1]->chair_stack_->GetComponentLocation().X, players_[1]->chair_stack_->GetComponentLocation().Y + n * 250, players_[1]->chair_stack_->GetComponentLocation().Z), false, nullptr, ETeleportType::TeleportPhysics);
		chairs_.Add(players_[1]->control_chair_);
	}

	// Player[0]���Ǘ����Ă���֎q�̎��_�ɕύX
	players_[0]->GetOperate();
	++nowroundnum_;
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ��^�[���̎�(Player1�̔�)
	if (nowroundnum_ % 2 == 1)
	{
		// NULL�`�F�b�N
		if (players_[0]->control_chair_ != NULL)
		{
			// ���ݑ��삵�Ă���֎q���֎q�ɓ����� or ��胉�C���܂ōs���Ă��܂�����
			if (players_[0]->control_chair_->phase_ == EPhase::kEnd)
			{
				// ���b���o�ߌ�A���삷��֎q�̕ύX
				if (TimeCheck(DeltaTime))
				{
					players_[1]->control_chair_ = chairs_[nowroundnum_];
					players_[1]->GetOperate();
					
					// �֎q�̔z��̌��������֎q��SpawnDefaultController()�֐����Ă�
					// �{���͑��삷��֎q�̕ύX��A�O�܂ő��삵�Ă����֎q����SpawnDefaultController()�֐�
					// ���g�p����Ηǂ��\�肾���A�����͒ʂ������̂̏�肭�@�\���Ȃ�����for���Ŗ������s���Ă��܂��B���Ȃ��낵���Ȃ�
					for (int i = 0; i < chairs_.Num(); ++i)
					{
						chairs_[i]->SpawnDefaultController();
						// chairs_[i]->b();
					}

					// players_[1]->CreateChair();						// 2021/05/08 BeginPlay�Ő�������悤�ɕύX
					// chairs_.Add(players_[1]->control_chair_);		

					++nowroundnum_;
				}
			}
		}
	}
	// ��^�[���̎�(Player2�̔�)
	else if (nowroundnum_ % 2 == 0)
	{
		// NULL�`�F�b�N
		if (players_[1]->control_chair_ != NULL)
		{
			// ���ݑ��삵�Ă���֎q���֎q�ɓ����� or ��胉�C���܂ōs���Ă��܂�����
			if (players_[1]->control_chair_->phase_ == EPhase::kEnd)
			{
				// ���b���o�ߌ�A���삷��֎q�̕ύX
				if (TimeCheck(DeltaTime))
				{
					// ��Ɠ���(�����̂Ŋ���)
					players_[0]->control_chair_ = chairs_[nowroundnum_];
					players_[0]->GetOperate();
					for (int i = 0; i < chairs_.Num(); ++i)
					{
						chairs_[i]->SpawnDefaultController();
						//chairs_[i]->b();
					}

					//chairs_[nowroundnum_]->b();

					// players_[0]->CreateChair();						// 2021/05/08 BeginPlay�Ő�������悤�ɕύX
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
