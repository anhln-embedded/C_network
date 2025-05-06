# 📘 Giải thích một số `__attribute__` trong C

Trong GCC (và Clang), `__attribute__` là một cú pháp mở rộng giúp lập trình viên cung cấp thông tin bổ sung cho trình biên dịch để tối ưu, cảnh báo, hoặc điều khiển cách hàm, biến và struct được xử lý.

---

## 🔧 1. Function Attributes

### `constructor`
- Hàm được gọi **trước `main()`**
```c
__attribute__((constructor))
void init() {
    // Chạy trước main
}
