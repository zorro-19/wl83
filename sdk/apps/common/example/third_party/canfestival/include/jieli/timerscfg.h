/*
This file is part of CanFestival, a library implementing CanOpen Stack.

Copyright (C): Edouard TISSERANT and Francis DUPIN

See COPYING file for copyrights details.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __CANOPEN_TIMERSCFG_H__
#define __CANOPEN_TIMERSCFG_H__
#include "canopen_def.h"
/* Time unit : ns */
/* Time resolution : 64bit (~585 years) */
#define TIMEVAL unsigned long long
#define TIMEVAL_MAX   0xFFFF

#ifdef CANOPEN_TIMER_10MS_ENABLE
#define MS_TO_TIMEVAL(ms) ((ms) / 10)//等于1ms
#define US_TO_TIMEVAL(us) ((us) / 10000)//等于1us
#else
#define MS_TO_TIMEVAL(ms) ((ms) * 1)//等于1ms
#define US_TO_TIMEVAL(us) ((us) / 1000)//等于1us
#endif

#define TASK_HANDLE void*

#endif
