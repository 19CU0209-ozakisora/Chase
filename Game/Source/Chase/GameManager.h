// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.h"
#include "Playerchara.h"
#include "HouseCenter.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
	int nowroundnum_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		int m_maxroundnum_;					// �֎q�𓊂���ő�̐�

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		float m_chair_create_time_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		float m_switch_level_time;			// ���x���J�ڂ̎���

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
		int GetPoint1P()const { return m_teamPoint1P; }

	//�E�B�W�F�b�g�o��2P
	UFUNCTION(BlueprintCallable, Category = "My Functions")
		int GetPoint2P()const { return m_teamPoint2P; }

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

};
