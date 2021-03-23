// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ClearBlackBoardValue.h"
#include "BehaviorTree/BlackboardComponent.h"



UMyBTTask_ClearBlackBoardValue::UMyBTTask_ClearBlackBoardValue() {

	NodeName = "Clear Blackboard Value";


};


EBTNodeResult::Type UMyBTTask_ClearBlackBoardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;

}
