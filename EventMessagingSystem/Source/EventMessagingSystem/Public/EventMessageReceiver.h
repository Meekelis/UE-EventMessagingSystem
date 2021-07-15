// Copyright (c) 2021, Kazimieras Mikelis, MIT license.

#pragma once

#include "CoreMinimal.h"
#include "MessagePayload.h"
#include "UObject/Interface.h"
#include "EventMessageReceiver.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEventMessageReceiver : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface to receive event messages. 
 */
class EVENTMESSAGINGSYSTEM_API IEventMessageReceiver
{
	GENERATED_BODY()

public:

	/**
	 * Event that gets called when this actor receives an event message.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnEventMessageReceived(FName EventName, UObject * Sender, FMessagePayload Payload);
};
