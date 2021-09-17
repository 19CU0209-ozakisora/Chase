//--------------------------------------------------------------
//�N���X���FInstance.h
//�T�v    :GameInstance�i�^�[���̐���j
//�쐬���@�F2021/08/10
//�쐬�ҁ@�F19CU0301 �ؑ�m
//�X�V�����F2021/08/10 �ؑ�m �쐬
//			2021/08/31 ��c���_ �`�[�����Ƃ̍��v���_���i�[����ϐ��ǉ��i�E�B�W�F�b�g�o�͗p�j
//			2021/09/07 ��c���_ �e�֎q���Ƃ������_���v�Z����ϐ��ǉ��i�E�B�W�F�b�g�o�͗p�j
//			2021/09/09 �n粗��� �����̃E�B�W�F�b�g���쐬���A�ێ�����
//			2021/09/13 ��c���_ �e���_�łɈ֎q��������Ă邩���i�[���鏈���ɕύX
//			2021/09/13 ��c���_ ���̃R�����g�L��
//--------------------------------------------------------------

//�C���N���[�h�J�[�h
#pragma once

//�C���N���[�h
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

	//�e���_�łɈ֎q��������Ă邩���i�[����ϐ��i���ʉ�ʂŎg�p�j
	UPROPERTY(BlueprintReadWrite)
		int m_chairGet10P_1P = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairGet20P_1P = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairGet30P_1P = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairGet10P_2P = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairGet20P_2P = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairGet30P_2P = 0;

};
