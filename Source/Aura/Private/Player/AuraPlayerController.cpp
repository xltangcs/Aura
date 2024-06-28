// Copyright Loongxltang


#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Interaction/EnemyInterface.h"
#include "Character/AuraCharacter.h"
#include "GameFramework/SpringArmComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior((EMouseLockMode::DoNotLock));
	InputModeData.SetHideCursorDuringCapture(false);

	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Look);
	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &AAuraPlayerController::Dash);
	EnhancedInputComponent->BindAction(CameraDistanceAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::CameraDistance);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if(LastActor == nullptr)
	{
		if(ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
		}
		else
		{
			
		}
	}
	else
	{
		if(ThisActor == nullptr)
		{
			LastActor->UnHighlightActor();
		}
		else
		{
			if(LastActor != ThisActor)
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				
			}
		}
	}
	
}


void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}

}

void AAuraPlayerController::Look(const FInputActionValue& Value)
{
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(Value.Get<float>());
	}
	
}

void AAuraPlayerController::CameraDistance(const FInputActionValue& InputActionValue)
{
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		const ACharacter* AAuraCharacter = Cast<ACharacter>(ControlledPawn);
		USpringArmComponent* AuraSpring = AAuraCharacter->GetComponentByClass<USpringArmComponent>();
		AuraSpring->TargetArmLength = FMath::Clamp(AuraSpring->TargetArmLength + InputActionValue.Get<float>() * 10.0, 200.0f, 800.0f);
	}
}
