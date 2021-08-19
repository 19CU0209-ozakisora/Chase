//--------------------------------------------------------------
//�N���X���FInstance.h
//�T�v    :GameInstance�i�^�[���̐���j
//�쐬���@�F2021/08/10
//�쐬�ҁ@�F19CU0301 �ؑ�m
//�X�V�����F2021/08/10 �ؑ�m �쐬
//--------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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
};
