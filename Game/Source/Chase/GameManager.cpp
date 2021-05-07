// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

// Sets default values
AGameManager::AGameManager()
	: maxroundnum_(10)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<APlayerchara> findClass;
	findClass = APlayerchara::StaticClass();
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, temp);


	for (int i = 0; i < temp.Num(); ++i)
	{
		players_.Add(Cast<APlayerchara>(temp[i]));
	}

	players_[0]->CreateChair();
	chairs_.Add(players_[0]->control_chair_);
	++nowroundnum_;
	
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nowroundnum_ % 2 == 1)
	{
		if (players_[0]->control_chair_ != NULL)
		{
			if (players_[0]->control_chair_->phase_ == EPhase::kEnd)
			{
				if (TimeCheck(DeltaTime))
				{
					players_[1]->CreateChair();
					chairs_.Add(players_[1]->control_chair_);
					++nowroundnum_;
				}
			}
		}
	}
	else if (nowroundnum_ % 2 == 0)
	{
		if (players_[1]->control_chair_->phase_ == EPhase::kEnd)
		{
			if (TimeCheck(DeltaTime))
			{
				players_[0]->CreateChair();
				chairs_.Add(players_[0]->control_chair_);
				++nowroundnum_;
			}
		}
	}

}

bool AGameManager::TimeCheck(float _deltatime)
{
	time_cnt_ += _deltatime;

	if (time_cnt_ <= chair_create_time)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < chairs_.Num(); i++)
		{
			chairs_[i]->m_floating_pawn_movement_->Velocity = FVector::ZeroVector;
		}
		time_cnt_ = 0.f;
		return true;
	}
}
