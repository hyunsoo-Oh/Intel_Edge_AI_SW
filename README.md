# Intel-Edge-AI-SW
 
 기간 : 2025-02-12 ~ 2025-08-29

**임베디드 시스템, IoT, 실시간 제어, FreeRTOS, 센서 통신, Edge AI 등을 기반으로 한 프로젝트 중심 실습 과정**

### 선풍기 프로젝트

 기간 : 2025-02-21 ~ 2025-02-24

 개요 : ATmega128을 활용하여 버튼 입력에 따라 LED 시각화와 팬 속도를 제어하는 소형 선풍기 구현

**ATmega128 + Button, Bar LED, 4 Digit 7 Segment, DC Fan을 활용**

#### 주요 구성 요소
- MCU: ATmega128
- Button: 모드/속도 전환용 입력 (GPIO IN)
- Bar LED: 풍속 표시용 (GPIO OUT)
- 4 Digit 7 Segment: 현재 풍속 단계 표시 (GPIO OUT)
- DC Fan: PWM 제어

임베디드 PWM 제어 및 GPIO 출력의 기본 이해

실시간 입력 → 시각화 → 출력 제어 흐름 완성 경험

### 엘리베이터 프로젝트

 기간 : 2025-03-28 ~ 2025-04-4

 개요 : 실제 엘리베이터처럼 작동하는 상태 기반 시스템 구현. 여러 층 버튼 입력에 따라 적절한 층에 정지하도록 Step 모터 제어
 
**Nucleo F411RE + Step motor, RFID, Photo Interrupt, I2C LCD, Button을 활용**

#### 주요 구성 요소
- MCU: STM32F411RE (Nucleo Board)
- Step Motor: 층 이동 제어 (PWM + FSM)
- RFID Reader: 사용자 인증 (SPI)
- Photo Interrupt Sensor: 도착 감지 (EXTI)
- I2C LCD: 층 수 및 상태 표시
- Button: 층 호출 버튼

FSM 기반 상태 관리 구조 설계

센서 및 통신 인터페이스 통합 경험 (GPIO + SPI + I2C + EXTI)

### 선박 관리 프로젝트

 기간 : 2025-04-08 ~ 2025-05-08

 개요 : STM32 + Raspberry Pi 간 Bluetooth 통신 기반 센서 데이터 수집 및 시각화 시스템

#### Nucleo F411RE <- Bluetooth -> Raspberry Pi를 활용

#### 하드웨어 구성
- MCU: STM32F411RE
- 센서: DHT11 (온습도), Flame Sensor (화재 감지), Water Level Sensor (수위), Humidity Sensor
- 통신: HC-05 (Bluetooth SPP)
- 서버: Raspberry Pi 4 + MariaDB + PyQt5 GUI

임베디드-서버 통신 구조 설계 및 실시간 데이터 수집/시각화 경험

데이터베이스 연동을 통한 IoT 시스템 전체 흐름 구현

### RC카 프로젝트

 기간 : 2025-05-09 ~ 2025-05-21

 개요 : 장애물 회피 및 Bluetooth 제어 가능한 스마트 RC카 구현
 Bare-Metal로 초기 개발 후 FreeRTOS로 멀티태스킹 구조 전환

**Nucleo F411RE + L298N, HC-SR04 3개, HC-05**

- MCU: STM32F411RE (Nucleo)
- 모터 구동: L298N 모듈 (PWM 제어)
- 초음파 센서: HC-SR04 3개 (Input Capture)
- Bluetooth: HC-05 (UART)

PWM + 방향제어로 정밀한 모터 제어

TIM Input Capture + NVIC 인터럽트를 이용한 거리 측정

FreeRTOS 기반 Task 분리

센서 값에 따른 회피 알고리즘 (좌우 비교 + 거리 기반 제어)