// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Components/BoxComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = collider;

	if(collider)
	{
		collider->SetSimulatePhysics(false);
		collider->SetEnableGravity(true);
		collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		mesh->SetCollisionProfileName(TEXT("bullet"));
	}

	
	ConstructorHelpers::FObjectFinder<UStaticMesh>
	obj(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));

	if (obj.Succeeded())
	{
		mesh->SetStaticMesh(obj.Object);
		mesh->SetRelativeLocation(FVector(0, 0, 0));
		mesh->SetRelativeScale3D(FVector(0.6,0.6,0.6));
		mesh->SetRelativeRotation((FRotator(90,0,0)).Quaternion());
	}


}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector vec = GetActorLocation() + GetActorForwardVector() * 500 * DeltaTime;
	SetActorLocation(vec);
}




