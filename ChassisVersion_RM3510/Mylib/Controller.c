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
 
#include "Controller.h"
#include "main.h"

WorkingState workingState = WORKING_STATE_STOP;
WorkingState lastWorkingState = WORKING_STATE_STOP;

int threshold = 0;
void WorkingStateSM(void)
{
	//printf("^");
	lastWorkingState = workingState;
	
	/*
	if(!DBUS_Det(dbus))//rc¿ªÆôÅÐ¶Ï
	{
		workingState = WORKING_STATE_STOP;
		return;
	}
	*/
	
	switch(dbus.rc.s2) // RC is opened
	{
		case SW_UP:
		{
			workingState = WORKING_STATE_SIM;
		}break;
		case SW_MID:
		{
			workingState = WORKING_STATE_NORMAL;
		}break;
		case SW_DOWN:
		case 0: // not open rc
		default:
		{
			threshold ++;
			if(threshold >= 10){
				workingState = WORKING_STATE_STOP;
				threshold = 0;
			}
			
		}break;
	}	

}


int near_offset(int a, int offset)
{
	if(abs(a - offset) < 2){
		return 1;
	}
	return 0;
}

int all_ch_near_offset()
{
	if(near_offset(dbus.rc.ch0, CH_VALUE_OFFSET) && near_offset(dbus.rc.ch1, CH_VALUE_OFFSET) && near_offset(dbus.rc.ch2, CH_VALUE_OFFSET))
	{
		//printf("*");
		return 1;
	}
	return 0;
}


static uint32_t ms_tick = 0;
void ControlTask(void)
{
	ms_tick++;
	WorkingStateSM();
	
	if( workingState != lastWorkingState || workingState == WORKING_STATE_STOP ) // state changed
	{
		//printf(";");
		ms_tick = 0;
		Controller_Reset();		
		ChassisMotor_Velocity_Control(0,0,0,0);
	}
	if(ms_tick % 4 == 0)
	{
		if(workingState == WORKING_STATE_SIM)
			{
				ChassisMotor_Position_Control(sdbus.w1,sdbus.w2,sdbus.w3,sdbus.w4);
			}
			else if(workingState == WORKING_STATE_NORMAL)
			{
				move_control(dbus.rc.ch0, dbus.rc.ch1, dbus.rc.ch2, dbus.rc.s1, dbus.key.v,dbus.mouse.x);
			}
	}

}

void RM3510_DATA_RESET(RM3510_DATA* ptr_RM3510_DATA)
{
	memset(ptr_RM3510_DATA, 0, sizeof(RM3510_DATA));
}


void Encoder_ResetAll(void)
{
	RM3510_DATA_RESET(&RM3510_1);
	RM3510_DATA_RESET(&RM3510_2);
	RM3510_DATA_RESET(&RM3510_3);
	RM3510_DATA_RESET(&RM3510_4);
}

void Controller_Reset(void)
{
	Encoder_ResetAll();
	SDBUS_Reset(&sdbus);
	DBUS_Reset(&dbus);
}

