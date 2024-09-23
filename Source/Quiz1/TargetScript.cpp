// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetScript.h"

#include "Bullet.h"
#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

class ABullet;
// Sets default values
ATargetScript::ATargetScript()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = collider;

	if(collider)
	{
		collider->SetSimulatePhysics(false);
		collider->SetEnableGravity(false);
		collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		collider->SetCollisionProfileName(TEXT("wall"));
		mesh->SetCollisionProfileName(TEXT("wall"));
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>
	obj(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'"));

	if (obj.Succeeded())
		mesh->SetStaticMesh(obj.Object);

	mesh->SetupAttachment(RootComponent); 
	collider->OnComponentBeginOverlap.AddDynamic(this, &ATargetScript::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void ATargetScript::BeginPlay()
{
	Super::BeginPlay();
	pawn = Cast<AMyPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void ATargetScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATargetScript::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABullet* Bullet = Cast<ABullet>(OtherActor);
	if(Bullet)
	{
		pawn->killCnt++;
		pawn -> PrintKillCount();
		Bullet->Destroy();
	}
}
