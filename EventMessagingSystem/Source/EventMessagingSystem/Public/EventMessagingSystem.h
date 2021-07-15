// Copyright (c) 2021, Kazimieras Mikelis, MIT license.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FEventMessagingSystemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
