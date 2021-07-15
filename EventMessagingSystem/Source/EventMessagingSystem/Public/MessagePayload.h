// Copyright (c) 2021, Kazimieras Mikelis, MIT license.

#pragma once

#include "CoreMinimal.h"
#include "MessagePayload.generated.h"

/**
 * Struct for storing multiple data types of payload in an event message.
 */
struct FMessagePayloadProperty
{
	FMessagePayloadProperty() {}
	FMessagePayloadProperty(const int32 & IntPayload) : IntPayload(IntPayload) {}
	FMessagePayloadProperty(UObject * ObjectPayload) : ObjectPayload(ObjectPayload) {}
	FMessagePayloadProperty(const FName & NamePayload) : NamePayload(NamePayload) {}
	FMessagePayloadProperty(const uint8 BytePayload) : BytePayload(BytePayload) {}
	FMessagePayloadProperty(const FString & StringPayload) : StringPayload(StringPayload) {}
	
	int32 IntPayload = 0;								// Integer payload (if present)
	TWeakObjectPtr<UObject> ObjectPayload = nullptr;	// Object payload (if present)
	FName NamePayload = NAME_None;						// Name payload (if present)
	uint8 BytePayload = 0x0;							// Byte payload (if present)
	FString StringPayload = FString();					// String payload (if present)
};

/**
 * Message payload struct, ready to be used in Blueprints and in C++.
 */
USTRUCT(BlueprintType)
struct FMessagePayload
{
	GENERATED_BODY()

	TMap<FName, FMessagePayloadProperty> Properties;

	/**
	 * Set a property value in this payload.
	 */
	template <typename T>
    void SetProperty(const FName & PropertyName, T Value)
	{
		Properties.Add(PropertyName, Value);
	}

	/**
	 * Get an int32 property value from this payload by property name.
	 */
	int32 GetIntProperty(const FName & Name) const 
	{
		if(Properties.Contains(Name))
		{
			return Properties[Name].IntPayload;
		}
		return 0;
	}

	/**
	* Get an FName property value from this payload by property name.
	*/
	FName GetNameProperty(const FName & Name) const
	{
		if(Properties.Contains(Name))
		{
			return Properties[Name].NamePayload;
		}
		return NAME_None;
	}

	/**
	* Get a uint8 (byte) property value from this payload by property name.
	*/
	uint8 GetByteProperty(const FName & Name) const
	{
		if(Properties.Contains(Name))
		{
			return Properties[Name].BytePayload;
		}
		return 0;
	}

	/**
	* Get an FString property value from this payload by property name.
	*/
	FString GetStringProperty(const FName & Name) const
	{
		if(Properties.Contains(Name))
		{
			return Properties[Name].StringPayload;
		}
		return FString();
	}

	/**
	* Get a UObject property value from this payload by property name.
	*/
	UObject * GetObjectProperty(const FName & Name) const
	{
		if(Properties.Contains(Name))
		{
			if(Properties[Name].ObjectPayload.IsValid())
			{
				return Properties[Name].ObjectPayload.Get();	
			}
		}
		return nullptr;
	}
};