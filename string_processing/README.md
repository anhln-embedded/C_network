# Các hàm xử lý chuỗi và bộ nhớ trong C (`<string.h>`)

| **Số hiệu** | **Hàm** | **Chức năng & Mô tả** |
|-------------|---------|------------------------|
| 1 | `void *memchr(const void *str, int c, size_t n)` | Tìm ký tự `c` trong `n` byte đầu tiên của chuỗi `str`. |
| 2 | `int memcmp(const void *str1, const void *str2, size_t n)` | So sánh `n` byte đầu tiên của `str1` và `str2`. |
| 3 | `void *memcpy(void *dest, const void *src, size_t n)` | Sao chép `n` byte từ `src` đến `dest`. |
| 4 | `void *memmove(void *dest, const void *src, size_t n)` | Sao chép `n` byte từ `src` đến `dest` (hỗ trợ vùng nhớ chồng lặp). |
| 5 | `void *memset(void *str, int c, size_t n)` | Gán giá trị `c` cho `n` byte đầu tiên của `str`. |
| 6 | `char *strcat(char *dest, const char *src)` | Nối `src` vào cuối chuỗi `dest`. |
| 7 | `char *strncat(char *dest, const char *src, size_t n)` | Nối tối đa `n` ký tự từ `src` vào `dest`. |
| 8 | `char *strchr(const char *str, int c)` | Tìm ký tự `c` đầu tiên trong chuỗi `str`. |
| 9 | `int strcmp(const char *str1, const char *str2)` | So sánh hai chuỗi `str1` và `str2`. |
| 10 | `int strncmp(const char *str1, const char *str2, size_t n)` | So sánh tối đa `n` ký tự giữa `str1` và `str2`. |
| 11 | `int strcoll(const char *str1, const char *str2)` | So sánh hai chuỗi theo thứ tự ngôn ngữ hiện tại (LC_COLLATE). |
| 12 | `char *strcpy(char *dest, const char *src)` | Sao chép chuỗi `src` sang `dest`. |
| 13 | `char *strncpy(char *dest, const char *src, size_t n)` | Sao chép tối đa `n` ký tự từ `src` sang `dest`. |
| 14 | `size_t strcspn(const char *str1, const char *str2)` | Đo độ dài đoạn đầu `str1` không chứa ký tự nào trong `str2`. |
| 15 | `char *strerror(int errnum)` | Trả về chuỗi mô tả lỗi tương ứng với `errnum`. |
| 16 | `size_t strlen(const char *str)` | Trả về độ dài chuỗi `str` (không tính ký tự null). |
| 17 | `char *strpbrk(const char *str1, const char *str2)` | Tìm ký tự đầu tiên trong `str1` có trong `str2`. |
| 18 | `char *strrchr(const char *str, int c)` | Tìm ký tự `c` cuối cùng trong chuỗi `str`. |
| 19 | `size_t strspn(const char *str1, const char *str2)` | Đo độ dài đoạn đầu `str1` chỉ gồm ký tự có trong `str2`. |
| 20 | `char *strstr(const char *haystack, const char *needle)` | Tìm chuỗi `needle` đầu tiên trong `haystack`. |
| 21 | `char *strtok(char *str, const char *delim)` | Cắt chuỗi `str` thành các phần (token) theo dấu phân cách `delim`. |
| 22 | `size_t strxfrm(char *dest, const char *src, size_t n)` | Chuyển đổi `src` thành dạng so sánh ngôn ngữ rồi lưu vào `dest`. |
