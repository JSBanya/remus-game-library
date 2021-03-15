#pragma once

#include <cstdlib>
#include <time.h>
#include <remus/logging/logger.h>
#include <remus/engine/window.h>
#include <remus/engine/runtime.h>
#include <remus/engine/driver/driver.h>
#include <remus/engine/cache.h>
#include "testDriver.h"
#include "settings.h"

void loadResources(remus::engine::Cache* cache);