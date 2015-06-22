#include <exception>
#include <stdio.h>
#include <iostream>
#include <logging.hpp>

using std::exception;

/**
 * Dataflow Exception Constructor
 */
DataFlowException::DataFlowException(const char *type, const char *error)
{
	sprintf(this->msg, "%s", error);
}

FILE * Logger::logger = NULL;

/**
 * Logs event to log file but first open file if not already open
 */
void Logger::LogEvent(const char *event)
{
	if(logger == NULL){
		logger = fopen("log/log_file", "w");
        	if(logger == NULL){
			logger = fopen("../log/log_file", "w");
        		if(logger == NULL){
                		DataFlowException except("Logger", "Cannot lock log file!");
                		throw except;
			}
        	}
	}	
        fprintf(logger, "%s\n", event);
//	fprintf(stderr,"%s\n", event);
}

/**
 * Closes File when done
 */
void Logger::Finalize()
{
	fclose(logger);
//	printf("Finalizing Log");
}
