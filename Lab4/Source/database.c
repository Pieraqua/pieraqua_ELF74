/**
*       @file database.c
*/
#include "database.h"


#if BYTEVAL_NUM > 0
uint8_t bytevals[BYTEVAL_NUM];
#endif

#if SHORTVAL_NUM > 0
uint8_t shortvals[SHORTAL_NUM];
#endif

#if LONGVAL_NUM > 0
uint32_t longvals[LONGVAL_NUM];
#endif

/** @brief Inicializacao de valores-padrao na base de dados */
void vDB_Init()
{
  uint32_t size = BYTEVAL_NUM;
#if SHORTVAL_NUM > 0
  size = size < SHORTVAL_NUM ? SHORTVAL_NUM : size;
#endif
#if LONGVAL_NUM > 0
  size = size < LONGVAL_NUM ? LONGVAL_NUM : size;
#endif
  
  while(size)
  {
    size--;
#if BYTEVAL_NUM > 0
    if(size < BYTEVAL_NUM)
    {
      bytevals[size] = 0;
    }
#endif
#if SHORTVAL_NUM > 0
    if(size < SHORTVAL_NUM)
    {
      shortvals[size] = 0;
    }
#endif
#if LONGVAL_NUM > 0
    if(size < LONGVAL_NUM)
    {
      longvals[size] = 0;
    }
#endif
  }
  
}

/** @brief Retorna o valor de byte referenciado por @p addr, ou 0 caso nao exista. */
uint8_t ui8DB_getByteVal(enBytevals addr)
{
#if BYTEVAL_NUM > 0
  if(addr >= BYTEVAL_NUM)
    return 0;
  return bytevals[addr];
#else
  return 0;
#endif
}

/** @brief Retorna o valor de short referenciado por @p addr, ou 0 caso nao exista. */
uint16_t ui16DB_getShortVal(enShortvals addr)
{
#if SHORTVAL_NUM > 0
  if(addr >= SHORTVAL_NUM)
    return 0;
  return shortvals[addr];
#else
  return 0;
#endif
}

/** @brief Seta o valor de long referenciado por @p addr, ou 0 caso nao exista. */
uint32_t ui32DB_getLongVal(enLongvals addr)
{
#if LONGVAL_NUM > 0
  if(addr >= LONGVAL_NUM)
    return 0;
  
  return longvals[addr];
#else
  return 0;
#endif
}

/** @brief Seta o valor de byte referenciado por @p addr para @p val . */
void vDB_setByteVal(enBytevals addr, uint8_t val)
{
  
#if BYTEVAL_NUM > 0
  if(addr >= BYTEVAL_NUM)
    return;
  bytevals[addr] = val;
#endif
}

/** @brief Seta o valor de short referenciado por @p addr para @p val . */
void vDB_setShortVal(enShortvals addr, uint16_t val)
{
#if SHORTVAL_NUM > 0
  if(addr >= SHORTVAL_NUM)
    return;
  shortvals[addr] = val;
#endif
}

/** @brief Seta o valor de long referenciado por @p addr para @p val . */
void vDB_setLongVal(enLongvals addr, uint32_t val)
{
  
#if LONGVAL_NUM > 0
  if(addr >= LONGVAL_NUM)
    return;
  
  longvals[addr] = val;
#endif
}
