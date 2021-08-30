//--------------------------------------------------------------
//�N���X���FChair.cpp
//�T�v	  �F�֎q���~�܂��Ă������ɃX�R�A�����Z������p�N���X
//�쐬���@�F2021/07/16
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/07/16 ���葓�� �쐬
//--------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "AddScoreTrigger.generated.h"

UCLASS()
class CHASE_API AAddScoreTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAddScoreTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)			// �ǉ����链�_��ݒ肷��ϐ�
		int m_score_;

};
