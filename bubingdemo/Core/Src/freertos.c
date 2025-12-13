/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_can.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
    float sinx;
    float cosx;
    extern can_instance_t *can_instances[CANINSTANCE_NB];
    extern int idx;
    /* USER CODE END PTD */

    /* Private define ------------------------------------------------------------*/
    /* USER CODE BEGIN PD */

    /* USER CODE END PD */

    /* Private macro -------------------------------------------------------------*/
    /* USER CODE BEGIN PM */

    /* USER CODE END PM */

    /* Private variables ---------------------------------------------------------*/
    /* USER CODE BEGIN Variables */

    /* USER CODE END Variables */
    osThreadId defaultTaskHandle;
    osThreadId myTask02Handle;
    osThreadId myTask03Handle;

    /* Private function prototypes -----------------------------------------------*/
    /* USER CODE BEGIN FunctionPrototypes */

    /* USER CODE END FunctionPrototypes */

    void StartDefaultTask(void const *argument);
    extern void StartTask02(void const *argument);
    void StartTask03(void const *argument);

    void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

    /* GetIdleTaskMemory prototype (linked to static allocation support) */
    void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

    /* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
    static StaticTask_t xIdleTaskTCBBuffer;
    static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

    void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
    {
        *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
        *ppxIdleTaskStackBuffer = &xIdleStack[0];
        *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
        /* place for user code */
    }
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 512);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityIdle, 0, 512);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityIdle, 0, 512);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */           

  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  while(1)
  {
      sinx = arm_sin_f32((float)(uwTick));
      cosx = arm_cos_f32((float)(uwTick / 1000));
      printf("sinx is:%f\n", sinx);
      printf("cosx is:%f\n", cosx); 
      

    HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_10);
    osDelay(10);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  while(1)
  {     
      HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_12);
      for (int i = 0;i < idx;i++)
      {
          can_instances[i]->can_txmessage(can_instances[i]);
          CAN_cmd_gimbal();
      }
      
    osDelay(30);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void StartTask02(void const *argument)
{
    /* USER CODE BEGIN StartTask03 */
    /* Infinite loop */
    while (1)
    {
        HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_11);
        osDelay(50);
    }
    /* USER CODE END StartTask03 */
}

/* USER CODE END Application */
