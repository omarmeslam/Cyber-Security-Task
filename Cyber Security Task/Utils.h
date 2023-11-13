/*
 * Utils.h
 *
 * Created: 12/06/2023 00:09:09
 *  Author: OMAR
 */ 


#ifndef UTILS_H_
#define UTILS_H_


#define READ_BIT(reg, bit) ((reg>>bit)&1)
#define SET_BIT(reg, bit) (reg=reg|(1<<bit))
#define CLR_BIT(reg, bit) (reg=reg&~(1<<bit))
#define TOG_BIT(reg, bit) (reg=reg^(1<<bit))


#endif /* UTILS_H_ */