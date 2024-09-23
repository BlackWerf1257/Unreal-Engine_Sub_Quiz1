// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "Bullet.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = collider;

	if(collider)
	{
		collider->SetSimulatePhysics(true);
		//collider->SetEnableGravity(false);
		collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		collider->SetCollisionProfileName(TEXT("Pawn"));
		mesh->SetCollisionProfileName(TEXT("Pawn"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("Collider가 없음"));
	
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("cam"));
	arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("arm"));
	arm->SetupAttachment(RootComponent);
	arm->TargetArmLength = 650.f;
	arm->SetRelativeRotation(FRotator(-45.0f, 0, 0));
	cam->SetRelativeLocation(FVector(-1000.f, 0.0f, 200.f));
	cam->SetupAttachment(arm);
	mesh->SetupAttachment(RootComponent); 
	
	ConstructorHelpers::FObjectFinder<UStaticMesh>
	obj(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Bush.SM_Bush'"));

	if (obj.Succeeded())
		mesh->SetStaticMesh(obj.Object);

	collider->OnComponentBeginOverlap.AddDynamic(this, &AMyPawn::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	// 충돌 설정
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Horizontal", this, &AMyPawn::Horizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &AMyPawn::Vertical);
	PlayerInputComponent->BindAxis("MouseX", this, &AMyPawn::Rotate);
	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyPawn::Fire);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyPawn::Jump);
}

void AMyPawn::Horizontal(float value)
{
	FVector vec = GetActorLocation() + GetActorRightVector() * 10.f * value;
	SetActorLocation(vec);
}

void AMyPawn::Vertical(float value)
{
	FVector vec = GetActorLocation() + GetActorForwardVector() * 10.f * value;
	SetActorLocation(vec);
}

void AMyPawn::Fire()
{
	UE_LOG(LogTemp, Log, TEXT("발사함"));

	ABullet* wp = GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(),
				GetActorLocation() + GetActorForwardVector() * 200 + GetActorUpVector() * 20,
				GetActorRotation());
}

void AMyPawn::Jump()
{
	FVector vec = GetActorLocation() + GetActorUpVector() * 100.f;
	SetActorLocation(vec);
}

void AMyPawn::Rotate(float value)
{
	FRotator rot = GetActorRotation() + FRotator(0,4,0) * value;
	SetActorRotation(rot);
}

void AMyPawn::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABullet* Bullet = Cast<ABullet>(OtherActor);
	if(Bullet)
		Bullet->Destroy();
}
void AMyPawn::PrintKillCount()
{
	UE_LOG(LogTemp, Log, TEXT("킬 카운트 : %d"), killCnt);
}


