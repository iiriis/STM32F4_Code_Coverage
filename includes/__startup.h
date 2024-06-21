

void Reset_Handler(void);
__weak_symbol __attribute__((alias("Default_Handler"))) void NMI_Handler(void);
__weak_symbol __attribute__((alias("Default_Handler"))) void HardFault_Handler(void);
__weak_symbol __attribute__((alias("Default_Handler"))) void MemoryManagementFault_Handler(void);
__weak_symbol __attribute__((alias("Default_Handler"))) void BusFault_Handler(void);
__weak_symbol __attribute__((alias("Default_Handler"))) void UsageFault_Handler(void);
