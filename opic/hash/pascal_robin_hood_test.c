/* pascal_robin_hood_test.c ---
 *
 * Filename: pascal_robin_hood_test.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Created: Sun May 21 15:56:43 2017 (-0700)
 * Version:
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
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/* Code: */


#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <sys/mman.h>
#include <string.h>
#include <cmocka.h>

#include "opic/common/op_log.h"
#include "pascal_robin_hood.h"

OP_LOGGER_FACTORY(logger, "opic.hash.pascal_robin_hood_test");

#define TEST_OBJECTS (1 << 15)

static int objcnt = 0;
static uint8_t objmap[TEST_OBJECTS];

void ResetObjcnt(void)
{
  objcnt = 0;
}

void ResetObjmap(void)
{
  memset(objmap, 0x00, sizeof(objmap));
}

void CountObjects(void* key, void* val,
                  size_t keysize, size_t valsize, void* ctx)
{
  objcnt++;
}

void CheckObjects(void* key, void* val,
                  size_t keysize, size_t valsize, void* ctx)
{
  int* intkey = key;
  objmap[*intkey] = 1;
}

static void
test_RHHNew(void** context)
{
  OPHeap* heap;
  PascalRobinHoodHash* rhh;
  assert_true(OPHeapNew(&heap));
  assert_true(PRHHNew(heap, &rhh, TEST_OBJECTS,
                      0.95, 0));
  PRHHDestroy(rhh);
  OPHeapDestroy(heap);
}

/*
static void
test_BasicInsert(void** context)
{
  OPHeap* heap;
  PascalRobinHoodHash* rhh;

  OP_LOG_INFO(logger, "Starting basic insert");
  assert_true(OPHeapNew(&heap));
  assert_true(PRHHNew(heap, &rhh, 20,
                      0.80, sizeof(int), 0));
  OP_LOG_DEBUG(logger, "RHH addr %p", rhh);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      OP_LOG_DEBUG(logger, "Inserting %d", i);
      PRHHPut(rhh, &i, NULL);
    }
  //PRHHPrintStat(rhh);
  assert_int_equal(TEST_OBJECTS, PRHHObjcnt(rhh));
  ResetObjcnt();
  PRHHIterate(rhh, CountObjects, NULL);
  assert_int_equal(TEST_OBJECTS, objcnt);
  ResetObjmap();
  PRHHIterate(rhh, CheckObjects, NULL);
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      assert_int_equal(1, objmap[i]);
    }
  PRHHDestroy(rhh);
  OPHeapDestroy(heap);
}

static void
test_BasicDelete(void** context)
{
  OPHeap* heap;
  PascalRobinHoodHash* rhh;

  assert_true(OPHeapNew(&heap));
  assert_true(PRHHNew(heap, &rhh, TEST_OBJECTS,
                     0.95, sizeof(int), 0));
  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      PRHHPut(rhh, &i, NULL);
    }
  assert_int_equal(TEST_OBJECTS, PRHHObjcnt(rhh));

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      assert_non_null(PRHHDelete(rhh, &i));
    }
  assert_int_equal(0, PRHHObjcnt(rhh));
  RHHDestroy(rhh);
  OPHeapDestroy(heap);
}

static void
test_DistributionForUpdate(void** context)
{
  OPHeap* heap;
  PascalRobinHoodHash* rhh;
  int key;

  assert_true(OPHeapNew(&heap));
  assert_true(PRHHNew(heap, &rhh, TEST_OBJECTS,
                     0.70, sizeof(int), 0));

  for (int i = 0; i < TEST_OBJECTS; i++)
    {
      PRHHPut(rhh, &i, NULL);
    }
  assert_int_equal(TEST_OBJECTS, PRHHObjcnt(rhh));
  // TODO Change API to test the highest probe
  PRHHPrintStat(rhh);

  for (int i = TEST_OBJECTS; i < TEST_OBJECTS*10; i++)
    {
      key = i - TEST_OBJECTS;
      PRHHDelete(rhh, &key);
      PRHHPut(rhh, &i, NULL);
    }
  PRHHPrintStat(rhh);
  PRHHDestroy(rhh);
  OPHeapDestroy(heap);
}
*/

int
main (void)
{
  const struct CMUnitTest prhh_tests[] =
    {
      cmocka_unit_test(test_RHHNew),
      // cmocka_unit_test(test_BasicInsert),
      // cmocka_unit_test(test_BasicDelete),
      // cmocka_unit_test(test_DistributionForUpdate),
    };

  return cmocka_run_group_tests(prhh_tests, NULL, NULL);
}

/* robin_hood_test.c ends here */

/* pascal_robin_hood_test.c ends here */
