/*
 * Dump registers for diagnostic purposes
 */

#include <registerdump.h>
#include <nrf51.h>
#include <stdio.h>

void putreg(volatile void *reg, const char *name)
{
    uint32_t *ptr= (uint32_t *)reg;
    printf("%s %08x: %08x\r\n", name, uint32_t(ptr), *ptr);
}

void dumpIrqEnables(void) {
    putreg(&NVIC->ISER, "NVIC->ISER\t");
    putreg(&NVIC->ICER, "NVIC->ICER\t");
    putreg(&NVIC->ISPR, "NVIC->ISPR\t");
    putreg(&NVIC->ICPR, "NVIC->ICPR\t");
    char nvic_ip[]= "NVIC->IP[@]\t"; 
    for (int b= 0; b<8; b++) {
        nvic_ip[9]= '0'+b;
        putreg(&NVIC->IP[b], nvic_ip);
    }

    putreg(&SCB->CPUID, "SCB->CPUID\t");
    putreg(&SCB->ICSR, "SCB->ICSR\t");
    putreg(&SCB->AIRCR, "SCB->AIRCR\t");
    putreg(&SCB->SCR, "SCB->SCR\t");
    putreg(&SCB->CCR, "SCB->CCR\t");
    putreg(&SCB->SHP[1], "SCB->SHP[1]\t");
    putreg(&SCB->SHCSR, "SCB->SHCSR\t");

    putreg(&NRF_POWER->INTENCLR, "NRF_POWER->INTENCLR\t");
    putreg(&NRF_CLOCK->INTENCLR, "NRF_CLOCK->INTENCLR\t");
    putreg(&NRF_RADIO->INTENCLR, "NRF_RADIO->INTENCLR\t");
    putreg(&NRF_UART0->INTENCLR, "NRF_UART0->INTENCLR\t");
    putreg(&NRF_SPI0->INTENCLR, "NRF_SPI0->INTENCLR\t");
    putreg(&NRF_TWI0->INTENCLR, "NRF_TWI0->INTENCLR\t");
    putreg(&NRF_SPI1->INTENCLR, "NRF_SPI1->INTENCLR\t");
    putreg(&NRF_TWI1->INTENCLR, "NRF_TWI1->INTENCLR\t");
    putreg(&NRF_SPIS1->INTENCLR, "NRF_SPIS1->INTENCLR\t");
    putreg(&NRF_SPIM1->INTENCLR, "NRF_SPIM1->INTENCLR\t");
    putreg(&NRF_GPIOTE->INTENCLR, "NRF_GPIOTE->INTENCLR\t");
    putreg(&NRF_ADC->INTENCLR, "NRF_ADC->INTENCLR\t");
    putreg(&NRF_TIMER0->INTENCLR, "NRF_TIMER0->INTENCLR\t");
    putreg(&NRF_TIMER1->INTENCLR, "NRF_TIMER1->INTENCLR\t");
    putreg(&NRF_TIMER2->INTENCLR, "NRF_TIMER2->INTENCLR\t");
    putreg(&NRF_RTC0->INTENCLR, "NRF_RTC0->INTENCLR\t");
    putreg(&NRF_TEMP->INTENCLR, "NRF_TEMP->INTENCLR\t");
    putreg(&NRF_RNG->INTENCLR, "NRF_RNG->INTENCLR\t");
    putreg(&NRF_ECB->INTENCLR, "NRF_ECB->INTENCLR\t");
    putreg(&NRF_AAR->INTENCLR, "NRF_AAR->INTENCLR\t");
    putreg(&NRF_CCM->INTENCLR, "NRF_CCM->INTENCLR\t");
    putreg(&NRF_WDT->INTENCLR, "NRF_WDT->INTENCLR\t");
    putreg(&NRF_RTC1->INTENCLR, "NRF_RTC1->INTENCLR\t");
    putreg(&NRF_QDEC->INTENCLR, "NRF_QDEC->INTENCLR\t");
    putreg(&NRF_LPCOMP->INTENCLR,"NRF_LPCOMP->INTENCLR\t");
}

void dumpClockRegisters(void)
{
    putreg(&NRF_CLOCK->TASKS_HFCLKSTART, "NRF_CLOCK->TASKS_HFCLKSTART     "); /*!< Start HFCLK clock source. */
    putreg(&NRF_CLOCK->TASKS_HFCLKSTOP, "NRF_CLOCK->TASKS_HFCLKSTOP      "); /*!< Stop HFCLK clock source. */
    putreg(&NRF_CLOCK->TASKS_LFCLKSTART, "NRF_CLOCK->TASKS_LFCLKSTART     "); /*!< Start LFCLK clock source. */
    putreg(&NRF_CLOCK->TASKS_LFCLKSTOP, "NRF_CLOCK->TASKS_LFCLKSTOP      "); /*!< Stop LFCLK clock source. */
    putreg(&NRF_CLOCK->TASKS_CAL, "NRF_CLOCK->TASKS_CAL            "); /*!< Start calibration of LFCLK RC oscillator. */
    putreg(&NRF_CLOCK->TASKS_CTSTART, "NRF_CLOCK->TASKS_CTSTART        "); /*!< Start calibration timer. */
    putreg(&NRF_CLOCK->TASKS_CTSTOP, "NRF_CLOCK->TASKS_CTSTOP         "); /*!< Stop calibration timer. */
    putreg(&NRF_CLOCK->EVENTS_HFCLKSTARTED, "NRF_CLOCK->EVENTS_HFCLKSTARTED  "); /*!< HFCLK oscillator started. */
    putreg(&NRF_CLOCK->EVENTS_LFCLKSTARTED, "NRF_CLOCK->EVENTS_LFCLKSTARTED  "); /*!< LFCLK oscillator started. */
    putreg(&NRF_CLOCK->EVENTS_DONE, "NRF_CLOCK->EVENTS_DONE          "); /*!< Calibration of LFCLK RC oscillator completed. */
    putreg(&NRF_CLOCK->EVENTS_CTTO, "NRF_CLOCK->EVENTS_CTTO          "); /*!< Calibration timer timeout. */
    putreg(&NRF_CLOCK->INTENSET, "NRF_CLOCK->INTENSET             "); /*!< Interrupt enable set register. */
    putreg(&NRF_CLOCK->INTENCLR, "NRF_CLOCK->INTENCLR             "); /*!< Interrupt enable clear register. */
    putreg(&NRF_CLOCK->HFCLKRUN, "NRF_CLOCK->HFCLKRUN             "); /*!< Task HFCLKSTART trigger status. */
    putreg(&NRF_CLOCK->HFCLKSTAT, "NRF_CLOCK->HFCLKSTAT            "); /*!< High frequency clock status. */
    putreg(&NRF_CLOCK->LFCLKRUN, "NRF_CLOCK->LFCLKRUN             "); /*!< Task LFCLKSTART triggered status. */
    putreg(&NRF_CLOCK->LFCLKSTAT, "NRF_CLOCK->LFCLKSTAT            "); /*!< Low frequency clock status. */
    putreg(&NRF_CLOCK->LFCLKSRCCOPY, "NRF_CLOCK->LFCLKSRCCOPY         "); /*!< Clock source for the LFCLK clock, set when task LKCLKSTART is triggered. */
    putreg(&NRF_CLOCK->LFCLKSRC, "NRF_CLOCK->LFCLKSRC             "); /*!< Clock source for the LFCLK clock. */
    putreg(&NRF_CLOCK->CTIV, "NRF_CLOCK->CTIV                 "); /*!< Calibration timer interval. */
    putreg(&NRF_CLOCK->XTALFREQ, "NRF_CLOCK->XTALFREQ             "); /*!< Crystal frequency. */
}

void dumpRadioRegisters(void)
{
    putreg(&NRF_RADIO->TASKS_TXEN, "NRF_RADIO->TASKS_TXEN       "); /*!< Enable radio in TX mode. */
    putreg(&NRF_RADIO->TASKS_RXEN, "NRF_RADIO->TASKS_RXEN       "); /*!< Enable radio in RX mode. */
    putreg(&NRF_RADIO->TASKS_START, "NRF_RADIO->TASKS_START      "); /*!< Start radio. */
    putreg(&NRF_RADIO->TASKS_STOP, "NRF_RADIO->TASKS_STOP       "); /*!< Stop radio. */
    putreg(&NRF_RADIO->TASKS_DISABLE, "NRF_RADIO->TASKS_DISABLE    "); /*!< Disable radio. */
    putreg(&NRF_RADIO->TASKS_RSSISTART, "NRF_RADIO->TASKS_RSSISTART  "); /*!< Start the RSSI and take one sample of the receive signal strength. */
    putreg(&NRF_RADIO->TASKS_RSSISTOP, "NRF_RADIO->TASKS_RSSISTOP   "); /*!< Stop the RSSI measurement. */
    putreg(&NRF_RADIO->TASKS_BCSTART, "NRF_RADIO->TASKS_BCSTART    "); /*!< Start the bit counter. */
    putreg(&NRF_RADIO->TASKS_BCSTOP, "NRF_RADIO->TASKS_BCSTOP     "); /*!< Stop the bit counter. */
    putreg(&NRF_RADIO->EVENTS_READY, "NRF_RADIO->EVENTS_READY     "); /*!< Ready event. */
    putreg(&NRF_RADIO->EVENTS_ADDRESS, "NRF_RADIO->EVENTS_ADDRESS   "); /*!< Address event. */
    putreg(&NRF_RADIO->EVENTS_PAYLOAD, "NRF_RADIO->EVENTS_PAYLOAD   "); /*!< Payload event. */
    putreg(&NRF_RADIO->EVENTS_END, "NRF_RADIO->EVENTS_END       "); /*!< End event. */
    putreg(&NRF_RADIO->EVENTS_DISABLED, "NRF_RADIO->EVENTS_DISABLED  "); /*!< Disable event. */
    putreg(&NRF_RADIO->EVENTS_DEVMATCH, "NRF_RADIO->EVENTS_DEVMATCH  "); /*!< A device address match occurred on the last received packet. */
    putreg(&NRF_RADIO->EVENTS_DEVMISS, "NRF_RADIO->EVENTS_DEVMISS   "); /*!< No device address match occurred on the last received packet. */
    putreg(&NRF_RADIO->EVENTS_RSSIEND, "NRF_RADIO->EVENTS_RSSIEND   "); /*!< Sampling of the receive signal strength complete. A new RSSI sample is ready for readout at the RSSISAMPLE register. */
    putreg(&NRF_RADIO->EVENTS_BCMATCH, "NRF_RADIO->EVENTS_BCMATCH   "); /*!< Bit counter reached bit count value specified in BCC register.*/
    putreg(&NRF_RADIO->SHORTS, "NRF_RADIO->SHORTS           "); /*!< Shortcuts for the radio. */
    putreg(&NRF_RADIO->INTENSET, "NRF_RADIO->INTENSET         "); /*!< Interrupt enable set register.*/
    putreg(&NRF_RADIO->INTENCLR, "NRF_RADIO->INTENCLR         "); /*!< Interrupt enable clear register. */
    putreg(&NRF_RADIO->CRCSTATUS, "NRF_RADIO->CRCSTATUS        "); /*!< CRC status of received packet. */
    putreg(&NRF_RADIO->RXMATCH, "NRF_RADIO->RXMATCH          "); /*!< Received address. */
    putreg(&NRF_RADIO->RXCRC, "NRF_RADIO->RXCRC            "); /*!< Received CRC. */
    putreg(&NRF_RADIO->DAI, "NRF_RADIO->DAI              "); /*!< Device address match index. */
    putreg(&NRF_RADIO->PACKETPTR, "NRF_RADIO->PACKETPTR        "); /*!< Packet pointer. Decision point: START task. */
    putreg(&NRF_RADIO->FREQUENCY, "NRF_RADIO->FREQUENCY        "); /*!< Frequency. */
    putreg(&NRF_RADIO->TXPOWER, "NRF_RADIO->TXPOWER          "); /*!< Output power. */
    putreg(&NRF_RADIO->MODE, "NRF_RADIO->MODE             "); /*!< Data rate and modulation. */
    putreg(&NRF_RADIO->PCNF0, "NRF_RADIO->PCNF0            "); /*!< Packet configuration 0. */
    putreg(&NRF_RADIO->PCNF1, "NRF_RADIO->PCNF1            "); /*!< Packet configuration 1. */
    putreg(&NRF_RADIO->BASE0, "NRF_RADIO->BASE0            "); /*!< Radio base address 0. Decision point: START task. */
    putreg(&NRF_RADIO->BASE1, "NRF_RADIO->BASE1            "); /*!< Radio base address 1. Decision point: START task. */
    putreg(&NRF_RADIO->PREFIX0, "NRF_RADIO->PREFIX0          "); /*!< Prefixes bytes for logical addresses 0 to 3. */
    putreg(&NRF_RADIO->PREFIX1, "NRF_RADIO->PREFIX1          "); /*!< Prefixes bytes for logical addresses 4 to 7. */
    putreg(&NRF_RADIO->TXADDRESS, "NRF_RADIO->TXADDRESS        "); /*!< Transmit address select. */
    putreg(&NRF_RADIO->RXADDRESSES, "NRF_RADIO->RXADDRESSES      "); /*!< Receive address select. */
    putreg(&NRF_RADIO->CRCCNF, "NRF_RADIO->CRCCNF           "); /*!< CRC configuration. */
    putreg(&NRF_RADIO->CRCPOLY, "NRF_RADIO->CRCPOLY          "); /*!< CRC polynomial. */
    putreg(&NRF_RADIO->CRCINIT, "NRF_RADIO->CRCINIT          "); /*!< CRC initial value. */
    putreg(&NRF_RADIO->TEST, "NRF_RADIO->TEST             "); /*!< Test features enable register.*/
    putreg(&NRF_RADIO->TIFS, "NRF_RADIO->TIFS             "); /*!< Inter Frame Spacing in microseconds. */
    putreg(&NRF_RADIO->RSSISAMPLE, "NRF_RADIO->RSSISAMPLE       "); /*!< RSSI sample. */
    putreg(&NRF_RADIO->STATE, "NRF_RADIO->STATE            "); /*!< Current radio state. */
    putreg(&NRF_RADIO->DATAWHITEIV, "NRF_RADIO->DATAWHITEIV      "); /*!< Data whitening initial value. */
    putreg(&NRF_RADIO->BCC, "NRF_RADIO->BCC              "); /*!< Bit counter compare. */
    char radio_dab[]= "NRF_RADIO->DAB[@]           ";
    for (int b= 0; b<8; b++) {
        radio_dab[15]= '0'+b;
        putreg(&NRF_RADIO->DAB[b], radio_dab); /*!< Device address base segment. */
    }
    char radio_dap[]= "NRF_RADIO->DAP[@]           ";
    for (int b= 0; b<8; b++) {
        radio_dap[15]= '0'+b;
        putreg(&NRF_RADIO->DAP[b], radio_dap); /*!< Device address prefix. */
    }
    putreg(&NRF_RADIO->DACNF, "NRF_RADIO->DACNF            "); /*!< Device address match configuration. */
    putreg(&NRF_RADIO->OVERRIDE0, "NRF_RADIO->OVERRIDE0        "); /*!< Trim value override register 0. */
    putreg(&NRF_RADIO->OVERRIDE1, "NRF_RADIO->OVERRIDE1        "); /*!< Trim value override register 1. */
    putreg(&NRF_RADIO->OVERRIDE2, "NRF_RADIO->OVERRIDE2        "); /*!< Trim value override register 2. */
    putreg(&NRF_RADIO->OVERRIDE3, "NRF_RADIO->OVERRIDE3        "); /*!< Trim value override register 3. */
    putreg(&NRF_RADIO->OVERRIDE4, "NRF_RADIO->OVERRIDE4        "); /*!< Trim value override register 4. */
    putreg(&NRF_RADIO->POWER, "NRF_RADIO->POWER            "); /*!< Peripheral power control. */
}
