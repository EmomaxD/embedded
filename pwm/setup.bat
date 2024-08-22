@echo off
rem AVR-GCC ve AVRDUDE yolunu ayarlayın (eğer PATH değişkeninde yoksa)
set PATH=%PATH%;C:\path\to\avr-gcc\bin;C:\path\to\avrdude\bin

rem C kodunu derleyin
avr-gcc -mmcu=atmega328p -Os -DF_CPU=16000000UL -o main.elf main.c

rem ELF dosyasını HEX dosyasına dönüştürün
avr-objcopy -O ihex -R .eeprom main.elf main.hex

rem Arduino’ya yükleyin (COM4 portu)
avrdude -v -patmega328p -carduino -PCOM4 -b115200 -D -Uflash:w:main.hex:i

rem Geçici dosyaları temizleyin (isteğe bağlı)
del main.elf
del main.hex

echo İşlem tamamlandı!
pause
