#pragma once

#define LOG_WAIT_LOADING_RIFT "loading rift"
#define LOG_DONE_LOADED_RIFT "rift loaded"
#define LOG_WAIT_DESTROYING_RIFT "destroying rift"

#define LOG_FAIL_OPENNING_LOGILE "unable to open the log file"

#define LOG_WAIT_MEMORY_READ "reading memory"
#define LOG_DONE_MEMORY_READ "memory read at:"
#define LOG_FAIL_MEMORY_READ "failed to read at:"

#define LOG_WAIT_MEMORY_WRITE "writing memory"
#define LOG_DONE_MEMORY_WRITE "memory wrote at:"
#define LOG_FAIL_MEMORY_WRITE "failed to write at:"

#define LOG_WAIT_HANDLING "handling process"
#define LOG_DONE_HANDLING "handled process:"
#define LOG_FAIL_HANDLING "failed to open process:"

#define LOG_WAIT_UNHANDLE "unhandling process"
#define LOG_DONE_UNHANDLE "unhandled process:"
#define LOG_FAIL_UNHANDLE "failed to unhandle process:"

#define LOG_WAIT_SEARCH_WINDOW "searching window:"
#define LOG_DONE_SEARCH_WINDOW "window found:"
#define LOG_FAIL_SEARCH_WINDOW "window not found:"

#define LOG_WAIT_GET_PROCESS "getting process:"
#define LOG_DONE_GET_PROCESS "process found:"
#define LOG_FAIL_GET_PROCESS "process not found:"

#define LOG_WAIT_ENUMERATE_MODULES "enumerating modules from process:"
#define LOG_DONE_ENUMERATE_MODULES "modules enumerated from process:"
#define LOG_FAIL_ENUMERATE_MODULES "fail to enumerate process modules:"

#define LOG_MEMORY_BASE_ADDRESS "base address of the process:"
#define LOG_FAIL_BASE_ADDRESS "fail to get module base name"