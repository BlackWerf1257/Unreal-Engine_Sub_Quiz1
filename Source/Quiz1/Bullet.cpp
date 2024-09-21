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
	
	ConstructorHelpers::FObjectFinder<UStaticMesh>
	obj(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));

	if (obj.Succeeded())
	{
		mesh->SetStaticMesh(obj.Object);
		mesh->SetRelativeLocation(FVector(0, 0, 0));
		mesh->SetRelativeScale3D(FVector(0.6,0.6,0.6));
		mesh->SetRelativeRotation((FRotator(90,0,0)).Quaternion());
	}

	collider->SetCollisionProfileName(TEXT("bullet"));
	collider->SetSimulatePhysics(true);
	collider->SetEnableGravity(true);
	collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    collider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
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
	FVector pos = GetActorLocation() + GetActorLocation() * DeltaTime * 5;
	this->SetActorLocation(pos);

}

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Activate"));
}

