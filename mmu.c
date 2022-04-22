// ==============================================================================
/**
 * mmu.c
 */
// ==============================================================================



// ==============================================================================
// INCLUDES

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "mmu.h"
#include "vmsim.h"
// ==============================================================================



// ==============================================================================
// MACROS AND GLOBALS

/** 
 * The (real) address of the upper page table.  Initialized by a call
 * to `mmu_init()`.
 */
static vmsim_addr_t upper_pt_addr = 0;
// ==============================================================================



// ==============================================================================
void
mmu_init (vmsim_addr_t new_upper_pt_addr) {

  upper_pt_addr = new_upper_pt_addr;
  
}
// ==============================================================================



// ==============================================================================
vmsim_addr_t
mmu_translate (vmsim_addr_t sim_addr) {

  printf("Virtual Address: %x \n", sim_addr); 
  // decompose the address
  uint32_t offset = sim_addr & 0xfff;
  uint32_t middle_10_bits = sim_addr & 0x3ff000;
  uint32_t upper_10_bits = sim_addr & 0xffc00000;

 
  uint32_t upt_index = sim_addr >> 22;
  upt_index = upt_index * 4;
  //  printf ("Offset: %x \n", offset);
  printf("UPT Index: %d \n", upt_index);
  //test the first condition

  while (upper_pt_addr + upt_index == 0){
    vmsim_map_fault(sim_addr);
  }
  
  uint32_t lpt_index = middle_10_bits >> 12 ; // cut off the lower 12 bits
  lpt_index = lpt_index * 4;
  printf("LPT index: %d \n", lpt_index);

  vmsim_addr_t lower_pt_addr = upper_pt_addr + upt_index; //get the base address of the lpt
  //printf("lower page table address: %x \n", lower_pt_addr);

  while (upper_pt_addr + upt_index != 0 && lower_pt_addr + lpt_index == 0){
    vmsim_map_fault(sim_addr);
  }

  //if (upper_pt_addr + upt_index != 0 && lower_pt_addr + lpt_index != 0){
    vmsim_addr_t real_page_addr = (vmsim_addr_t) lower_pt_addr + lpt_index; // the real page should be here
    //printf(" real page address: %x \n", real_page_addr);
            
    vmsim_addr_t real_address = (vmsim_addr_t) real_page_addr + offset;
    printf("real address: %x \n", real_address);  

    return real_address;
}
  
//  return 0;
  
  //}
// ==============================================================================
