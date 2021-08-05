////////////////////////////////////////////////////////////////////////////////////////
//
//      2021 Georgi Angelov
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////////////

#include "interface.h"
#include <driverlib/osc.h>
#include <driverlib/prcm.h>
#include <driverlib/sys_ctrl.h>
#include <driverlib/aon_rtc.h>

void setup();
void loop();
void initVariant();

extern "C" void __sinit(struct _reent *);
extern "C" void SysTickSetup(void);

int main(void)
{
    // Enable HF XOSC
    OSCHF_TurnOnXosc();
    while (!OSCHF_AttemptToSwitchToXosc())
        ;

    // Use 32768 Hz XOSC
    OSCClockSourceSet(OSC_SRC_CLK_LF, OSC_XOSC_LF);
    while (OSCClockSourceGet(OSC_SRC_CLK_LF) != OSC_XOSC_LF)
        ;

    // Make sure writes take effect
    SysCtrlAonSync();
    PRCMCacheRetentionDisable(); // now disable retention

    // for delay
    SysTickSetup();

    // for STDIO
    __sinit(_GLOBAL_REENT);
    stdio_retarget(NULL);

    // Start and end points of the constructor list, defined by the linker script.
    extern void (*__preinit_array_start)(void);
    extern void (*__preinit_array_end)(void);
    for (void (**p)(void) = &__preinit_array_start; p < &__preinit_array_end; ++p)
    {
        (*p)();
    }

    // Start and end points of the constructor list, defined by the linker script.
    extern void (*__init_array_start)(void);
    extern void (*__init_array_end)(void);
    for (void (**p)(void) = &__init_array_start; p < &__init_array_end; ++p)
    {
        (*p)();
    }

    // Enable RTC if it isn't already running
    if (AONRTCActive() == false)
    {
        AONRTCReset();
        AONRTCEnable();
    }

    // ARDUINO
    initVariant();
    setup();
    for (;;)
        loop();
}
