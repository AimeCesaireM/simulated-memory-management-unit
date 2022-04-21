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

  // decompose the address
  uint32_t offset = sim_addr & 0xfff;
  uint32_t upper_10_bits = sim_addr & 0x3ff000;
  uint32_t lower_10_bits = sim_addr & 0xffc00000;

  uint32_t upt_index = upper_10_bits >> 22 ; //cut off the lower 22 zeros

  //test the first condition
  while (upper_pt_addr+ upt_index == 0){
    vmsim_map_fault(sim_addr); // i should try recursion if with recursion if this fails **
  }
  
  uint32_t lpt_index = lower_10_bits >> 12 ; // cut off the lower 12 bits

  vmsim_addr_t lower_pt_addr = upper_pt_addr + upt_index; //get the base address of the lpt

  while (upper_pt_addr + upt_index != 0 && lower_pt_addr + lpt_index == 0){
    vmsim_map_fault(sim_addr); //** if with recursion maybe ?
  }

  if (upper_pt_addr + upt_index != 0 && lower_pt_addr + lpt_index != 0){
    vmsim_addr_t real_page_addr = (vmsim_addr_t) lower_pt_addr + lpt_index; // the real page should be here

    uint32_t real_page_temp = (uint32_t) real_page_addr; // make a copy to not screw up things
    // real_page_temp = real_page_temp << 12 ; //make place for the offset , we have 12 zeros tailing the number
    real_page_temp = real_page_temp | 0xfff; //flip all the 12 0s at tail to 1s
    real_page_temp = real_page_temp & offset ; // copy the offset into place

    vmsim_addr_t real_address = (vmsim_addr_t) real_page_temp;

    return real_address;
  }
  
  // REPLACE THIS WITH YOUR OWN, FULL IMPLEMENTATION OF THIS FUNCTION.
  return 0;
  
}
// ==============================================================================
