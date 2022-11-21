/* 
 * Definicoes gerais utilizadas pelo codigo
 */
#include <stdint.h>

typedef enum{
  t_plus = 0,
  t_minus,
  v_plus,
  v_minus,
  saida
} enumComandoUsuario;

typedef enum{
  desligado = 0,
  vidro,
  painel,
  pes
}enumSaidasAr;

/* Temperaturas definidas na escala de 0,1C */
const uint8_t T_MIN = 160;
const uint8_t T_MAX = 300;
const uint8_t T_PASSO = 5;

/* Velocidades */
const uint8_t V_MAX = 5;