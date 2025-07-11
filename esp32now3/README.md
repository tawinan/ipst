# โปรเจกต์: ESP-NOW - ควบคุม LED ด้วยปุ่มกด (หนึ่งผู้ส่ง, หลายผู้รับ)

โปรเจกต์นี้สาธิตการใช้ ESP-NOW เพื่อควบคุม LED บนบอร์ดผู้รับหลายตัวด้วยปุ่มกดจากบอร์ดผู้ส่งเพียงตัวเดียว

- **`esp_now_toggle_sender`**: โค้ดสำหรับบอร์ดผู้ส่ง ซึ่งจะมีปุ่มกดที่ GPIO0
- **`esp_now_toggle_receiver`**: โค้ดสำหรับบอร์ดผู้รับ ซึ่งจะสลับสถานะ LED ที่ GPIO0 เมื่อได้รับสัญญาณจากผู้ส่ง

## การทำงาน

เมื่อผู้ส่งกดปุ่ม (Toggle Switch) สัญญาณจะถูกส่งผ่าน ESP-NOW ไปยังผู้รับทุกตัว ผู้รับแต่ละตัวจะรับสัญญาณและสลับสถานะของ LED ที่เชื่อมต่อกับ GPIO0 LED จะเริ่มต้นที่สถานะสว่าง (ON)

## ข้อควรระวัง: การใช้ GPIO0

GPIO0 บน ESP32-C3 เป็นขา Boot Mode หากคุณเชื่อมต่อสวิตช์หรือ LED เข้ากับ GPIO0 คุณอาจต้องถอดการเชื่อมต่อออกชั่วคราวเมื่ออัปโหลดโค้ด เพื่อให้บอร์ดเข้าสู่โหมด Bootloader ได้อย่างถูกต้อง

## ขั้นตอนการตั้งค่า

### 1. หา MAC Address ของบอร์ดผู้รับ (Receivers)

1.  อัปโหลดโค้ดจากโปรเจกต์ `esp32c3mac` ไปยังบอร์ด **ผู้รับ** ทุกตัวที่คุณต้องการใช้
2.  เปิด Serial Monitor และจด MAC Address ที่แสดงขึ้นมาสำหรับบอร์ดผู้รับแต่ละตัว

### 2. แก้ไขโค้ดของผู้ส่ง (Sender)

1.  เปิดไฟล์ `esp_now_toggle_sender/esp_now_toggle_sender.ino`
2.  **ใส่ MAC Address ของผู้รับ:** มองหาส่วนที่เขียนว่า `// REPLACE WITH THE MAC ADDRESS OF YOUR RECEIVER(S)`
    *   แก้ไข `broadcastAddress1` โดยใส่ MAC Address ของบอร์ดผู้รับตัวแรกที่คุณจดไว้
    *   หากมีผู้รับมากกว่าหนึ่งตัว ให้เอาคอมเมนต์ `//` หน้า `broadcastAddress2` ออก และใส่ MAC Address ของผู้รับตัวที่สอง ทำซ้ำได้สูงสุด 20 ตัว
    *   **สำคัญ:** คุณต้องเพิ่มโค้ดบล็อก `esp_now_add_peer` สำหรับผู้รับแต่ละตัวด้วย (ดูตัวอย่างในโค้ด)

### 3. การเชื่อมต่อวงจร

#### ผู้ส่ง (Sender)
*   เชื่อมต่อปุ่มกดระหว่าง **GPIO0** และ **GND** (ใช้ `INPUT_PULLUP` ในโค้ด)

#### ผู้รับ (Receiver)
*   เชื่อมต่อ LED ระหว่าง **GPIO0** และ **GND** (อย่าลืมใส่ตัวต้านทานจำกัดกระแสไฟ LED ด้วย)

### 4. อัปโหลดโค้ด

1.  **สำหรับบอร์ดผู้ส่ง:** อัปโหลดโค้ด `esp_now_toggle_sender.ino` ที่แก้ไขแล้วไปยังบอร์ด ESP32 ที่จะทำหน้าที่เป็นผู้ส่งเพียง **ตัวเดียว**
2.  **สำหรับบอร์ดผู้รับ:** อัปโหลดโค้ด `esp_now_toggle_receiver.ino` ไปยังบอร์ด ESP32 **ทุกตัว** ที่จะเป็นผู้รับข้อมูล

### 5. ดูผลลัพธ์

- เปิด Serial Monitor ของบอร์ด **ผู้รับ** แต่ละตัว เพื่อดูสถานะการรับข้อมูลและการเปลี่ยนแปลงสถานะ LED
