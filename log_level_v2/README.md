# 1. Log level – Các mức độ ghi log

Mức độ ghi log (*log levels*) giúp phân loại và ưu tiên thông điệp nhật ký trong hệ thống, từ đó hỗ trợ việc theo dõi, bảo trì và xử lý sự cố hiệu quả.

## Bảng tóm tắt log levels

| Mức độ  | Mô tả ngắn gọn                            | Mức ưu tiên |
|--------|--------------------------------------------|-------------|
| TRACE  | Ghi chi tiết mọi hành động nhỏ             | Thấp nhất   |
| DEBUG  | Gỡ lỗi, ghi trạng thái biến, logic xử lý   |             |
| INFO   | Thông tin hoạt động bình thường            |             |
| WARN   | Cảnh báo rủi ro tiềm tàng                  |             |
| ERROR  | Lỗi ảnh hưởng đến chức năng                |             |
| FATAL  | Lỗi nghiêm trọng làm sập hệ thống          | Cao nhất    |

---

## 1.1. TRACE
- Mức độ chi tiết nhất, ghi nhận mọi sự kiện nhỏ nhất trong hệ thống.
- Hữu ích khi cần theo dõi luồng dữ liệu hoặc hành động cụ thể trong ứng dụng.

## 1.2. DEBUG
- Mức độ chi tiết nhưng nhẹ hơn TRACE, ghi nhận trạng thái biến, dòng mã và các sự kiện nội bộ.
- Chủ yếu dùng trong giai đoạn phát triển để kiểm tra và gỡ lỗi.

## 1.3. INFO
- Ghi nhận các hoạt động quan trọng trong hệ thống nhưng không phải lỗi.
- Ví dụ: kết nối cơ sở dữ liệu thành công, người dùng đăng nhập, tiến trình hoàn tất.

## 1.4. WARN
- Cảnh báo về hành vi không lý tưởng hoặc vấn đề tiềm tàng.
- Không ảnh hưởng ngay lập tức nhưng có thể gây lỗi trong tương lai nếu không xử lý.

## 1.5. ERROR
- Ghi nhận lỗi xảy ra trong quá trình thực thi, ảnh hưởng đến chức năng của hệ thống.
- Cần xử lý sớm để đảm bảo hệ thống hoạt động ổn định.

## 1.6. FATAL
- Mức nghiêm trọng nhất. Những lỗi ở mức này thường khiến ứng dụng bị ngừng hoạt động hoặc sụp đổ.
- Yêu cầu hành động khẩn cấp để khắc phục và khôi phục hệ thống.
