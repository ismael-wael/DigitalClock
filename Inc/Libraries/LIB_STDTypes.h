#ifndef LIBRARIES_LIB_STDTYPES_H_
#define LIBRARIES_LIB_STDTYPES_H_

typedef unsigned char u8;
typedef unsigned char * pu8;

typedef signed char s8;
typedef signed char * ps8;

typedef unsigned int u16;
typedef unsigned int * pu16;

typedef signed int s16;
typedef signed int * ps16;

typedef signed long int s32;
typedef signed long int * ps32;

typedef unsigned long int u32;
typedef unsigned long int * pu32;

typedef unsigned long long int u64;
typedef unsigned long long int * pu64;

typedef signed long long int s64;
typedef signed long long int * ps64;

#define LSTY_NULL ((void*)0)

typedef enum{
	LSTY_EXECUTED_SUCCESSFULLY = 0,
	LSTY_OUT_OF_RANGE = 1,
	LSTY_NULL_POINTER = 2,
	LSTY_READ_ERROR = 3,
	LSTY_WRITE_ERROR = 4,
	LSTY_NOK = 5,
	LSTY_TIME_OUT = 6
} tenumFncErrorState ;

typedef enum{
	False,
	True
}Bool_t;

typedef enum{
	Off,
	On
}ToggleState_t;

typedef struct{
	u8 u8Second;
	u8 u8Minute;
	u8 u8Hour;
}Time_t ;

typedef struct{
	u8 u8Day;
	u8 u8Month;
	u8 u8Year;
}Date_t;

typedef struct{
	Date_t AlarmDate;

	Time_t AlarmTime;
}Alarm_t;

#endif



