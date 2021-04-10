#pragma once

#include <cstdlib>
#include <time.h>
#include <remus/logging/logger.h>
#include <remus/engine/window.h>
#include <remus/engine/runtime.h>
#include <remus/engine/driver/driver.h>
#include <remus/engine/cache.h>
#include <remus/engine/render/forward.h>
#include "testDriver.h"
#include "settings.h"

using namespace remus;

void loadResources(engine::Cache* cache);