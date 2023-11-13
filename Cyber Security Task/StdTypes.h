/*
 * StdTypes.h
 *
 * Created: 12/06/2023 00:08:02
 *  Author: OMAR
 */ 


#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char u8;
typedef signed char s8;
typedef  char c8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned long u32;
typedef signed long s32;

typedef enum{
	FALSE,
	TRUE
}Bool_t;

typedef enum{
	OK,
	NOK,
	NULL_PTR,
	OUTOFRANGE
}Error_t;

#define  NULLPTR  ((void*)0)

#define  MAX_U8  (u8(255))
#define  MIN_U8  (u8(0))

#define  MAX_S8  (s8(127))
#define  MIN_S8  (s8(-128))
#define  ZERO_S8  (s8(0))



#endif /* STDTYPES_H_ */