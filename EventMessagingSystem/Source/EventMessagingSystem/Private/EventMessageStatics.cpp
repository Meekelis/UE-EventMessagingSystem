// Copyright (c) 2021, Kazimieras Mikelis, MIT license.

#include "EventMessageStatics.h"

#include "EventMessageReceiver.h"

#define DEFINE_MESSAGE_PAYLOAD_GETTER_SETTER(FuncName, TypeName) \
	TypeName UEventMessageStatics::Get##FuncName##Payload_BP(const FMessagePayload& Payload, const FName PropertyName) \
	{ \
		return Payload.Get##FuncName##Property(PropertyName); \
	} \
	FMessagePayload UEventMessageStatics::Add##FuncName##Payload_BP(FMessagePayload Payload, const FName PropertyName, TypeName Value) \
	{ \
		Payload.SetProperty(PropertyName, Value); \
		return Payload; \
	}

DEFINE_MESSAGE_PAYLOAD_GETTER_SETTER(Int, int32)
DEFINE_MESSAGE_PAYLOAD_GETTER_SETTER(Name, FName)
DEFINE_MESSAGE_PAYLOAD_GETTER_SETTER(Byte, uint8)
DEFINE_MESSAGE_PAYLOAD_GETTER_SETTER(String, FString)
DEFINE_MESSAGE_PAYLOAD_GETTER_SETTER(Object, UObject*)

FMessagePayload UEventMessageStatics::MakeLiteralEventMessagePayload()
{
	return FMessagePayload();
}

void UEventMessageStatics::SendEventMessageByTag(UObject* Sender, const FName ReceiverActorTag, const FName EventName,
                                                 const FMessagePayload Payload)
{
	TArray<AActor*> WorldActors;
	GetWorldActorsFast(Sender, WorldActors);

	for(auto Actor : WorldActors)
	{
		if(Actor->Implements<UEventMessageReceiver>())
		{
			if(Actor->ActorHasTag(ReceiverActorTag))
			{
				IEventMessageReceiver::Execute_OnEventMessageReceived(Actor, EventName, Sender, Payload);	
			}
		}
	}
}

void UEventMessageStatics::SendEventMessageByClass(UObject* Sender, UClass* ReceiverClass, const FName EventName,
                                                   const FMessagePayload Payload)
{
	TArray<AActor*> WorldActors;
	GetWorldActorsFast(Sender, WorldActors);

	for(auto Actor : WorldActors)
	{
		if(Actor->Implements<UEventMessageReceiver>())
		{
			const UClass * CandidateClass = Actor->GetClass();
			if(CandidateClass == ReceiverClass || CandidateClass->IsChildOf(ReceiverClass))
			{
				IEventMessageReceiver::Execute_OnEventMessageReceived(Actor, EventName, Sender, Payload);	
			}
		}
	}
}

void UEventMessageStatics::SendMulticastEventMessage(UObject* Sender, const FName EventName, const FMessagePayload Payload)
{
	TArray<AActor*> WorldActors;
	GetWorldActorsFast(Sender, WorldActors);
	
	for(auto Actor : WorldActors)
	{
		if(Actor->Implements<UEventMessageReceiver>())
		{
			IEventMessageReceiver::Execute_OnEventMessageReceived(Actor, EventName, Sender, Payload);
		}
	}
}

void UEventMessageStatics::GetWorldActorsFast(UObject* WorldContext, TArray<AActor*>& OutActors)
{
	OutActors.Empty(512); // This magic number cuts down on memcpy operations. 

	// Attempt to get world from context.
	UWorld * World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::LogAndReturnNull);
	if(!IsValid(World))
	{
		return;
	}

	// Get all levels of the world, and compile a list of referenced actors.
	TArray<ULevel*> Levels = World->GetLevels();
	for(auto Level : Levels)
	{
		if(IsValid(Level) && Level->bIsVisible)
		{
			OutActors.Append(Level->Actors);
		}
	}

	for(int32 i = OutActors.Num() - 1; i >= 0; --i)
	{
		if(!IsValid(OutActors[i]))
		{
			OutActors.RemoveAt(i, 1, false);
		}
	}

	OutActors.Shrink();
}
