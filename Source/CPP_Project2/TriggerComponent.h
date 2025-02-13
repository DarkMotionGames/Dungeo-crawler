// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "AC_Mover.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP_PROJECT2_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerComponent();




protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UAC_Mover* AC_Mover);

private:

	UPROPERTY(EditAnywhere)
	FName TagName;

	AActor* GetActoToWork() const;
	
	UAC_Mover* AC_Mover;
};
