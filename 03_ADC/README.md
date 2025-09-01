# 1. What is ADC

- In microcontrollers, an ADC (Analog-to-Digital Converter) is an important component that helps convert analog signals from the external world (for example, signals from sensors) into digital signals that the microcontroller can process.

## 1.1. Resolution

Resolution is the **number of bits** the ADC uses to represent the
measured voltage.\
- Higher resolution → more precise measurements.

**Number of quantization steps:**

    Steps = 2^Resolution - 1

**Example:**

| Resolution | Steps | Voltage per step (Vref=3.3V) |
| ---------- | ----- | ---------------------------- |
| 8-bit      | 256   | 3.3 / 255 ≈ 0.0129 V         |
| 10-bit     | 1024  | 3.3 / 1023 ≈ 0.0032 V        |
| 12-bit     | 4096  | 3.3 / 4095 ≈ 0.0008 V        |

------------------------------------------------------------------------

## 1.2. Reference Voltage (Vref)

Vref is the **maximum voltage the ADC can measure**.\
- If the input voltage exceeds Vref → ADC reads its maximum value.\
- Typical Vref values are **3.3V or 5V**, depending on the MCU.

**Voltage calculation formula:**

    Vin = (ADC_Value / (2^Resolution - 1)) * Vref

**Example:**\
- 12-bit ADC (4096 levels), Vref = 3.3V\
- ADC value = 2047

    Vin = (2047 / 4095) * 3.3 ≈ 1.65V

------------------------------------------------------------------------

## 1.3. Sampling Rate

Sampling rate is the **number of times per second** the ADC samples the
input signal (Samples Per Second -- SPS).

-   **High sampling rate** → captures fast-changing signals (e.g.,
    audio, vibration).\
-   **Low sampling rate** → fine for slow signals (e.g., temperature).

**Nyquist rule:**\
Sampling rate must be **at least twice the highest frequency** of the
signal to avoid distortion.

**Examples:**\
- Human voice (\~20 kHz) → **≥40 kSPS**.\
- Temperature sensor (slow changes) → **1--10 SPS** is enough.

------------------------------------------------------------------------

# 2. Example ADC with STM

## 2.1. Hardware connection

| Potentionmeter | Function       | STM32 Pin  |
|---------|-----------------|-------------------|
| VSS     | GND             | GND               |
| VDD     | +3.3V           | 3.3V                |
| Output    | Output voltage        | PA0 |

## 2.2. Output

turn maximum

<img width="328" height="80" alt="image" src="https://github.com/user-attachments/assets/69866356-7a71-4f5c-b3bf-bc486c16c31a" />

turn minimum 

<img width="340" height="81" alt="image" src="https://github.com/user-attachments/assets/541939ea-42e2-47de-a266-d62cab33b419" />



