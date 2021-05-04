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
#include "Kismet/GameplayStatics.h"
#include "HouseCenter.generated.h"

/**
 * 
 */
 // 2021 04/30 ���� �\���̂̒�`�ǉ�
struct FChair
{
	AChair* chair_obj_;
	FVector location_;
};

UCLASS()
class CHASE_API AHouseCenter : public AChair
{
	GENERATED_BODY()

public:
	//�R���X�g���N�^
	AHouseCenter();

public:
	//�֎q�����ׂĎ~�܂������̏��� (2021/04/30 ���� UFUNCTION��ǉ�)
	UFUNCTION(meta = (CallInEditor = "true"))
		void StopChair();

	//�֎q�̋����\�[�g�p
	void ChairSort(float _Vector[]);

	void SetPoint(float _Vector[]);

	UFUNCTION(BlueprintCallable,Category = "My Functions")
	int GetPoint()const { return m_getPoint; }


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

	//�֎q�̍��W����
	int Count;

	//�������g�̍��W
	FVector m_thisLocation;

	//�֎q(Chair�N���X)�̍��W�擾�p
	FVector m_ChairLocation;

	//�n�E�X�̒��S���W�ƈ֎q�̍��W�̍����i�[������W
	//�v�Z������@�͒��S����֎q��X,Y���̖ʐς������ċ������v�Z����
	float m_differenceLocation;

	// 2021 04/30 ���� �\���̂̐錾�ǉ�
	TArray<FChair> chairs;

	float _Vector[10];

	int Rank;
};
