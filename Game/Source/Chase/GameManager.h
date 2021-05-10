// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.h"
#include "Playerchara.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager.generated.h"

struct FChair
{
	AChair* chair_obj_;
	FVector location_;

	//2�_�Ԃ̋������i�[����ϐ�
	float Vectormeter_;
};

UCLASS()
class CHASE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	int nowroundnum_;
	float time_cnt_;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		int maxroundnum_;

	UPROPERTY(EditAnywhere)
		int player_num_;

	UPROPERTY(EditAnywhere)
		AChair* control_chair_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		float chair_create_time;

	UPROPERTY(EditAnywhere)
		TArray<APlayerchara*> players_;

	UPROPERTY(EditAnywhere)
		TArray<AChair*> chairs_;

	bool TimeCheck(float _deltatime);

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

private:

	//�`�[���|�C���g�i1P�p�j
	int m_teamPoint1P;

	//�`�[���|�C���g�i2P�p�j
	int m_teamPoint2P;

	//�������g�̍��W
	FVector m_thisLocation;

	//�J�E���g�p�ϐ�
	bool m_bFunctionCheck;

//-------------------------------------------------------

	// 2021 04/30 ���� �\���̂̐錾�ǉ�
	TArray<FChair*> chairs;

	AChair* m_pAChair[10] = {NULL};

	float m_ChairDistance[10] = {0.f};

	bool m_Check[10] = { false };

};
