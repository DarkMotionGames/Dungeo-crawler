// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}




void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}




void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetActoToWork();

	if (Actor)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());

		if (Component)
		{
			Component->SetSimulatePhysics(false);
		}

		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

		AC_Mover->SetShouldMove(true);
	}
	else
	{
		AC_Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UAC_Mover* NewMover)
{
	AC_Mover = NewMover;
}





AActor* UTriggerComponent::GetActoToWork() const
{

	TArray<AActor*> ActorPtr;
	GetOverlappingActors(ActorPtr);

	for (AActor* Actor : ActorPtr)
	{
		bool HasAcceptableTag = Actor->ActorHasTag(TagName);
		bool IsGrabbedTag = Actor->ActorHasTag("Grabbed");
		if (HasAcceptableTag && !IsGrabbedTag)
		{
			return Actor;
		}	
	}
	return nullptr;
}

