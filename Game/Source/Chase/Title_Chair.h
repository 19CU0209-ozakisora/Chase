//------------------------------------------------------------------
//�N���X���FTitle_Chair.h
//�T�v	  �F�^�C�g���̈֎q�̓�������
//�쐬���@�F2021/05/11
//�쐬�ҁ@�F19CU0228 ��c���_
//�T�v	�@�F2021/05/11 �N���X�쐬
//------------------------------------------------------------------

//�C���N���[�h�J�[�h
#pragma once

//�C���N���[�h
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Title_Chair.generated.h"

//�O���錾
class UBoxComponent;
class USkeltalMeshComponent;
class USceneComponent;

UCLASS()
class CHASE_API ATitle_Chair : public AActor
{
	GENERATED_BODY()
	
public:	
	//�R���X�g���N�^
	ATitle_Chair();

protected:
	//�Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:	
	//���t���[���X�V����
	virtual void Tick(float DeltaTime) override;

private:

	//�֎q�ړ�
	void MoveChair(float deltaTime_);

	//�֎q����������
	void DestroyChair();

	//���Ԏ擾
	float m_movetime_;

	//�\�����ԁi���݁j
	float m_visibletime_;

	//���̎��Ԃ𒴂�����\�������鎞�ԁi�֎q���Ƃɐݒ�ł���j
	UPROPERTY(EditAnywhere)
	    float m_visibletimemax_;

	//���̎��Ԃ𒴂�����~�߂�
	UPROPERTY(EditAnywhere)
		float m_stopchairtime_;

	UPROPERTY(EditAnywhere)
		float m_location_x_;

	//�֎q�J�E���g
	float m_chaircnt_;

	UPROPERTY(EditAnywhere)
	float m_chaircntmax_;

public:

	UPROPERTY()
		USceneComponent* m_pbase_;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		UBoxComponent* m_pboxcomponent_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* m_pstaticmeshcomp_;

};
