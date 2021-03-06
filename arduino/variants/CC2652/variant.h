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

#ifndef __VARIANT_H__
#define __VARIANT_H__

#include <interface.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* C ware ********************************************************/

#define LED 7 
#define LED_GREEN 7
#define LED_RED 6

#define ADC_7 0x09 /* ADC_COMPB_IN_AUXIO7 */
#define ADC_6 0x0A /* ADC_COMPB_IN_AUXIO6 */
#define ADC_5 0x0B /* ADC_COMPB_IN_AUXIO5 */
#define ADC_4 0x0C /* ADC_COMPB_IN_AUXIO4 */
#define ADC_3 0x0D /* ADC_COMPB_IN_AUXIO3 */
#define ADC_2 0x0E /* ADC_COMPB_IN_AUXIO2 */
#define ADC_1 0x0F /* ADC_COMPB_IN_AUXIO1 */
#define ADC_0 0x10 /* ADC_COMPB_IN_AUXIO0 */

#ifdef __cplusplus
}

/* CPP ware ********************************************************/

#include <SerialUart.h>
extern Uart Serial;
extern Uart Serial1;

#endif //__cplusplus

#endif /* __VARIANT_H__ */
