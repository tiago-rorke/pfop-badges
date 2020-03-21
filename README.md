# Badges from other Planets

I made these supercapacitor powered badges for [Nowhere 2019](https://www.goingnowhere.org/), a regional burn near Zaragoza, Spain, for our fledgling barrio "People from Other Planets"

I wanted to try to use supercapacitors to avoid consuming hundreds of non-rechargeable coin cell batteries whilst keeping the design as simple as possible. Because 5V supercaps are considerably more expensive, I've used a pair of 2.5V caps in series, with a 2.5V zener across each cap to prevent overcharging.  Not sure of the safety of this, the small amount of the use these boards have had so far haven't led to any explosions, but none-the-less *use this at your own risk!*

I settled on a pair of 4.7F caps in series as a balance between cost/size/capacity, which for these two example sketches seem to provide around an hour of interaction after about 1min of charging.

We also disassembled a bunch of old laptop batteries, removed any good cells and put them into [empty powerbanks](https://www.aliexpress.com/item/32966395604.html) to provide charging units for the badges, and to use as power sources for other activities we did at the burn in our desert makerspace :).


## BOM

| | | qty |
|---|---|---|
| [capacitors 4.7F](https://pt.farnell.com/samxon/dre475s0eg20rrdap/cap-4-7f-2-5v-double-layer-radial/dp/2800103) | 2 |
| [attiny45](https://pt.mouser.com/ProductDetail/Microchip-Technology-Atmel/ATTINY45-20XU?qs=sGAEpiMZZMvqv2n3s2xjsQTu%2F4bUyWdjf4Rc8T7jfeQ%3D) | 1 |
| [white leds](https://www.tme.eu/pt/en/details/ll-r3014w-w5m-q10/smd-white-leds/lucky-light/) | 3 |
| [red led](https://www.tme.eu/pt/en/details/ll-s172sc-2s/smd-colour-leds/lucky-light/) | 1 |
| [green led](https://www.tme.eu/pt/en/details/el17-215sygc_53/smd-colour-leds/everlight/) | 1 |
| [3.3v regulator](https://www.tme.eu/pt/en/details/ap7313-33srg-7/ldo-unregulated-voltage-regulators/diodes-incorporated/) | 1 |
| [2.7v zener](https://www.tme.eu/pt/en/details/tzmb2v7-gs08/smd-zener-diodes/vishay/) | 2 |
| [5.1v zener](https://www.tme.eu/pt/en/details/bzt55c5v1-gs08/smd-zener-diodes/vishay/) | 1 |
| [2n7000 mosfet](https://www.tme.eu/pt/en/details/2n7002lt1g/smd-n-channel-transistors/on-semiconductor/) | 1 |
| [resistor power 5.6R 1W](https://www.tme.eu/pt/en/details/smd2512-5r6/2512-smd-resistors/royal-ohm/25121wj056jt4e/) | 1 |
| [resistor led 100R](https://www.tme.eu/pt/en/details/rc0805fr-07100r/0805-smd-resistors/yageo/rc0805fr-07100rl/) | 5 |
| [resistor 10k](https://www.tme.eu/pt/en/details/smd0805-10k-1%25/0805-smd-resistors/royal-ohm/0805s8f1002t5e/) | 1 |
| *touch version* | | |
| [resistor 2.2M](https://www.tme.eu/pt/en/details/smd0805-2m2/0805-smd-resistors/royal-ohm/0805s8j0225t5e/) | 1 |
| *sound version* | | |
| [electret microphone](https://www.aliexpress.com/item/10pcs-bag-4-5-2-2mm-condenser-electret-microphone-pickup-52DB/32262612470.html?spm=2114.search0104.3.2.36823c86ZRhB5p&ws_ab_test=searchweb0_0,searchweb201602_7_10065_10068_319_10059_10884_317_10887_10696_321_322_10084_453_10083_454_10103_10618_10304_10307_10820_10301_10821_537_536,searchweb201603_52,ppcSwitch_0&algo_expid=e5ac956f-4788-4c7e-8c49-3e065ae08252-0&algo_pvid=e5ac956f-4788-4c7e-8c49-3e065ae08252) | 1 |
| [bc847 transistor](https://www.tme.eu/pt/en/details/bc847be6327/npn-smd-transistors/infineon-technologies/) | 1 |
| [resistor 10k](https://www.tme.eu/pt/en/details/smd0805-10k-1%25/0805-smd-resistors/royal-ohm/0805s8f1002t5e/) | 1 |
| [resistor 100k](https://www.tme.eu/pt/en/details/crcw0805100kfktabc/0805-smd-resistors/vishay/) | 1 |
| [cap 0.1uF](https://www.tme.eu/pt/en/details/cc0805krx7r9104/0805-mlcc-smd-capacitors/yageo/cc0805krx7r9bb104/) | 1 |