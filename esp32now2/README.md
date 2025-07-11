# โปรเจกต์: ESP-NOW - หลายผู้ส่ง, หนึ่งผู้รับ

โปรเจกต์นี้สาธิตวิธีการใช้เทคโนโลยี ESP-NOW เพื่อส่งข้อมูลจากบอร์ด ESP32 หลายตัว (ผู้ส่ง) ไปยังบอร์ด ESP32 เพียงตัวเดียว (ผู้รับ)

- **`esp_now_multi_sender`**: โค้ดสำหรับบอร์ดที่จะอ่านค่าจากเซ็นเซอร์และส่งข้อมูลออกไป **(คุณจะใช้โค้ดนี้กับบอร์ดผู้ส่งทุกตัว)**
- **`esp_now_single_receiver`**: โค้ดสำหรับบอร์ดที่จะรับข้อมูลจากผู้ส่งทุกตัวและแสดงผลทาง Serial Monitor

## ขั้นตอนการตั้งค่า

### 1. หา MAC Address ของบอร์ดผู้รับ (Receiver)

1.  อัปโหลดโค้ดจากโปรเจกต์ `esp32c3mac` ไปยังบอร์ด **ผู้รับ** เพียงตัวเดียว
2.  เปิด Serial Monitor และจด MAC Address ที่แสดงขึ้นมา

### 2. แก้ไขโค้ดของผู้ส่ง (Senders)

คุณจะต้องแก้ไขและอัปโหลดโค้ดนี้สำหรับผู้ส่ง **ทุกตัว**

1.  เปิดไฟล์ `esp_now_multi_sender/esp_now_multi_sender.ino`
2.  **ใส่ MAC Address ของผู้รับ:** แก้ไข `broadcastAddress` โดยใส่ MAC Address ของบอร์ดผู้รับที่คุณจดไว้
3.  **ตั้งค่า ID ที่ไม่ซ้ำกัน:** มองหาบรรทัด `myData.id = 1;` ในฟังก์ชัน `loop()` และ **เปลี่ยนเลข 1 เป็น ID ที่ไม่ซ้ำกันสำหรับผู้ส่งแต่ละตัว** (เช่น 1, 2, 3, ...)

### 3. อัปโหลดโค้ด

1.  **สำหรับบอร์ดผู้ส่ง:** อัปโหลดโค้ด `esp_now_multi_sender.ino` ที่แก้ไขแล้วไปยังบอร์ด ESP32 **ทุกตัว** ที่จะทำหน้าที่เป็นผู้ส่ง
2.  **สำหรับบอร์ดผู้รับ:** อัปโหลดโค้ด `esp_now_single_receiver.ino` ไปยังบอร์ด ESP32 ที่จะเป็นผู้รับข้อมูล

### 4. ดูผลลัพธ์

- เปิด Serial Monitor ของบอร์ด **ผู้รับ** เพื่อดูข้อมูลเซ็นเซอร์ที่ได้รับจากผู้ส่งแต่ละตัว ซึ่งจะถูกระบุด้วย ID ที่คุณตั้งไว้
