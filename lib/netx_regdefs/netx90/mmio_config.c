#include "mmio_config.h"

static NX90_ASIC_CTRL_AREA_T* s_ptAsicCtrl = (NX90_ASIC_CTRL_AREA_T*) Addr_NX90_asic_ctrl;
static NX90_MMIO_CTRL_AREA_T* s_ptMmioCtrl = (NX90_MMIO_CTRL_AREA_T*) Addr_NX90_mmio_ctrl;


static MMIO_CONFIG_T s_atMmioConfig[] =
{
  /* MMIO No | MMIO Function              |  Invert in  | Invert out   |                                        */
  {  4,        NX90_MMIO_SEL_GPIO0,            0,           0},                /* (LED0) <=> MMIO04 <=> GPIO0  */
  {  5,        NX90_MMIO_SEL_GPIO1,            0,           0},                /* (LED1) <=> MMIO05 <=> GPIO1  */
  {  6,        NX90_MMIO_SEL_GPIO2,            0,           0},                /* (LED2) <=> MMIO06 <=> GPIO2  */
  {  7,        NX90_MMIO_SEL_GPIO3,            0,           0},                /* (LED3) <=> MMIO07 <=> GPIO3  */
};



/**************************************************************************************
 function:    mmio_config_netx90_app
 description: Configured the MMIO pad with the Multiplexing Matrix unit inside netX90 app.

 global:      none
 input:       none

 output:      none
 return:      none
**************************************************************************************/
void mmio_config_netx90_app( void )
{
  int iIdx;

  /* Configure MMIO pin multiplexer */
  for( iIdx = 0; iIdx < sizeof( s_atMmioConfig ) / sizeof( s_atMmioConfig[0] ); iIdx++ )
  {
    // read access key, write back access key
    s_ptAsicCtrl->ulAsic_ctrl_access_key = s_ptAsicCtrl->ulAsic_ctrl_access_key;

    s_ptMmioCtrl->aulMmio_cfg[s_atMmioConfig[iIdx].bMmio] = s_atMmioConfig[iIdx].bFunction <<  SRT_NX90_mmio0_cfg_mmio_sel
                                                |( ( s_atMmioConfig[iIdx].fInvertIn  ) ? MSK_NX90_mmio0_cfg_mmio_out_inv : 0)
                                                |( ( s_atMmioConfig[iIdx].fInvertOut ) ? MSK_NX90_mmio0_cfg_mmio_in_inv  : 0);
  }

} /* mmio_config_netx10 */
