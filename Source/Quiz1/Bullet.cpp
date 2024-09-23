// Fill out your copyright notice in the Description page of Project Settings.
#include "Bullet.h"
#include "Components/SphereComponent.h"

// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = collider;

	if(collider)
	{
		collider->SetSimulatePhysics(false);
		collider->SetEnableGravity(false);  // 중력 비활성화
		collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//collider->SetCollisionProfileName(TEXT("bullet"));  // Custom collision profile
		collider->SetCollisionProfileName(TEXT("Projectile"));
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>
	obj(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));

	if (obj.Succeeded())
	{
		mesh->SetStaticMesh(obj.Object);
		mesh->SetRelativeScale3D(FVector(0.4,0.4,0.4));
		mesh->SetupAttachment(RootComponent); 
	}

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	collider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBoxBeginOverlap);

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector vec = GetActorLocation() + GetActorForwardVector() * 500 * DeltaTime;
	SetActorLocation(vec);
}

void ABullet::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 자기 자신과의 충돌을 무시
	if (!OtherActor || OtherActor == this)
		return;
	
}
