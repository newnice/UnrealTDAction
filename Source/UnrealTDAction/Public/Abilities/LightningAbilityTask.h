// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "LightningAbilityTask.generated.h"

class AEnemyManager;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLightningAbilityTaskDelegate);

UCLASS()
class UNREALTDACTION_API ULightningAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

	float DelayBetweenAttacks;
	float AttackRadius;
	FVector ActorPosition;
	FVector ForwardVector;

	UPROPERTY()
	TArray<AActor*> EnemiesToDamage;
	TWeakObjectPtr<AEnemyManager> EnemyManager;
	FVector PreviousAttackedEnemyLocation;
	FTimerHandle TimerHandle;

protected:
	virtual void Activate() override;
public:
	static ULightningAbilityTask* CreateLightningTask(UGameplayAbility* OwningAbility,
	                                                  FName TaskInstanceName,
	                                                  float AbilityRadius,
	                                                  float DelayBetweenAttacks,
	                                                  const FVector& StartPoint,
	                                                  const FVector& ForwardVector);

	FLightningAbilityTaskDelegate OnCompleted;

private:
	void ApplyAttack();
	AEnemyManager* FindEnemyManagerActor() const;
	TArray<AActor*> SortEnemies(TArray<AActor*>& Array) const;
	TArray<AActor*> FindDamagedEnemies() const;
	
	UFUNCTION()
	void OnTimeFinish();
	
	void KillSingleEnemy();

	virtual void OnDestroy(bool bInOwnerFinished) override;
};
