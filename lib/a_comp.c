#include "a_comp.h"

uint8_t A_COMP_read(){
 wait_for_zero(ACSR, ACI);
 return !!(ACSR & (1 << ACO));
}
