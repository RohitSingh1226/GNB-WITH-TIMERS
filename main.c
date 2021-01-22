#include <math.h>
#include <stdio.h>
#include "arm_math.h"
#include "stm32f4xx.h"     // Device header




#define NB_OF_CLASSES 2
#define VECTOR_DIMENSION 2
arm_gaussian_naive_bayes_instance_f32 S;
const float32_t theta[NB_OF_CLASSES*VECTOR_DIMENSION] = {
  -0.45740326f, -0.27263527f, 
  0.77882176f, 0.4642168f
}; /**< Mean values for the Gaussians */

const float32_t sigma[NB_OF_CLASSES*VECTOR_DIMENSION] = {
	0.60054618f,0.50695834f,
	0.71735215f,1.49744425f
}; /**< Variances for the Gaussians */

const float32_t classPriors[NB_OF_CLASSES] = {
  0.63f,0.37f}; /**< Class prior probabilities */



int main(void)
{
	__disable_irq();   // disabling global interrupt
	SysTick-> LOAD = 160000-1;
	SysTick->VAL = 0;
	SysTick->CTRL = 7;    /// enables the SYSTICK ENABLE interrupt when converted to binary
	S.vectorDimension = VECTOR_DIMENSION; 
  S.numberOfClasses = NB_OF_CLASSES; 
  S.theta = theta;          
  S.sigma = sigma;         
  S.classPriors = classPriors;    
  S.epsilon=1.0000000000000007e-09f; 
	

	__enable_irq();
	
	
	
	
	
	
	
	

	
}


void SysTick_Handler(void)     // callback function
{
	 float32_t in[2];

  /* Result of the classifier */
  float32_t result[NB_OF_CLASSES];
  float32_t maxProba;
  uint32_t index;
  
	in[0] = -0.457f;
  in[1] = -0.272f;

  index = arm_gaussian_naive_bayes_predict_f32(&S, in, result);

  maxProba = result[index];
	

#if defined(SEMIHOSTING)
  printf("Class = %d\n", index);
#endif


#if !defined(SEMIHOSTING)
  while (1); /* main function does not return */
#endif
	
	
	
}