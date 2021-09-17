//--------------------------------------------------------------
//�N���X���FGameManager.h
//�T�v	  �F�Q�[�����Ǘ�����N���X
//�쐬���@�F2021/04/26
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/04/22 ���葓�� �쐬
//			2021/04/30 Chair��Player��h�ǉ�
//			2021/05/04 ���݂̃^�[���E�ǂ���̔Ԃ��E�֎q�̐������Ǘ�����ϐ��̒ǉ�
//			2021/05/09 ���葓�� TimeCheck�֐�(��莞�Ԍ�Ɏ��̃��E���h�ֈڍs����֐�)�̒ǉ�
//			2021/05/09 ��c���_ ���_����̕ϐ��̒ǉ�
//			2021/05/16 ���葓�� HouseCenter.h�̒ǉ�
//			2021/05/25 ���葓�� m_switch_level_time(���x���؂�ւ��̎���)�̕ϐ��ǉ�
//			2021/07/16 ���葓�� m_teamPoint(1P2P�ǂ����)���v���C���Ɋm�F�ł���悤��EditAnyWhere��ǉ�
//								AddScore(�v���C���[���~�܂��Ă���}�X�ɋ߂����̓_�������Z����)�֐���ǉ�
//			2021/08/09 ���葓�� m_is_event_(�C�x���g���������ǂ���)
//								m_event_cnt_(�C�x���g������������)
//								m_event_round_(�C�x���g���������郉�E���h��)
//								NextRound�֐�(���̃��E���h�Ɉړ�������֐�)��ǉ�
//								��GameManager.cpp���ɍ��������������������ׂ܂Ƃ߂܂���
//			2021/08/30 ��c���_  GetPoint�֐��̖߂�l��Insrance�ɕύX
//			2021/09/04 ���葓�� �f�o�b�O�p��+�Ń��E���h���𑝂₷�悤��
//			2021/09/07 ��c���_ �e�֎q���Ƃ������_���v�Z����ϐ��ǉ��i�E�B�W�F�b�g�o�͗p�j
//			2021/09/13 ��c���_ �e���_�łɈ֎q��������Ă邩���i�[���鏈���ɕύX
//			2021/09/17 ��c���_ 09/07�A09/13�̌��ɂ��ẴR�����g�L���A09/07����s�v�ɂȂ����ϐ��̍폜
//--------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.h"
#include "Playerchara.h"
#include "HouseCenter.h"
#include "Instance.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager.generated.h"

// 2021/05/10 ���� �R�����g��(����ō��������)
/*struct FChair
{
	AChair* chair_obj_;

	//2�_�Ԃ̋������i�[����ϐ�
	float Vectormeter_;
};
*/

UCLASS(BluePrintable)
class CHASE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


//---------------------------------------------------------
// ���� ����
private:

	bool TimeCheck(float _deltatime);

	float time_cnt_;

	void AddScore();

public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		TArray<APlayerchara*> m_players_;		// Player�Ǘ��p

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		TArray<AChair*> m_chairs_;				// Chair�Ǘ��p(���_�v�Z����������̂ō\���̂̕����ǂ�����)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_is_event_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		float m_chair_create_time_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		float m_switch_level_time;			// ���x���J�ڂ̎���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		int m_event_cnt_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		int m_nowroundnum_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		int m_maxroundnum_;					// �֎q�𓊂���ő�̐�

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		TArray<int> m_event_round_;

	UFUNCTION(BluePrintCallable)
		void NextRound();

//---------------------------------------------------------
//2021/05/06:�@��c�@�ϐ��A�֐��ǉ�
public:
	//�֎q�����ׂĎ~�܂������̏���
	void StopChair();

	//�֎q�̋����\�[�g�p
	void ChairSort();

	//���_�v�Z
	void SetPoint();

	//�E�B�W�F�b�g�o��1P
	UFUNCTION(BlueprintCallable, Category = "My Functions")
		int GetPoint1P()const { return Instance->m_teamPoint1P; }

	//�E�B�W�F�b�g�o��2P
	UFUNCTION(BlueprintCallable, Category = "My Functions")
		int GetPoint2P()const { return Instance->m_teamPoint2P; }

	//�`�[���|�C���g�i1P�p�j
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		int m_teamPoint1P;

	//�`�[���|�C���g�i2P�p�j]
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		int m_teamPoint2P;

private:

	//�������g�̍��W
	FVector m_thisLocation;

	//�J�E���g�p�ϐ�
	bool m_bFunctionCheck;

//-------------------------------------------------------

	// 2021 05/10 ����  m_chairs_�ɕύX
	// AChair* m_pAChair[10] = {NULL};

	float m_ChairDistance[10] = {0.f};

	bool m_Check[10] = { false };

//��������������������������������������������������������
// �ؒǉ�
	// GameInstance
	UInstance* Instance;

public:
	// Player1�̃^�[����
	UPROPERTY(BlueprintReadOnly)
		int m_Player1Turn;
	// Player2�̃^�[����
	UPROPERTY(BlueprintReadOnly)
		int m_Player2Turn;
//��������������������������������������������������������
};