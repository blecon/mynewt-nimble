/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <stddef.h>
#include "os/os.h"
#include "sysinit/sysinit.h"
#include "host/ble_hs.h"
#if NIMBLE_CFG_CONTROLLER
#include "controller/ble_ll.h"
#endif

void
nimble_port_init(void)
{
    void os_msys_init(void);
    void ble_store_ram_init(void);
#if NIMBLE_CFG_CONTROLLER
    void ble_hci_ram_init(void);
#endif

    os_msys_init();

    ble_hs_init();

    /* XXX Need to have template for store */
    ble_store_ram_init();

#if NIMBLE_CFG_CONTROLLER
    hal_timer_init(5, NULL);
    os_cputime_init(32768);
    ble_ll_init();
    ble_hci_ram_init();
#endif
}

#if NIMBLE_CFG_CONTROLLER
void
nimble_port_ll_task_func(void *arg)
{
    extern void ble_ll_task(void *);

    ble_ll_task(arg);
}
#endif