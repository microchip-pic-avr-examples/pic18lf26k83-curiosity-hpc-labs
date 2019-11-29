[![MCHP](https://cldup.com/U0qhLwBijF.png)](https://www.microchip.com) 
# PIC18F45Q10 Robust Button Debouncing

# Robust Debouncing with Core-Independent Peripherals (CIPs)


**Introduction:**
This Tips 'n Tricks presents two more robust and quick debouncing solutions, which equally applies to rotary encoders, buttons, switches, keypads, knobs and the like. By using an internal timer to provide customized slower clock and Configurable Logic Cells (CLCs), it is possible to filter out various kinds of button generated noise. One solution requires two CLCs per button, which on PIC18F Q10 Family devices with 8 CLCs can support debouncing of 4 buttons. This solutions works well for the demonstrated example senarios. Another solution requires three CLCs per button, which is more robust and addresses a timing corner case in the two CLCs solution. User has the option between these two solutions based on their requirements. The debouncing is performed in hardware with no required code other than setting up the timer and CLCs in MPLAB Code Configurator (MCC) in MPLAB X.

Figure below shows the logic diagram for the two-CLCs solution with two buttons supported: S2 button on HPC board and external rotary encoder connected on pin RB2.
  - [Two-CLCs Solution Logic Diagram](https://i.imgur.com/EK0Y0KQ.jpg)


**Peripherals:**
  - Timer
  - CLCs

**Hardware Requirements:**
  - Curiosity HPC w/PIC18F45Q10   
    - http://www.microchip.com/developmenttools/ProductDetails/dm164136 
    - https://www.microchip.com/wwwproducts/en/PIC18F45Q10
  - External rotary encoder (Encoder on XMEGA-E5 Xplained board is used)
    - https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/ATXMEGAE5-XPLD

**Software Prerequisites**
  - MPLAB ® X IDE v.5.10
    - http://www.microchip.com/mplab/mplab-x-ide
  - MPLAB XC8 C Compiler v.2.0
    - http://www.microchip.com/mplab/compilers

**Interface Settings:**
  - CPU: Oscillator Select: HFINTOSC - Clock Divider: 4 to set system clock at 1MHz 
  - TIMER6: Select LFINTOSC for Clock Source and 1.5ms for Timer Period
  - CLCs: configure CLC0-4 as 2-input D flip-flop with R mode and configure inputs&outputs as described in the Tips 'n Tricks
  - Pins: configure pins RA4, RA5, RA6, RA7, RB2 and RC5 in Pin Manager as described in the Tips 'n Tricks
  - Connect rotary encoder on XMEGA-E5 Xplained board to pin PB2 on HPC board
  - Connect HPC and XMEGA-E5 Xplained boards to the computer
  - Generate code by clicking generate button in MCC in MPLAB
  - Add SLEEP(); code in the main() function to set the CPU in sleep mode in order to save power consumption. This step is otpional
  - Build and program the code onto the PIC device
  - Press the S2 button on HPC board and identify the onboard LEDs D2 and D3 is toggling, indicating button debouncing is functioning
  - Rotate encoder on XMEGA-E5 Xplained board and identify the onboard LEDs D4 and D5 are toggling, indicating encoder debouncing is functioning
  

  - One can further configure CLC5 and reconfigure CLC1 in MCC to extend the two-CLCs solution to three-CLCs solution as described in the Tips 'n Tricks. Regenerate code and then build&program the device to check the three-CLCs solution.