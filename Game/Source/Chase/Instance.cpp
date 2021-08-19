//--------------------------------------------------------------
//�N���X���FInstance.cpp
//�T�v    :GameInstance�i�^�[���̐���j
//�쐬���@�F2021/08/10
//�쐬�ҁ@�F19CU0301 �ؑ�m
//�X�V�����F2021/08/10 �ؑ�m �쐬
//--------------------------------------------------------------


#include "Instance.h"
#include "Engine/Engine.h"

UInstance* UInstance::GetInstance()
{
    UInstance* instance = nullptr;

    if (GEngine)
    {
        FWorldContext* context = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
        instance = Cast<UInstance>(context->OwningGameInstance);
    }

    return instance;
}