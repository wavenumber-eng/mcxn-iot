/*
 * CAN FD Testing of motor real time control loop
 */

#include <stdio.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/can.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/sys_clock.h>

const struct device *const RTCtrlCANBus_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_canbus));
struct gpio_dt_spec led = GPIO_DT_SPEC_GET_OR(DT_ALIAS(led0), gpios, {0});


/***************************
Module defines
****************************/
/* debugging options */
#define SERIAL_DIAGNOSTICS

/* CAN bus settings */
//#define USE_LOOPBACK		/* use loopback to self-ack if this is the only active node to avoid entering error passive state during testing */
#define USE_CAN_FD			/* use CAN FD if defined or standard CAN if not (for initial testing with non-FD capable tools) */
#define CAN_STD_BITRATE				(500000)	/* CAN standard & FD Aritration phase bitrate */
#define CAN_STD_SAMP_PT_PERMILLE	(750)		/* CAN standard & FD Aritration phase sampling point */
#define CAN_FD_BITRATE				(2000000)	/* CAN FD Data phase sampling point */
#define CAN_FD_SAMP_PT_PERMILLE		(750)		/* CAN FD Data phase sampling point */

/* interval to generate the data request poll message */
#define POLL_INTERVAL_US	(1000000)

/* CAN message & signal defines - ideally these will be auto-generated from the .dbc definition file */
/* message PDU_Poll */
#define PDU_Poll_ID			(0x20)
#define PDU_Poll_DLC		(1)
#define PDU_Poll_TIMEOUT_US	(100)	/* As we're managing the data then any delay sending is an indication of a fault and results in a failed cycle */
/* message ADM_Status */
#define ADM_Status_ID		(0x60)
#define ADM_Status_DLC		(32)
/* message AzMotor_Status */
#define AzMotor_Status_ID	(0x61)
#define AzMotor_Status_DLC	(8)
/* message ZenMotor_Status */
#define ZenMotor_Status_ID	(0x62)
#define ZenMotor_Status_DLC	(8)
/* message PDU_Targets */
#define PDU_Targets_ID		(0xA0)
#define PDU_Targets_DLC		(16)
/* signals */
/* PDU_Poll - not really the way to do it as not flexible for other signals,
              Should have a start bit offset & length specified but OK for testing */
#define ADMPollReq			(BIT(0))
#define AzMotorPollReq		(BIT(1))
#define ZenMotorPollReq		(BIT(2))

/***************************
Module private prototypes
****************************/
static bool MotorRTCtrlInitialise(void);
static bool MotorRTCtrlInitCAN(void);
static bool MotorRTCtrlInitLED(void);
static bool MotorRTCtrlSetCANTiming(void);
static bool MotorRTCtrlSetCANStdTiming(void);
static bool MotorRTCtrlSetCANFDTiming(void);
static void MotorRTCtrlProcess(void);
static bool MotorRTCtrlReqData(void);
static void MotorRTCtrlCANTx_callback(const struct device* Dev, int Error, void* InfoPtr);
static const char* MotorRTCtrlCANStateToStr(enum can_state CANState);
static void MotorRTCtrlToggleLED(void);

/***************************
Module public functions
****************************/
/***********************************************************************
Task main process

Parameters: None
Return: None
***********************************************************************/
int main(void)
{
	int err;
	struct can_timing StdTiming;
	struct can_timing FDTiming;
		
	//can_calc_timing(Arbitration Timing Values);
	//can_set_timing(Arbitration Timing Values);
	//can_calc_timing_data(Data Timing Values);
	//can_set_timing_data(Data Timing Values);

	if (can_calc_timing(RTCtrlCANBus_dev, &StdTiming, CAN_STD_BITRATE, CAN_STD_SAMP_PT_PERMILLE) != 0)
		printf("Error calculating CAN std timing\r\n");

	if (can_set_timing(RTCtrlCANBus_dev, &StdTiming) != 0)
		printf("Error setting CAN std timing\r\n");

	if (can_calc_timing_data(RTCtrlCANBus_dev, &FDTiming, CAN_FD_BITRATE, CAN_FD_SAMP_PT_PERMILLE) != 0)
		printf("Error calculating CAN FD timing\r\n");

	if (can_set_timing_data(RTCtrlCANBus_dev, &FDTiming) != 0)
		printf("Error setting CAN FD timing\r\n");

	err = can_set_mode(RTCtrlCANBus_dev, CAN_MODE_FD);
	if(err != 0){
		printf("ERROR SETTING CAN MODE\n");
		
	}

	printf("CAN Configured correctly\n");


	err = can_start(RTCtrlCANBus_dev);
	if(err != 0){
		printf("ERROR STARTING CAN\n");
	}

	while(true)
	{
		struct can_frame PDU_Poll =
		{
			//.flags =  0,
			.flags = CAN_FRAME_FDF | CAN_FRAME_BRS, /* CAN FD with BRS */
			.id = 0x20,
			.dlc = 1,
			.data[0] = 3
		};
		can_send(RTCtrlCANBus_dev, &PDU_Poll, K_MSEC(100), NULL, NULL);

		/* thread sleep until the next request is due */
		k_sleep(K_MSEC(50));
			
	}

//	if(true == MotorRTCtrlInitialise())
//	{
//		while(true)
//		{
//			MotorRTCtrlProcess();
//		}
//	}
//#ifdef SERIAL_DIAGNOSTICS
//	else
//	{
//		printf("MotorRTCtrlInitialise() failed\r\n");
//	}
//#endif
}



/***************************
Module private functions
****************************/
/***********************************************************************
Initialise the Task related elements

Parameters: None
Return: true if successful
***********************************************************************/
static bool MotorRTCtrlInitialise(void)
{
	bool RetVal = false;

	if(true == MotorRTCtrlInitCAN())
	{
		if(true == MotorRTCtrlInitLED())
		{
			RetVal = true;
		}
		
	}

	return RetVal;
}



/***********************************************************************
Initialise the LED

Parameters: None
Return: true if successful
***********************************************************************/
static bool MotorRTCtrlInitLED(void)
{
	bool RetVal = false;

	if (NULL != led.port) 
	{
		if(true == gpio_is_ready_dt(&led))
		{
			if(0 == gpio_pin_configure_dt(&led, GPIO_OUTPUT_HIGH))
			{
				RetVal = true;
			}
#ifdef SERIAL_DIAGNOSTICS
			else
			{
				printf("Error setting LED pin to output mode");
			}
		}
		else
		{
			printf("LED device not ready.\n");
		}
	}
	else
	{
		printf("LED device not asigned");
	}
#else
		}
	}
#endif
	return RetVal;
}



/***********************************************************************
Initialise the Real Time Control CAN bus

Parameters: None
Return: true if successful
***********************************************************************/
static bool MotorRTCtrlInitCAN(void)
{
	bool RetVal = false;
#ifdef USE_CAN_FD
	can_mode_t CANBusMode = CAN_MODE_FD;
#else
	can_mode_t CANBusMode = CAN_MODE_NORMAL;
#endif

#ifdef USE_LOOPBACK
	CANBusMode |= CAN_MODE_LOOPBACK;
#endif

	if(true == device_is_ready(RTCtrlCANBus_dev))
	{
		if(true == MotorRTCtrlSetCANTiming())
		{
			if(0 == can_set_mode(RTCtrlCANBus_dev, CANBusMode))
			{
				if(0 == can_start(RTCtrlCANBus_dev))
				{
					RetVal = true;
				}
#ifdef SERIAL_DIAGNOSTICS
				else
				{
					/* CAN start failed */
					printf("CAN bus failed to start\r\n");
				}
			}
			else
			{
				/* CAN Set Mode failed */
				printf("Error setting CAN Mode");
			}
		}
		else
		{
			/* MotorRTCtrlSetCANTiming()n failed */
			printf("CAN bus failed to set timing\r\n");
		}
	}
	else
	{
		/* CAN initialisation failed */
		printf("CAN bus not ready in initialisation\r\n");
	}
#else
			}
		}	
	}
#endif

	return RetVal;

}



/***********************************************************************
Configure the Real Time Control CAN bus timing parameters

Parameters: None
Return: true if successful
***********************************************************************/
static bool MotorRTCtrlSetCANTiming(void)
{
	bool RetVal = false;

	if(true == MotorRTCtrlSetCANStdTiming())
	{
		if(true == MotorRTCtrlSetCANFDTiming())
		{
			RetVal = true;
		}
#ifdef SERIAL_DIAGNOSTICS
		else
		{
			printf("MotorRTCtrlSetCANTiming Erorr(FD)\r\n");
		}
	}
	else
	{
		printf("MotorRTCtrlSetCANTiming Erorr(std)\r\n");
	}
#else
	}
#endif
	return RetVal;
}



/***********************************************************************
Configure the Real Time Control CAN bus timing parameters for standard CAN
and the arbitration phase of CAN FD if used

Parameters: None
Return: true if successful
***********************************************************************/
static bool MotorRTCtrlSetCANStdTiming(void)
{
	bool RetVal = false;
	struct can_timing StdTiming;

	if(0 == can_calc_timing(RTCtrlCANBus_dev, &StdTiming, CAN_STD_BITRATE, CAN_STD_SAMP_PT_PERMILLE))
	{
		if(0 == can_set_timing(RTCtrlCANBus_dev, &StdTiming))
		{
			RetVal = true;
		}
#ifdef SERIAL_DIAGNOSTICS
		else
		{
			printf("Error setting CAN std timing\r\n");
		}
	}
	else
	{
		printf("Error calculating CAN std timing\r\n");
	}
#else
	}
#endif
	return RetVal;
}



/***********************************************************************
Configure the Real Time Control CAN bus timing parameters for FD data phase

Parameters: None
Return: true if successful
***********************************************************************/
static bool MotorRTCtrlSetCANFDTiming(void)
{
#ifdef USE_CAN_FD
	bool RetVal = false;
	struct can_timing FDTiming;

	if(0 == can_calc_timing_data(RTCtrlCANBus_dev, &FDTiming, CAN_FD_BITRATE, CAN_FD_SAMP_PT_PERMILLE))
	{
		if(0 == can_set_timing_data(RTCtrlCANBus_dev, &FDTiming))
		{
			RetVal = true;
		}
#ifdef SERIAL_DIAGNOSTICS
		else
		{
			printf("Error setting CAN FD timing\r\n");
		}
	}
	else
	{
		printf("Error calculating CAN FD timing\r\n");
	}
#else
	}
#endif
	return RetVal;
#else	/* #ifdef USE_CAN_FD */
	return true;
#endif /* #ifdef USE_CAN_FD */
}


/***********************************************************************
Motor real time control loop main operating process

Parameters: None
Return: None
***********************************************************************/
static void MotorRTCtrlProcess(void)
{
	/* set a timepoint to that for the next poll */
	k_timepoint_t RequestTimepoint = sys_timepoint_calc(K_USEC(POLL_INTERVAL_US));
	if(true == MotorRTCtrlReqData())
	{
		/* request buffered */
		/* ToDo: wait for transmission confirmation & then any responses */
	}
#ifdef SERIAL_DIAGNOSTICS
	else
	{
		/* request failed */
		printf("failed to generate CAN request\r\n");
	}
#endif

	/* thread sleep until the next request is due */
	k_sleep(sys_timepoint_timeout(RequestTimepoint));

}


/***********************************************************************
Initiate request for input data from all the required sources

Parameters: None
Return: boolean true if successful
***********************************************************************/
static bool MotorRTCtrlReqData(void)
{	
	bool RetVal = false;
	enum can_state BusState;
	static enum can_state PrevBusState = CAN_STATE_ERROR_ACTIVE;
	struct can_bus_err_cnt BusErrCnt = {0, 0};
	static struct can_bus_err_cnt PrevBusErrCnt = {0, 0};
	int Result;
	struct can_frame PDU_Poll =
	{
#ifdef USE_CAN_FD
		.flags = CAN_FRAME_FDF | CAN_FRAME_BRS,	/* standard length ID by default, CAN FD with BRS */
#else
		.flags = 0,
#endif
		.id = PDU_Poll_ID,
		.dlc = PDU_Poll_DLC,
		.data[0] = (ADMPollReq | AzMotorPollReq | ZenMotorPollReq)	/* request data from all 3 sources */
	};

	Result = can_get_state(RTCtrlCANBus_dev, &BusState, &BusErrCnt);
	if(0 == Result)
	{
		/* error active & error warning are able to send, others will fail */
		if( (CAN_STATE_ERROR_ACTIVE == BusState) || (CAN_STATE_ERROR_WARNING == BusState) )
		{
			Result = can_send(RTCtrlCANBus_dev, &PDU_Poll, K_USEC(PDU_Poll_TIMEOUT_US), MotorRTCtrlCANTx_callback, "Request Data");
			if(0 == Result)
			{
				RetVal = true;
			}
#ifdef SERIAL_DIAGNOSTICS
			else
			{
				printf("can_send() failed: %d\r\n",Result);
			}			
		}
		/* don't need an else as it'll be picked up by the change of BusState below */
		
		if(BusState != PrevBusState)
		{
			printf("CAN Bus state change from %s to %s\r\n", MotorRTCtrlCANStateToStr(PrevBusState), MotorRTCtrlCANStateToStr(BusState));
		}
		if((BusErrCnt.rx_err_cnt != PrevBusErrCnt.rx_err_cnt) ||
		    (BusErrCnt.tx_err_cnt != PrevBusErrCnt.tx_err_cnt) )
		{
			printf("CAN Bus Error Count Tx: %d, Rx: %d\r\n", BusErrCnt.tx_err_cnt, BusErrCnt.rx_err_cnt);
		}
	}
	else
	{
		printf("Failed to determine CAN BUS state: %d\r\n", Result);
	}
#else
	}
#endif
	PrevBusState = BusState;
	PrevBusErrCnt = BusErrCnt;

	return RetVal;
}



/***********************************************************************
CAN transmit callback

Parameters: CAN Device pointer
			error or zero on successful transmission
			user data poninter passed from can_send()
Return: None

The error values are the same as those returned from can_send:
0 				if successful.
-EINVAL			if an invalid parameter was passed to the function.
-ENOTSUP		if an unsupported parameter was passed to the function.
-ENETDOWN		if the CAN controller is in stopped state.
-ENETUNREACH	if the CAN controller is in bus-off state.
-EBUSY			if CAN bus arbitration was lost (only applicable if automatic retransmissions are disabled).
-EIO			if a general transmit error occurred (e.g. missing ACK if automatic retransmissions are disabled).
-EAGAIN			on timeout
***********************************************************************/
static void MotorRTCtrlCANTx_callback(const struct device* Dev, int Error, void* InfoPtr)
{
	ARG_UNUSED(Dev);
	char* SourceStr = (char*)InfoPtr;

	/* ToDO: add transmission confirmation indicator */
	MotorRTCtrlToggleLED();	/* but for now just for visible debugging */

	if (0 != Error)
	{
#ifdef SERIAL_DIAGNOSTICS
		printf("Sending failed [%d]\nData: %s\r\n", Error, SourceStr);
#endif
	}
}



/***********************************************************************
Convert CAN Bus states to descriptive strings

Parameters: CAN Bus state enum
Return:descriptive string const pointer
***********************************************************************/
static const char* MotorRTCtrlCANStateToStr(enum can_state CANState)
{
	const char* RetVal;

	switch (CANState)
	{
		case CAN_STATE_ERROR_ACTIVE:
			RetVal = "error-active";
			break;

		case CAN_STATE_ERROR_WARNING:
			RetVal = "error-warning";
			break;

		case CAN_STATE_ERROR_PASSIVE:
			RetVal = "error-passive";
			break;

		case CAN_STATE_BUS_OFF:
			RetVal = "bus-off";
			break;

		case CAN_STATE_STOPPED:
			RetVal = "stopped";
			break;

		default:
			RetVal =  "unknown";
			break;
	}

	return RetVal;
}



/***********************************************************************
Convert CAN Bus states to descriptive strings

Parameters: CAN Bus state enum
Return:descriptive string pointer
***********************************************************************/
static void MotorRTCtrlToggleLED(void)
{
	static bool LEDOn = false;
	if (led.port != NULL)
	{
			gpio_pin_set(led.port, led.pin, (LEDOn == true) ? 1 : 0);
			LEDOn = !LEDOn;
	}
}
