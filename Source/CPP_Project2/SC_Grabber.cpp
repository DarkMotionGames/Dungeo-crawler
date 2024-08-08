// Fill out your copyright notice in the Description page of Project Settings.



#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "SC_Grabber.h"




// Sets default values for this component's properties
USC_Grabber::USC_Grabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}






// Called when the game starts
void USC_Grabber::BeginPlay()
{
	Super::BeginPlay();
}




// Called every frame
void USC_Grabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();




	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		FRotator TargetRotation = GetComponentRotation();
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, TargetRotation);
	}
}




void USC_Grabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();



	if (PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	bool HasHit = IsGrabbable(HitResult);
	


	if (HasHit)
	{

		//DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 5);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);

		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitResult.GetActor()->Tags.Add("Grabbed");
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}




void USC_Grabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent())
	{	
		AActor* ToRelease = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		ToRelease->Tags.Remove("Grabbed");
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}

}



UPhysicsHandleComponent* USC_Grabber::GetPhysicsHandle() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}




bool USC_Grabber::IsGrabbable(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDist;

	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);


}
