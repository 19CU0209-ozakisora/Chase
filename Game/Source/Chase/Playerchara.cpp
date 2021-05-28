//--------------------------------------------------------------
//�N���X���FPlayerchara.cpp
//�T�v	  �F�֎q�̐���p�N���X
//�쐬���@�F2021/04/22
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/05/04 ���葓�� �쐬�EPlayer�̔ԍ���ێ�
//--------------------------------------------------------------


#include "Playerchara.h"

// Sets default values
APlayerchara::APlayerchara()
	: player_number_(1)
	, chair_spawner_(NULL)
	, chair_stack_(NULL)
	, control_chair_(NULL)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	chair_spawner_ = CreateDefaultSubobject<USceneComponent>(TEXT("chair_spawner_"));
	chair_stack_ = CreateDefaultSubobject<USceneComponent>(TEXT("chair_stack_"));
}

// Called when the game starts or when spawned
void APlayerchara::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerchara::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerchara::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerchara::SetChairTag()
{
	if (player_number_ == 1)
	{
		control_chair_->m_name_ = "Player1";
	}
	else if (player_number_ == 2)
	{
		control_chair_->m_name_ = "Player2";
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerNumber is not default value"));
	}
}