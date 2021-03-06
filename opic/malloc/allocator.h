/* allocator.h ---
 *
 * Filename: allocator.h
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Copyright: (c) 2016-2017 Felix Chern
 * Created: Sat Oct 8, 2016
 * Version: 0.3.0
 * Package-Requires: ()
 * Last-Updated:
 *           By:
 *     Update #: 0
 * URL:
 * Doc URL:
 * Keywords:
 * Compatibility:
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change Log:
 *
 *
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Code: */

#ifndef OPIC_MALLOC_ALLOCATOR_H
#define OPIC_MALLOC_ALLOCATOR_H 1

#include "objdef.h"

OP_BEGIN_DECLS

bool
DispatchUSpanForAddr(OPHeapCtx* ctx, Magic magic, void** addr)
  __attribute__ ((visibility ("internal")));

bool
DispatchHPageForSSpan(OPHeapCtx* ctx, Magic magic, unsigned int spage_cnt,
                      bool use_full_span)
  __attribute__ ((visibility ("internal")));

QueueOperation
USpanObtainAddr(OPHeapCtx* ctx, void** addr)
  __attribute__ ((visibility ("internal")));

QueueOperation
HPageObtainSSpan(OPHeapCtx* ctx, unsigned int spage_cnt, bool use_full_span)
  __attribute__ ((visibility ("internal")));

QueueOperation
HPageObtainUSpan(OPHeapCtx* ctx, unsigned int spage_cnt, bool use_full_span)
  __attribute__ ((visibility ("internal")));

bool OPHeapObtainHPage(OPHeap* heap, OPHeapCtx* ctx)
  __attribute__ ((visibility ("internal")));

bool OPHeapObtainHBlob(OPHeap* heap, OPHeapCtx* ctx, unsigned int hpage_cnt)
  __attribute__ ((visibility ("internal")));

bool
OPHeapObtainSmallHBlob(OPHeap* heap, OPHeapCtx* ctx, unsigned int hpage_cnt)
  __attribute__ ((visibility ("internal")));

bool
OPHeapObtainLargeHBlob(OPHeap* heap, OPHeapCtx* ctx, unsigned int hpage_cnt)
  __attribute__ ((visibility ("internal")));

OP_END_DECLS

#endif
/* allocator.h ends here */
