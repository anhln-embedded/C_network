# 📁 Các thao tác với file trong ngôn ngữ C

## 1. Các thao tác cơ bản

| Thao tác                   | Hàm tương ứng                                           | Mô tả |
|----------------------------|----------------------------------------------------------|------|
| Mở file                    | `fopen()`                                                | Mở file để đọc, ghi hoặc cập nhật. |
| Đóng file                  | `fclose()`                                               | Đóng file sau khi sử dụng. |
| Đọc dữ liệu từ file        | `fgetc()`, `fgets()`, `fread()`, `fscanf()`             | Đọc từng ký tự, dòng, hoặc khối dữ liệu. |
| Ghi dữ liệu vào file       | `fputc()`, `fputs()`, `fwrite()`, `fprintf()`           | Ghi từng ký tự, chuỗi, hoặc dữ liệu định dạng. |
| Di chuyển vị trí con trỏ   | `fseek()`, `ftell()`, `rewind()`                        | Di chuyển tới vị trí cụ thể trong file. |
| Kiểm tra lỗi hoặc kết thúc | `feof()`, `ferror()`                                     | Kiểm tra đã kết thúc file hoặc có lỗi không. |

---

## 2. Các hàm thao tác với file

### 📌 `FILE *fopen(const char *filename, const char *mode);`
- Mở file với tên và chế độ tương ứng.
- **Chế độ mở**:
  - `"r"`: đọc.
  - `"w"`: ghi, xóa nội dung cũ.
  - `"a"`: ghi thêm.
  - `"r+"`, `"w+"`, `"a+"`: đọc/ghi kết hợp.

---

### 📌 `int fclose(FILE *stream);`
- Đóng file đã mở.

---

### 📌 `int fgetc(FILE *stream);`
- Đọc một ký tự từ file.

---

### 📌 `char *fgets(char *str, int n, FILE *stream);`
- Đọc một dòng hoặc tối đa `n - 1` ký tự từ file.

---

### 📌 `size_t fread(void *ptr, size_t size, size_t count, FILE *stream);`
- Đọc dữ liệu nhị phân từ file.

---

### 📌 `int fputc(int char, FILE *stream);`
- Ghi một ký tự vào file.

---

### 📌 `int fputs(const char *str, FILE *stream);`
- Ghi một chuỗi vào file.

---

### 📌 `size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);`
- Ghi dữ liệu nhị phân.

---

### 📌 `int fprintf(FILE *stream, const char *format, ...);`
- Ghi dữ liệu theo định dạng vào file (giống `printf`).

---

### 📌 `int fscanf(FILE *stream, const char *format, ...);`
- Đọc dữ liệu theo định dạng từ file (giống `scanf`).

---

### 📌 `int fseek(FILE *stream, long offset, int whence);`
- Di chuyển con trỏ file:
  - `SEEK_SET`: đầu file.
  - `SEEK_CUR`: vị trí hiện tại.
  - `SEEK_END`: cuối file.

---

### 📌 `long ftell(FILE *stream);`
- Trả về vị trí hiện tại của con trỏ file.

---

### 📌 `void rewind(FILE *stream);`
- Đưa con trỏ về đầu file.

---

### 📌 `int feof(FILE *stream);`
- Trả về true nếu đã tới cuối file.

---

### 📌 `int ferror(FILE *stream);`
- Trả về true nếu có lỗi trong thao tác file.

---

## 3. Ví dụ đơn giản: Đọc và ghi file

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("example.txt", "w");
    if (fp == NULL) {
        printf("Không thể mở file.\n");
        return 1;
    }

    fprintf(fp, "Hello, file!\n");
    fclose(fp);

    fp = fopen("example.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), fp);
    printf("Nội dung file: %s", buffer);
    fclose(fp);

    return 0;
}
