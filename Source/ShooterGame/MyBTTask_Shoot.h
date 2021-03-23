// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UMyBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMyBTTask_Shoot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

};
