/**
*       @file database.h
*/
#include <stdint.h>

typedef enum{
  
  BYTEVAL_NUM
}enBytevals;

typedef enum{
  
  SHORTVAL_NUM
}enShortvals;

typedef enum{
  
  LONGVAL_NUM
}enLongvals;

typedef enum{
  
  STRINGVAL_NUM
}enStringvals;

/** @brief Inicializacao de valores-padrao na base de dados */
void vDB_Init();

/** @brief Retorna o valor de byte referenciado por @p addr, ou 0 caso nao exista. */
uint8_t ui8DB_getByteVal(enBytevals addr);

/** @brief Retorna o valor de short referenciado por @p addr, ou 0 caso nao exista. */
uint16_t ui16DB_getShortVal(enShortvals addr);

/** @brief Retorna o valor de long referenciado por @p addr, ou 0 caso nao exista. */
uint32_t ui32DB_getLongVal(enLongvals addr);

/** @brief Seta o valor de byte referenciado por @p addr para @p val . */
void vDB_setByteVal(enBytevals addr, uint8_t val);

/** @brief Seta o valor de short referenciado por @p addr para @p val . */
void vDB_setShortVal(enShortvals addr, uint16_t val);

/** @brief Seta o valor de long referenciado por @p addr para @p val . */
void vDB_setLongVal(enLongvals addr, uint32_t val);
