// Copyright Loongxltang

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()


public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/* Begin Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/* End Combat Interface */
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;

	virtual void InitAbilityActorInfo() override;
};
