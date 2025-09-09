# STM32F4-Discovery — SPL (StdPeriph) WorkSpace

Bu depo, staj dönemimde **STM32F4-Discovery** kartı üzerinde **STM32 Standard Peripheral Library (SPL)** ile yaptığım örnekleri içerir.  
Çalışma alanı; saat (RCC), GPIO, EXTI, ADC/DAC, TIMER, PWM, SysTick, USART ve çeşitli uygulama örneklerinden oluşan **adım adım ilerleyen** mini projelerden meydana gelir.

> Amaç: SPL API’sini temel seviyeden başlayıp çoklu çevresim senaryolarına doğru ilerleyen, küçük ve odaklı örneklerle öğrenmek.

---

## Hızlı Başlangıç

- **Kart:** STM32F4-Discovery (STM32F407VG)
<img width="315" height="236" alt="image" src="https://github.com/user-attachments/assets/316c7d26-cbff-4d78-921a-3d3726b919fa" />

- **Kütüphane:** STM32F4 Standard Peripheral Library (SPL 9.x)  
- **IDE / Derleyici:**  
  - Atollic TrueStudio **veya**  
  - STM32CubeIDE (SPL projeleri içe aktarılabilir)  
- **Programlayıcı:** On-board ST-Link/V2  

### Derleme & Yükleme
1. İlgili klasörü IDE’ye **“Existing project”** olarak ekleyin.  
2. Hedefi `STM32F407xx` olarak doğrulayın.  
3. `system_stm32f4xx.c` ve `stm32f4xx_rcc.c` dosyalarındaki saat ayarlarının proje ile uyumlu olduğundan emin olun.  
4. Build → Programla (ST-Link).  

> **Not:** Projeler **tek tek bağımsızdır**. Her klasör kendi `main.c` ve proje ayarlarına sahiptir.

---

## Klasör Yapısı

- `REGISTER_*` : Çevresimleri **kayıt düzeyi** ile sürerek temelleri gösterir.  
- `STDPeriph_*` / `STDP_*` : Aynı işi **SPL API** ile, daha okunaklı/taşınabilir biçimde yapar.  
- `*_Ex1`, `*_Ex2` : Aynı konunun varyasyonları/ilerleyen örnekleri.  

---

## Proje Dizini (Sıralı)

### 000–010: Saat & GPIO & Buton
- **001_REGISTER_CLOCK_CONFIGURATION** – RCC saat konfigürasyonu (register).  
- **002_SYSTEM_CLOCK_CONFIG_PLL** – PLL ile sistem saat ayarı.  
- **003_REGISTER_CLOCK_CONFIGURATION_ex1/ex2** – Saat ayar varyasyonları.  
- **004_GPIO_NOT / 004_GPIO_NOT1** – GPIO toggle örnekleri.  
- **005_REGISTER_LED_BLINK** – Register ile LED blink.  
- **006_STDPeriph_LED_BLINK** – SPL ile LED blink.  
- **008_STDPeriph_BUTTON_KONTROL** – Buton okuma.  
- **009_STDPeriph_LED_BUTON** – Buton ile LED kontrolü.  
- **010_REGISTER_BUTTON_KONTROL** – Register ile buton kontrolü.  

### 011–019: EXTI ve Zamanlama
- **011_STDPeriph_Interrupt_Button** – Harici kesmeyle buton.  
- **012_STDPeriph_7segmentDisplay** – 7-segment display sürümü.  
- **014_STDPeriph_EXTI_Ex1/Ex2** – EXTI hatlarıyla örnekler.  
- **016–019_MULTI_EXTI** – Çoklu EXTI hatları örnekleri.  

### 020–035: ADC & DAC
- **022_STDPeriph_ADC** – ADC temel okuma (SPL).  
- **023_STDPeriph_ADC_Ex1** – ADC tek kanal.  
- **024_STDPeriph_ADC_DegerOku / Ex2** – Değer okuma varyasyonları.  
- **025_REGISTER_ADC** – Register ile ADC.  
- **026_REGISTER_DAC** – Register ile DAC.  
- **031_STD_ADC_8bit / 032_STD_ADC_10bit** – 8/10-bit ADC örnekleri.  
- **034_REAL_TIME_DELAY** – Gerçek zamanlı gecikme.  

### 036–046: DAC, Timer, Interrupt
- **036_STDP_DAC_1 / Ex2 / Ex3** – SPL ile DAC.  
- **040_STD_TIMER_COUNTER** – Timer counter modu.  
- **042_STD_TIMER_LED** – Timer ile LED sürme.  
- **046_STDP_TIMER_INTERRUPT** – Timer kesmesi ile periyodik görev.  

### 047–066: Sine, SysTick, PWM, USART
- **047/048_SIN_WAVE** – DAC ile sinüs dalgası üretimi.  
- **052_TIMER_INTERRUPT_Ex1** – Timer interrupt varyasyonu.  
- **053_TIMER_REGISTER** – Timer register seviyesinde.  
- **054_SYSTICK_TIMER** – SysTick ile zamanlayıcı.  
- **056_STDP_PWM** – PWM üretimi.  
- **057/058_STDP_PWM_GerilimAyar** – PWM ile duty/gerilim ayarı.  
- **059_STDP_COKLU_ADC** – Çoklu ADC senaryosu (scan/DMA).  
- **061_STDP_ADC_DAC_SIN** – ADC → DAC sinüs dönüşümü.  
- **062_LazerSensor** – ADC ile sensör okuma.  
- **063_Buzzer** – PWM ile buzzer sürümü.  
- **066_STDP_USART** – USART haberleşme.  

---

## Görseller

<img width="286" height="368" alt="image" src="https://github.com/user-attachments/assets/82731cf8-d107-44b9-ae09-28661360f860" /><img width="491" height="368" alt="image" src="https://github.com/user-attachments/assets/a0366f40-ec55-4bff-84d2-a3454adbdf23" />

<img width="487" height="365" alt="image" src="https://github.com/user-attachments/assets/2e824ac5-1025-4942-b929-7849cc9ce9d8" /><img width="338" height="365" alt="image" src="https://github.com/user-attachments/assets/7e5ccc2a-6c91-478a-a947-1d870aba1059" />

<img width="450" height="312" alt="image" src="https://github.com/user-attachments/assets/23e7ce71-40bf-4c0b-ba35-fd924615bd49" /><img width="417" height="312" alt="image" src="https://github.com/user-attachments/assets/a936dff9-3e8e-47e3-8fe5-94b61f1685ce" />

<img width="403" height="302" alt="image" src="https://github.com/user-attachments/assets/c1da4c11-72e7-48d6-9605-543a147db286" /><img width="417" height="302" alt="image" src="https://github.com/user-attachments/assets/b1e4313c-6fff-41e5-ac4f-4af6f0eb5a68" />

<img width="430" height="347" alt="image" src="https://github.com/user-attachments/assets/4248a8d5-8b4d-419e-94bc-47c3a1524098" /><img width="460" height="347" alt="image" src="https://github.com/user-attachments/assets/c17da04d-7046-439e-aa06-f796934c778c" />

<img width="368" height="276" alt="image" src="https://github.com/user-attachments/assets/09ff7114-3f79-42b5-a698-c8df7a92ee25" /><img width="377" height="276" alt="image" src="https://github.com/user-attachments/assets/cdbcf501-207e-470b-b5d8-15b3c5eb4c84" />

<img width="395" height="222" alt="image" src="https://github.com/user-attachments/assets/f819ad0f-415f-41a1-9dc1-ac39bf76982a" /><img width="366" height="222" alt="image" src="https://github.com/user-attachments/assets/1b236229-20d1-4305-87ae-abeb2166ca97" />

<img width="218" height="384" alt="image" src="https://github.com/user-attachments/assets/084bc546-235e-46d6-9431-ef19699da332" /><img width="521" height="391" alt="image" src="https://github.com/user-attachments/assets/75ed604f-5815-4f8b-9796-f975dee64bf8" />

