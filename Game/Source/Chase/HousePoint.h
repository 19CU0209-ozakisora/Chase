//--------------------------------------------------------------
//�N���X���FHousePoint.h
//�T�v	  �F�֎q�̋����ɂ���āA���_������N���X
//�쐬���@�F2021/04/23
//�쐬�ҁ@�F19CU0228 ��c���_
//�X�V�����F2021/04/23 �쐬
//--------------------------------------------------------------

//�C���N���[�h�J�[�h
#pragma once

//�C���N���[�h
#include"Engine/Engine.h"			// �X�N���[�����O�o�͗p
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HousePoint.generated.h"

//�O���錾
class UStaticMeshComponent;

UCLASS()
class CHASE_API AHousePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	//�R���X�g���N�^
	AHousePoint();

public:
	//�֎q�����ׂĎ~�܂������̏���
	void StopChair();

protected:
	//�Q�[���X�^�[�g���A�܂��͋N�����ɔ������鏈��
	virtual void BeginPlay() override;

public:	
	//���t���[���X�V����
	virtual void Tick(float DeltaTime) override;

protected:
	//�m�F�p���b�V���R���|�[�l���g
	UPROPERTY(EditAnyWhere,BluePrintReadWrite)
		UStaticMeshComponent* m_pConfirmMesh;

private:

	//������|�C���g
	int m_getPoint;

	//�������g�̍��W
	FVector m_thisLocation;

	//�֎q(Chair�N���X)�̍��W�擾�p
	FVector m_ChairLocation;

	//�������g�̍��W�ƈ֎q�̍��W�̍����擾����ϐ�(���˂���O)
	FVector m_prevdifferenceLocation;

	//������̍��W
	FVector m_differenceLocation;

};
