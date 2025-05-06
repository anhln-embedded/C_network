# 🧬 fork() trong Lập trình C - Khái niệm cơ bản

## 📌 1. fork() là gì?

`fork()` là một system call trong Unix/Linux dùng để tạo ra một **tiến trình con (child process)** từ tiến trình hiện tại (cha - parent process).  
Tiến trình con là một **bản sao gần như hoàn toàn** của tiến trình cha.

---

## 🔧 2. Cú pháp

```c
#include <unistd.h>

pid_t fork();
```

---

## 📤 3. Giá trị trả về của fork()

| Giá trị trả về     | Ý nghĩa                                      |
|--------------------|----------------------------------------------|
| `> 0`              | Trong tiến trình cha – trả về PID của con     |
| `== 0`             | Trong tiến trình con                         |
| `< 0`              | fork thất bại – không tạo được tiến trình mới |

---

## 🧠 4. Đặc điểm chính của fork()

- Cả cha và con **chạy song song, tiếp tục từ vị trí sau `fork()`**.
- Không chia sẻ vùng nhớ (mỗi tiến trình có không gian địa chỉ riêng).
- Dữ liệu ban đầu giống nhau, nhưng thay đổi độc lập sau đó (Copy-On-Write).
- Mỗi tiến trình có PID riêng.

---

## 🧪 5. Ví dụ đơn giản

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Đây là tiến trình con. PID = %d\n", getpid());
    } else if (pid > 0) {
        printf("Đây là tiến trình cha. PID = %d\n", getpid());
    } else {
        printf("Tạo tiến trình con thất bại.\n");
    }

    return 0;
}
```

---

## 🔄 6. Một số lưu ý khi dùng fork()

- Nên gọi `wait()` trong tiến trình cha để đợi con kết thúc, tránh zombie process.
- Nếu dùng fork nhiều lần có thể tạo ra **cây tiến trình** phức tạp.
- Dùng `getpid()` để lấy PID của tiến trình hiện tại.
- Dùng `getppid()` để lấy PID của tiến trình cha.

---

## 📚 7. Liên quan

- `wait()` – đợi tiến trình con kết thúc.
- `exec()` – thay thế tiến trình hiện tại bằng chương trình mới.
- `vfork()` – một biến thể tối ưu hơn trong một số trường hợp.

---

## 🧭 8. Ứng dụng của fork()

- Tạo các tiến trình con trong server (ví dụ: Apache).
- Viết shell, daemon, hoặc hệ thống đa tiến trình.
- Kết hợp với `exec()` để thực thi chương trình con.

---

## 📌 Tổng kết

| Đặc điểm              | Giá trị                                |
|-----------------------|----------------------------------------|
| Tạo tiến trình mới    | Có                                     |
| Không gian địa chỉ    | Tách biệt (copy-on-write)              |
| Chạy song song        | Có                                     |
| Phải dùng `wait()`?   | Nên dùng để tránh zombie               |
