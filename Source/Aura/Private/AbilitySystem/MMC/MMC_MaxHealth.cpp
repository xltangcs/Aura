// Copyright Loongxltang


#include "AbilitySystem/MMC/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const auto SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
	const auto TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = SourceTag;
	EvalParams.TargetTags = TargetTag;

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvalParams, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		//PlayerLevel = VigorDef::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
		PlayerLevel = CombatInterface->GetPlayerLevel();
	}
	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
