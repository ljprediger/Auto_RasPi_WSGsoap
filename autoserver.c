/*
	autoserver.c

	Ejemplo para setaer la direccion y sentido de un auto

	Compilation in C :
	$ soapcpp2 -c auto.h
	$ gcc -o autoserver autoserver.c stdsoap2.c soapC.c soapServer.c -l bcm2835
*/
//Esto lo agrego para probar----ELIMINAR COMENTARIO
#include <bcm2835.h>
#include <stdio.h>


#include "soapH.h"
#include "setAuto.nsmap"


#define PIN_PWM_Servo 		RPI_V2_GPIO_P1_33
#define PIN_PWM_Motor 		RPI_GPIO_P1_12
#define PIN_MotorAdelante 	RPI_GPIO_P1_08
#define PIN_MotorAtras 		RPI_GPIO_P1_10


#define PWM_CHANNEL_0 0
#define PWM_CHANNEL_1 1

#define RANGE 1024


int main(int argc, char **argv){ 

    if (!bcm2835_init())
	return 1;
	
	bcm2835_gpio_fsel(PIN_MotorAdelante, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(PIN_MotorAtras , BCM2835_GPIO_FSEL_OUTP);
	
	bcm2835_gpio_fsel(PIN_PWM_Servo, BCM2835_GPIO_FSEL_ALT0);
    bcm2835_pwm_set_clock(375);
    bcm2835_pwm_set_mode(PWM_CHANNEL_1, 1, 1);
    bcm2835_pwm_set_range(PWM_CHANNEL_1, RANGE);
    
    bcm2835_gpio_fsel(PIN_PWM_Motor, BCM2835_GPIO_FSEL_ALT5);
    bcm2835_pwm_set_mode(PWM_CHANNEL_1, 1, 1);
    bcm2835_pwm_set_range(PWM_CHANNEL_1, RANGE);
    bcm2835_pwm_set_data(PWM_CHANNEL_0, 66);
    bcm2835_pwm_set_data(PWM_CHANNEL_1, 66);

	SOAP_SOCKET m, s; /* master and slave sockets */
  	struct soap soap;
  	soap_init(&soap);
 
   	
	m = soap_bind(&soap,  "192.168.1.120", 8080, 100);
    	if (!soap_valid_socket(m)){ 
		soap_print_fault(&soap, stderr);
      		exit(-1);
    		}
    	fprintf(stderr, "Socket connection successful: master socket = %d\n", m);

	for ( ; ; ){ 
	s = soap_accept(&soap);
      	fprintf(stderr, "Socket connection successful: slave socket = %d\n", s);
      	if (!soap_valid_socket(s)){ 
		soap_print_fault(&soap, stderr);
        	exit(-1);
      	} 
      	soap_serve(&soap);
      	soap_end(&soap);
    }

bcm2835_close();

  return 0;
} 

int ns__setAuto(struct soap *soap, double a, double b, double *result){ 
	//(void)soap;
	if(a=!1){
		bcm2835_gpio_write(PIN_MotorAdelante, HIGH);
}
else{
	bcm2835_gpio_write(PIN_MotorAdelante, LOW);
}
		
	//bcm2835_gpio_write(PIN_MotorAdelante, HIGH);
	
	// wait a bit
	//bcm2835_delay(500);
	
	// turn it off
	//bcm2835_gpio_write(PIN_MotorAdelante, LOW);

// bcm2835_pwm_set_data(PWM_CHANNEL, data);
  *result = a + b;
  return SOAP_OK;
} 

