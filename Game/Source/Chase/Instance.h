//--------------------------------------------------------------
//�N���X���FInstance.h
//�T�v    :GameInstance�i�^�[���̐���j
//�쐬���@�F2021/08/10
//�쐬�ҁ@�F19CU0301 �ؑ�m
//�X�V�����F2021/08/10 �ؑ�m �쐬
//			2021/08/31 ��c���_ �`�[�����Ƃ̍��v���_���i�[����ϐ��ǉ��i�E�B�W�F�b�g�o�͗p�j
//			2021/09/07 ��c���_ �e�֎q���Ƃ������_���v�Z����ϐ��ǉ��i�E�B�W�F�b�g�o�͗p�j
//			2021/09/09 �n粗��� �����̃E�B�W�F�b�g���쐬���A�ێ�����
//--------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Instance.generated.h"

UCLASS()
class CHASE_API UInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// GameInstance�̎��Ԃ��������Ă���֐�
	static UInstance* GetInstance();

	// �^�[����
	UPROPERTY(BlueprintReadWrite)
		int m_Turn = 6;

	//�e�`�[���̓��_���i�[�i1P�j
	UPROPERTY(BlueprintReadWrite)
		int m_teamPoint1P = 0;

	//�e�`�[���̓��_���i�[�i2P�j
	UPROPERTY(BlueprintReadWrite)
		int m_teamPoint2P = 0;

	// �����E�B�W�F�b�g
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* commentWidget;

	//�e���_�i�[�p
	//�E�B�W�F�b�g���s�ϔz���Ή��ATArray�^���Ǝ擾�������_�̌^������Ȃ����߁A
	//�������ł͂��邪���ꂼ��̓��_�z���ǉ��B������Β����B
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint1P_1 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint1P_2 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint1P_3 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint1P_4 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint1P_5 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint2P_1 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint2P_2 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint2P_3 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint2P_4 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint2P_5 = 0;

};
