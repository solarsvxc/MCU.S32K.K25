# RISC vs CISC

## 1. RISC (Reduced Instruction Set Computer)

Tập trung vào tập lệnh nhỏ, đơn giản, thực hiện nhanh (đa phần chỉ trong **1 chu kỳ clock**).  

### Đặc điểm
- Chương trình dài hơn, cần nhiều lệnh hơn.  
- Tối ưu tốc độ xử lý và sức mạnh.  
- Cần nhiều thanh ghi.  
- Processor cần cache để giảm thời gian truy cập bộ nhớ.  
- Chỉ có lệnh **LOAD/STORE** truy cập vào bộ nhớ, các lệnh khác dùng thanh ghi.  
- Sử dụng **pipelining** để tăng tốc độ thực thi.  
- Độ dài lệnh **cố định**, dễ giải mã.  
- Dựa trên cấu trúc **load-store** (tập trung vào register).  
- Thường cần **ít chu kỳ** hơn để thực hiện lệnh.  

### Nhược điểm
- Không hỗ trợ **memory-to-memory** (chỉ qua thanh ghi).  
- Chương trình thường dài hơn, tốn nhiều lệnh hơn.  
- Lệnh phức tạp thì khó hiện thực hóa.  

### Ví dụ
```asm
c = a + b
LOAD R1, A
LOAD R2, B
ADD  R3, R1, R2
STORE C, R3
```

---

## 2. CISC (Complex Instruction Set Computer)

Sử dụng **tập lệnh phức tạp**, mỗi lệnh có thể thực hiện nhiều thao tác, giúp chương trình ngắn hơn.  

### Đặc điểm
- Lệnh phức tạp, cần **nhiều chu kỳ clock** để thực hiện.  
- Có thể thao tác trực tiếp với **bộ nhớ** (memory-to-memory).  
- Độ dài lệnh **không cố định**, tùy độ phức tạp.  
- Chương trình ngắn gọn, dễ viết hơn.  
- Tối ưu hóa sử dụng bộ nhớ.  
- ISA phức tạp, compiler tối ưu hóa khó khăn hơn.  
- Thiết kế CPU phức tạp, tốn nhiều register.  
- Phù hợp với đa dạng tác vụ.  

### Ví dụ
```asm
c = a + b
ADD A, B, C
```

---

## 3. Điểm giống nhau
- Đều là **ISA (Instruction Set Architecture)** – kiến trúc tập lệnh cho máy tính.  