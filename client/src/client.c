#include "client.h"


int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
     log_info(logger,"Hola! Soy un log\n");
	
	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

        ip=config_get_string_value(config,"IP");
		puerto=config_get_string_value(config,"PUERTO");
		valor=config_get_string_value(config,"CLAVE");
	
	log_info(logger,"%s\n",valor);


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/
	conexion = crear_conexion(ip, puerto);

    enviar_mensaje(valor,conexion);
	
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
       nuevo_logger=log_create("tp0.log","Tp_0",1,LOG_LEVEL_INFO);
        if (nuevo_logger==NULL)
		{
			system("cls");
			 printf("No se creo el logger\n");
			exit (1);
		}
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
    nuevo_config=config_create("./cliente.config");
	if (nuevo_config==NULL){
        system("cls");
		 printf("No se pudo crear  el config\n");
		exit(2);
	}
	return nuevo_config;
}

void leer_consola(t_log* logger){
  char *leido;

    while (1)
	{
		leido=readline("> ");
		 if (strcmp(leido,"")==0)
		 {
			exit(1);
		 }
		 log_info(logger,"%s\n",leido);
		 if (strcmp(leido,"end")==0)
		 {
			free(leido);
			break;
		 }
		free(leido);
	}
	
}

void paquete(int conexion)
{   
	char *leido;
    t_paquete* paquete=crear_paquete();
	  
	  while (1)
	  {
		leido=readline("> ");
		 if (strcmp(leido,"")==0)
		 {
			break;
		 }
		 
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
		free(leido);
	  }
		enviar_paquete(paquete,conexion);
        eliminar_paquete(paquete);
		
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	(logger!=NULL)? log_destroy(logger):
	(config!=NULL)? config_destroy(config):
	liberar_conexion(conexion);
}
