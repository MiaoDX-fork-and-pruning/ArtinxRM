/**
 * Copyright (c) 2011-2016, Mobangjack Äª°ï½Ü (mobangjack@foxmail.com).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <stdint.h>
#include "main.h"

typedef enum
{
	WORKING_STATE_PREPARE = 0x00,
	WORKING_STATE_SIM = 0x01,
	WORKING_STATE_NORMAL = 0x02,
	WORKING_STATE_STOP = 0x03,
}WorkingState;

//extern WorkingState workingState;

void RM3510_DATA_RESET(RM3510_DATA* ptr_RM3510_DATA);
void Controller_Reset(void);
void ControlTask(void);

#endif

