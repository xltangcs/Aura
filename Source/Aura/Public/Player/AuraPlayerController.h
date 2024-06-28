// Copyright Loongxltang

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
class IEnemyInterface;

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()



public:
	AAuraPlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;;
	virtual void PlayerTick(float DeltaTime) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void Dash(const FInputActionValue& InputActionValue);
	
private:
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void CameraDistance(const FInputActionValue& InputActionValue);
	void CursorTrace();
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> DashAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> CameraDistanceAction;
	
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
};
