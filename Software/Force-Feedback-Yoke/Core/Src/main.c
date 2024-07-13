/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <devices/aAS5600.h>
#include "utilities/utilities.h"
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <usbd_customhid.h>
#include <stdbool.h>
#include <stdio.h>
#include <testing/motor_logger.h>
#include "encoder.h"
#include "pid.h"
#include "motor.h"
#include "peripherals/gpio.h"
#include "devices/ina219.h"
#include "force_feedback_controller.h"
#include "force_feedback_periodic.h"
#include "anti_cog.h"
#include "devices/home_sensor.h"
#include "usb_report.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define MOTOR_OFFSET 1300

#define ENCODER_HOME_OFFSET (-337)

#define ENCODER_NUM_SAMPLES 4
#define ENCODER_BUFFER_SIZE (ENCODER_NUM_SAMPLES+1)

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
extern USBD_HandleTypeDef hUsbDeviceFS;

typedef struct {
	int16_t joyX;
	int16_t joyY;
	uint8_t joyB1;
} GameHID_t;


//RotaryEncoder_t encoder;
int32_t prevEncoderCount;

// Circular buffer storing encoder samples
int32_t encoderBuffer[ENCODER_BUFFER_SIZE];
int32_t encoderBufferStart;
int32_t encoderBufferEnd;
int64_t encoderAccumulator;

Ina219_t currentSense;

PID_t positionPid;
PID_t currentPid;

Motor_t pitchMotor, rollMotor;

AS
Encoder_t pitchEncoder, rollEncoder;
float derivativeTerm;

FFBController_t pitchFFB, rollFFB;

HomeSensor_t homeSensor;
MotorController_t pitchMController, rollMController;

uint8_t reportTxBuffer[3];
uint8_t txBuffer[64];
uint8_t report_buffer[64];
uint8_t flag = 0;
uint8_t flag_rx = 0;

UsbReport_t usbReport;

//for live debugging
float avgAngle;
float angle;
float endStopKp = 0.01f;
float endStopKd = 0.01f;
FFBPeriodic_t periodic;

static volatile int32_t motorPowerLog;

//float testCurrent;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM7_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim == &htim6) {

		EncoderUpdate(&pitchEncoder, 0.5);
		EncoderUpdate(&rollEncoder, 0.5);

//		RotaryEncUpdate(&encoder, __HAL_TIM_GET_COUNTER(&htim4), 0.5);
//		encoderBuffer[encoderBufferEnd] = RotaryEncGetCount(&encoder);
//
//		// Add new value, subtract old value
//		encoderAccumulator += encoderBuffer[encoderBufferEnd] -
//				encoderBuffer[encoderBufferStart];
//
//		encoderBufferStart++;
//		if(encoderBufferStart == ENCODER_BUFFER_SIZE) {
//			encoderBufferStart = 0;
//		}
//
//		encoderBufferEnd++;
//		if(encoderBufferEnd == ENCODER_BUFFER_SIZE) {
//			encoderBufferEnd = 0;
//		}
	}
	else if(htim == &htim7) {
		MotorControllerUpdate(&controller, 2);
		//testCurrent = MotorControllerGetCurrent(&controller);
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_USB_DEVICE_Init();
  MX_TIM1_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */


  // TODO: Remove
  GameHID_t gameHID = {
		  .joyX = 0,
		  .joyY = 0,
		  .joyB1 = 0
  };

  UsbReportInit(&usbReport, USB_REPORT_IN_LITTLE_ENDIAN);

  PIDInit(&positionPid);
  RotaryEncInit(&encoder);

  encoderAccumulator = 0;
  encoderBufferStart = 0;
  encoderBufferEnd = ENCODER_NUM_SAMPLES;

  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

  PIDInit(&currentPid);
  currentPid.kP = 3580;
  currentPid.kI = 0;
  currentPid.kD = 0;
  CurrentSenseInit(&currentSense, &hi2c1);

  GPIO_t gpioMotorReverse;
  GPIOInit(&gpioMotorReverse, MOTOR_FORWARD_GPIO_Port, MOTOR_FORWARD_Pin);

  GPIO_t gpioMotorForward;
  GPIOInit(&gpioMotorForward, MOTOR_REVERSE_GPIO_Port, MOTOR_REVERSE_Pin);

  MotorInit(&motor, &htim1, TIM_CHANNEL_3, gpioMotorReverse, gpioMotorForward);
  //MotorSetOffset(&motor, MOTOR_OFFSET);
  MotorStartPWM(&motor);

  FFBInit(&ffb);

  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_Base_Start_IT(&htim6);

  while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET){}

  //Home motor
  GPIO_t homeSensorGpio;
  GPIOInit(&homeSensorGpio, HOME_SENSOR_GPIO_Port, HOME_SENSOR_Pin);
  HomeSensorInit(&homeSensor, homeSensorGpio);
  HomeSensorHome(&homeSensor, &motor);

// TODO: Remove. For setting up home offsets
//  while(1) {
//	  printf("%d\r\n", (int)RotaryEncGetCount(&encoder));
//  }

  //Reset encoder count after homing
  HAL_Delay(500);
  RotaryEncSetCount(&encoder, ENCODER_HOME_OFFSET);

  printf("Homing complete\r\n");

  MotorControllerInit_t controllerInit = {
		  .motor = &motor,
		  .encoder = &encoder,
		  .currentSensor = &currentSense,
		  .positionPid = &positionPid,
		  .currentPid = &currentPid,
  };
  MotorControllerInit(&controller, controllerInit);
  HAL_TIM_Base_Start_IT(&htim7);

//  int32_t motorPower = 0;
//  while(1) {
//	  printf("Speed: %f\r\n", RotaryEncGetSpeed(&encoder));
//	  HAL_Delay(1);
//
//	  uint8_t character = NULL;
//	  HAL_UART_Receive(&huart1, &character, 1, 100);
//	  if(character == 'd') {
//		  motorPower += 100;
//	  }
//	  else if (character == 'a') {
//		  motorPower -= 100;
//	  }
//
//	  MotorControllerSetPower(&controller, motorPower);
//  }

  MotorLogger_t mLogger;
  MotorLoggerInit(&mLogger, &controller);
//  MotorLoggerVRun(&mLogger, 2400, 100);
//  MotorLoggerARun(&mLogger, 2400, 2);

//  AntiCog_t antiCog;
//  AntiCogInit(&antiCog, &controller, &positionPid);

//  while(1) {
//	  while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET){}
//  AntiCogRun(&antiCog);
 // AntiCogTest(&antiCog);
//  }

  //MotorControllerSetCurrent(&controller, 0.3);
//  while(1){}


//  while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET){}

//  printf("Forward Calibration Values:\r\n");
//  for(int i = 0; i < ENCODER_COUNT_PER_REV; i++) {
//	  printf("%d,\r\n", (int)(AntiCogGetCalAt(&antiCog, i)));
//  }

// AntiCogTest(&antiCog);

//  for(;;){}

  //for(;;){}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  unsigned long previousTimeInMs = HAL_GetTick();
  FFBPeriodicInit(&periodic, 0, 120, 0);
  periodic.gain = 2.5;

  int32_t periFrequency = 0;
  float periAmplitude = 0.0f;
  float sprStrength = 0.0f;
  while(1) {

	  if(flag_rx == 1){

		  flag_rx = 0;

		  UsbReportLoad(&usbReport, report_buffer,
				  USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
		  sprStrength = UsbReportParseNextFloat(&usbReport);
		  periAmplitude = UsbReportParseNextFloat(&usbReport);
		  periFrequency = UsbReportParseNextInt(&usbReport);

//		  float strength;
//		  memcpy(&sprStrength, &report_buffer[1], sizeof(float));
//		  memcpy(&periAmplitude, &report_buffer[1+sizeof(float)],
//				  sizeof(float));
//		  memcpy(&periFrequency, &report_buffer[1+sizeof(float)*2],
//				  sizeof(float));

//
//		  angle = (RotaryEncGetCount(&encoder)/200.0f) * 90.0f;
//		  float motorPower = -FFBComputeSpringForce(&ffb,
//				  angle, 0.0f, strength);
//

		  // Prepare and send aileron axis
		  int16_t aileron = (int16_t)Constrain(((
				  RotaryEncGetCount(&encoder)/200.0f) *
				  32767), -32767, 32767);

		  // Set report ID to 1
		  reportTxBuffer[0] = 0x01;
		  reportTxBuffer[1] = aileron & 0xFF;
		  reportTxBuffer[2] = aileron >> 8;

		  USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, reportTxBuffer, 3);

		  //USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&aileron, 2);
	  }

	  if(flag == 1) {
		  USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, txBuffer, 64);

		  flag = 0;
	  }

	  angle = (RotaryEncGetCount(&encoder)/200.0f) * 90.0f;
	  float motorPower = -FFBCalcSpringForce(&ffb,
			  angle, 0.0f, sprStrength);

	  //TODO: Remove after testing
	  periodic.amplitude = periAmplitude;
	  periodic.frequency = periFrequency;

	  uint32_t timeInMs = HAL_GetTick();
	  motorPower += CalcFFBPeriodic(&periodic, timeInMs - previousTimeInMs)
			  * 1000.0f;
	  previousTimeInMs = timeInMs;

	  avgAngle = ((((float)encoderAccumulator)/ENCODER_NUM_SAMPLES)/
			  200.0f) * 90.0f;

	  if(angle > 90.0f || angle < -90.0f) {
		  float speed = (RotaryEncGetSpeed(&encoder)/200.0f) * 90.0f;
		  derivativeTerm = speed * endStopKd;

		  float error = angle > 90.0f ? angle - 89.5f : angle + 89.5f;

		  motorPower += UINT16_MAX * (error * endStopKp +
				   derivativeTerm);
	  }

	  motorPower = ConstrainFloat(motorPower, -UINT16_MAX, UINT16_MAX);
	  MotorControllerSetPower(&controller, (int32_t)motorPower);

	  //TODO: Remove. For logging
	  motorPowerLog = motorPower;

	  HAL_Delay(1);
  }

//  uint32_t printfCounter = 0;
//  int32_t prevEncCount = 0;
//  while (1)
//  {
//	  int32_t joyYOut = RotaryEncGetCount(&encoder);
//	  float speed = (joyYOut - prevEncCount)/0.005;
//
//	 // printf("Count: %d\r\n", (int)__HAL_TIM_GET_COUNTER(&htim4));
//
////	  if(__HAL_TIM_GET_COUNTER(&htim4) >= 667) {
////		  MotorSetPower(&motor, 0);
////	  }
//
//	  //constrain to 8-bit signed integer
//	  joyYOut = Constrain(joyYOut, -32767, 32767);
//
//	  //Motor control
//	  int32_t position = MotorControllerGetPosition(&controller);
//	  int32_t positionAhead = speed < 0 ? position-2 : position+2;
//
//	  float motorPower = FFBComputeDamperForce(&ffb, speed);// +
//			  //AntiCogGetCalAt(&antiCog, positionAhead);
////	  MotorSetPower(&motor, (int32_t)(motorPower));
//
//	  gameHID.joyY = (int16_t)joyYOut;
//	 // USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&gameHID,
//	//		  sizeof(gameHID));
////	  gameHID.joyX += 25;
////	  if(gameHID.joyX >= 32767) {
////		  gameHID.joyX = -32767;
////	  }
//
////	  printfCounter++;
////	  if(printfCounter == 1) {
////		  printf("Current: %f\r\n", CurrentSenseGetCurrent(&currentSense));
////		  printfCounter = 0;
////	  }
//
//	  prevEncCount = joyYOut;
//	  HAL_Delay(10);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_I2C2
                              |RCC_PERIPHCLK_TIM1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_HSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x0000020B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x0000020B;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 2400-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 4;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 4;
  if (HAL_TIM_Encoder_Init(&htim4, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 24-1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1000-1;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 48-1;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 2000-1;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 38400;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MOTOR_REVERSE_Pin|MOTOR_FORWARD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DRDY_Pin MEMS_INT3_Pin MEMS_INT4_Pin MEMS_INT1_Pin
                           MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = DRDY_Pin|MEMS_INT3_Pin|MEMS_INT4_Pin|MEMS_INT1_Pin
                          |MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : CS_I2C_SPI_Pin LD4_Pin LD3_Pin LD5_Pin
                           LD7_Pin LD9_Pin LD10_Pin LD8_Pin
                           LD6_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : B1_Pin HOME_SENSOR_Pin */
  GPIO_InitStruct.Pin = B1_Pin|HOME_SENSOR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR_REVERSE_Pin MOTOR_FORWARD_Pin */
  GPIO_InitStruct.Pin = MOTOR_REVERSE_Pin|MOTOR_FORWARD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
