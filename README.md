# Tic-Tac-Toe

**A project series hosted by Project in a Box at UCSD**
> Workshop documentation [Tic-Tac-Toe Guide](https://docs.google.com/document/d/1u_CGRj01X6Ycehi84Y9_JdpaqWEYwmZDjyTEvfT5QpA/edit?usp=sharing)<br />
> More about [Project in a Box](https://pibucsd.org/)

## Overview
This workshop is oriented to assembling a handheld Tic-Tac-Toe board with surface mount devices (SMD) and reflow soldering.

## BOM

| Component                    | Vendor                                                                                                     | Quantity   |
| ---------------------------- | ---------------------------------------------------------------------------------------------------------- | ---------- |
| NeoPixel Reverse Mount LEDs  | [Digikey](https://www.digikey.com/en/products/detail/adafruit-industries-llc/4960/14302512)                | 9          |
| ATMEGA328P-AUR              | [Digikey](https://www.digikey.com/en/products/detail/microchip-technology/ATMEGA328P-AUR/2357086)         | 1          |
| Tactile SMD Switch           | [Digikey](https://www.digikey.com/en/products/detail/te-connectivity-alcoswitch-switches/FSMSMTR/529671)   | 10         | 
| 5V-Regulator NCP1117ST50T3G  | [Digikey](https://www.digikey.com/en/products/detail/onsemi/NCP1117ST50T3G/1967217?utm_adgroup=Integrated%20Circuits%20%28ics%29&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Supplier_onsemi&utm_term=&utm_content=Integrated%20Circuits%20%28ics%29&gclid=Cj0KCQiAlMCOBhCZARIsANLid6Y771XCwKb85bAQFjVsh4KLFg09zcmp8NNUzVosYromvapvGWj7TFYaAqMzEALw_wcB)                                         | 1          | 
| Male Header (2x3-pins)       | [Digikey](https://www.digikey.com/en/products/detail/sullins-connector-solutions/PREC003DAAN-RC/2774891)   | 1          |
| DC Power Jack Socket         | [Digikey](https://www.digikey.com/en/products/detail/cui-devices/PJ-102AH/408448)                          | 1          |
| 330Ω SMD Resistor            | [Digikey](https://www.digikey.com/en/products/detail/yageo/RC1206FR-07330RL/731769?utm_adgroup=Yageo&utm_source=google&utm_medium=cpc&utm_campaign=Smart%20Shopping_Supplier_Yageo&utm_term=&utm_content=Yageo&gclid=Cj0KCQiAlMCOBhCZARIsANLid6Z2svdxXZcCLMl1CfXB-2cxl0jIykvjQrsu_GYfRR0vX5eyD9WpRuYaAu_oEALw_wcB)                                         | 1          |
| 10kΩ SMD Resistor            | [Digikey](https://www.digikey.com/en/products/detail/bourns-inc/CR0805-FX-1002ELF/3592928)                 | 1          |
| 0.1uF Ceramic SMD Capacitor  | [Digikey](https://www.digikey.com/en/products/detail/kyocera-avx/08055F104K4T2A/1024871?s=N4IgTCBcDaICwHYAcBaAzANgIxxVlAcgCIgC6AvkA)                                                                                                | 4          |
| 4.7uF Ceramic SMD Capacitor  | [Digikey](https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL21A475KAQNNNE/3886902)    | 1          |
| 10uF Tantalum SMD Capacitor  | [Digikey](https://www.digikey.com/en/products/detail/kyocera-avx/TAJR106M006RNJ/808827?utm_adgroup=Capacitors&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Supplier_AVX%20Corporation_8081_Co-op&utm_term=&utm_content=Capacitors&gclid=Cj0KCQiAlMCOBhCZARIsANLid6bJbctGY0qeTmGLRI9MiFk71J5VgDx9M5K57QbWr1aYRBVTJ_qByIAaAsGTEALw_wcB)                                         | 2          |
| 22pF Ceramic SMD Capacitor  | [Digikey](https://www.digikey.com/en/products/detail/kemet/C0805C220J5GACTU/411388)    | 2          |
| 16MHz SMD Cystal  | [Digikey](https://www.digikey.com/en/products/detail/ecs-inc/ECS-160-12-33-AGN-TR/9648827)    | 1          |
| TicTacToe PCB  | [JLCPCB](https://jlcpcb.com/)    | 1          |