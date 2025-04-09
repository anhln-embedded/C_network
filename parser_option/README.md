# 📘 Giải thích chương trình sử dụng `argc` và `argv[]` trong C

Chương trình sau đây minh họa cách xử lý **đối số dòng lệnh** trong ngôn ngữ lập trình C.

---

## 📌 Mục tiêu

Hiểu và sử dụng:
- `argc`: số lượng đối số dòng lệnh.
- `argv[]`: mảng các chuỗi chứa từng đối số.

---

## 💡 Cú pháp hàm `main` có đối số

```c
int main(int argc, char *argv[])
