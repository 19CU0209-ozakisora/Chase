//--------------------------------------------------------------
//�N���X���FHousePoint.h
//�T�v	  �F�֎q�̋����ɂ���āA���_������N���X�iChair�N���X�̌p���N���X�j
//�쐬���@�F2021/04/29
//�쐬�ҁ@�F19CU0228 ��c���_
//�X�V�����F2021/04/29 �쐬
//--------------------------------------------------------------

//�C���N���[�h�J�[�h
#pragma once

//�C���N���[�h
#include "CoreMinimal.h"
#include "Chair.h"
#include "HouseCenter.generated.h"

/**
 * 
 */
UCLASS()
class CHASE_API AHouseCenter : public AChair
{
	GENERATED_BODY()

public:
	//�R���X�g���N�^
	AHouseCenter();

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
	UPROPERTY(EditAnyWhere, BluePrintReadWrite)
		UStaticMeshComponent* m_pConfirmMesh;

private:

	//������|�C���g
	int m_getPoint;

	//�������g�̍��W
	FVector m_thisLocation;

	//�֎q(Chair�N���X)�̍��W�擾�p
	FVector m_ChairLocation;

	//�n�E�X�̒��S���W�ƈ֎q�̍��W�̍����i�[������W
	//�v�Z������@�͒��S����֎q��X,Y���̖ʐς������ċ������v�Z����
	float m_differenceLocation;
	
};
