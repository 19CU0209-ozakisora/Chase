//--------------------------------------------------------------
//�N���X���FChair.cpp
//�T�v	  �F�֎q���~�܂��Ă������ɃX�R�A�����Z������p�N���X
//�쐬���@�F2021/07/16
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/07/16 ���葓�� �쐬
//--------------------------------------------------------------


#include "AddScoreTrigger.h"

// Sets default values
AAddScoreTrigger::AAddScoreTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// false�ɕύX
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAddScoreTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAddScoreTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

