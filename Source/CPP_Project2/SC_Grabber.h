// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "SC_Grabber.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP_PROJECT2_API USC_Grabber : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USC_Grabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDist = 400;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 40;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	UPhysicsHandleComponent* GetPhysicsHandle() const;

	bool IsGrabbable(FHitResult& OutHitResult) const;


};
