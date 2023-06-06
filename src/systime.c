/***************************************************************************
 *   Copyright (C) 2012 by Christoph Thelen                                *
 *   doc_bacardi@users.sourceforge.net                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "systime.h"

#include "asic_types.h"

/* ASIC */
#define DEV_FREQUENCY 100000000

#if ASIC_TYP==ASIC_TYP_NETX90_APP

#include "netx90/netx90_regdef.h"
static NX90_SYSTIME_AREA_T * ptSystimeArea = (NX90_SYSTIME_AREA_T *) Addr_NX90_systime_app;

#elif ASIC_TYP==ASIC_TYP_NETX90

#include "netx90/netx90_regdef.h"
static NX90_SYSTIME_AREA_T * ptSystimeArea = (NX90_SYSTIME_AREA_T *) Addr_NX90_systime_com;

#elif ASIC_TYP==ASIC_TYP_NETX56

#include "netx56/netx56_regdef.h"
static NX56_SYSTIME_AREA_T* ptSystimeArea = (NX56_SYSTIME_AREA_T*) NX56_NETX_SYS_TIME_AREA;

#elif ASIC_TYP == ASIC_TYP_NETX500

#include "netx500/netx500_regdef.h"
static NX500_SYSTIME_AREA_T* ptSystimeArea = (NX500_SYSTIME_AREA_T*) NX500_NETX_SYS_TIME_AREA;

#elif ASIC_TYP == ASIC_TYP_NETX10

#include "netx10/netx10_regdef.h"
static NX10_SYSTIME_AREA_T* ptSystimeArea = (NX10_SYSTIME_AREA_T*) NX10_NETX_SYS_TIME_AREA;

#endif

void systime_init(void)
{
  /* Set the systime border to 1ms. */
  ptSystimeArea->ulSystime_border = (DEV_FREQUENCY / 100U) - 1U;
  ptSystimeArea->ulSystime_count_value = 10U << 28U;

#if ASIC_TYP==ASIC_TYP_NETX50
  /* Disable systime compare. */
  ptSystimeArea->ulSystime_s_compare_enable = 0;

  /* Reset any pending systime IRQs. */
  ptSystimeArea->ulSystime_s_compare_irq = 1;
#endif
}

unsigned long systime_get_ms(void)
{
  return ptSystimeArea->ulSystime_s;
}

int systime_elapsed(unsigned long ulStart, unsigned long ulDuration)
{
  /* get the time difference */
  unsigned long ulDiff = ptSystimeArea->ulSystime_s - ulStart;

  return (ulDiff >= ulDuration);
}

/*
 * \brief Stops the current execution for a given time.
 *
 *  \param ulDuration The time to wait in milliseconds.
 */
void systime_delay_ms(unsigned long ulDuration)
{
  unsigned long ulStart;
  int iElapsed;

  ulStart = systime_get_ms();
  do
  {
    iElapsed = systime_elapsed(ulStart, ulDuration);
  } while(iElapsed == 0);
}

void systime_handle_start_ms(TIMER_HANDLE_T *ptHandle, unsigned long ulDuration)
{
  ptHandle->ulStart = systime_get_ms();
  ptHandle->ulDuration = ulDuration;
}

int systime_handle_is_elapsed(TIMER_HANDLE_T *ptHandle)
{
  return systime_elapsed(ptHandle->ulStart, ptHandle->ulDuration);
}
