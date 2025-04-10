# 1 Tổng quan về Linkest List
## 1.1 Khái niệm
Đây là cấu trúc dữ liệu danh sách liên kết được dùng để lưu trữ nhiều phần tử tương tự như mảng, tuy nhiên khác với mảng có các địa chỉ của các phần tử liền kề nhau và cố định. Linkest list lưu trữ các phần tử với địa chỉ có thể thay đổi 1 cách linh hoạt, do chúng có tính liên kết với nhau.

=> Chính vì vậy ta có thể thực hiện các thao tác như __thêm__, __sửa__, __xóa__ , __chèn__ các phần tử bên dễ dàng và nhanh chóng hơn so với mảng
## 1.2 So sánh với mảng
### a) Trường hợp mảng nhỏ
ví dụ ta muốn __xóa__ 1 phần tử thì phải trải qua các bước sau
<p align = "center">
<img src = "https://github.com/user-attachments/assets/fc1bec82-fd38-4579-824d-5494cdaeff81" width = "400" height = "200">

__+ Bước 1:__ Xóa phần tử tại ví trí chỉ dịnh bằng cách ghi ký tự null

__+ Bước 2:__ dịch các phần tử phía sau vị trí xóa qua bên trái (số    lượng phần tử trong mảng càng nhiều thì thời gian xử lý sẽ càng lâu)

__+ Bước 3:__ Gán vị trí cuối mảng là null

__+ Bước 4:__ điều chỉnh lại kích thước mảng 

<p align = "center">
<img src = "https://github.com/user-attachments/assets/326863b6-a7bc-4409-aac1-85eb62f6bd4a" width = "600" height = "200">

### b) Trường hợp mảng lớn
Nếu ta áp dụng phương pháp như trường hợp mảng nhỏ đối với mảng sau đây thì sẽ không còn hiệu quả nữa, do số phần tử khá là lớn, vì vậy việc dịch các phần tử sẽ tốn thời gian xử lý của CPU, khiến chương trình chậm hơn

<p align = "center">
<img src = "https://github.com/user-attachments/assets/d4e68017-8b1c-4b18-9d89-c285673f8722" width = "600" height = "200">

=> Đây là lý do sử dụng linkest list sẽ hiệu quả hơn so với mảng

# 2. Mô phỏng linkest list
Linkest list sẽ lưu trữ các phần tử gọi là node gồm 2 thành phần đó là 
+ giá trị nó lưu trữ
+ địa chỉ của node tiếp theo 

## 2.1 Tạo ra 1 node trong linkest list
Đầu tiên ta tạo 1 struct để lưu trữ các thành phần của 1 node
```bash
typedef struct Node_t
{
    int data;
    struct Node *next;
} Node_t;
```
Tiếp theo ta sẽ có hàm để có hàm để khởi tạo 1 node
```bash
Node_t *createNode(int data)
{
    Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
    if (new_node == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}
```
Trong chương trình chính ta tạo ra 1 node như sau
+ ta sẽ dùng con trỏ __head__ để lưu trữ địa chỉ trả về của node đầu tiên được khởi tạo
```bash
int main(){
    Node* head = CreateNode(23);
    return 0;
}
```
+ Hình dưới đây mô phỏng cách mà __head__ quản lý node mà ta tạo ra
<p align = "center">
<img src = "https://github.com/user-attachments/assets/fc708b45-eb34-4bd0-bced-b219a5705fa5" width = "300" height = "100">

## 2.2 Thêm node vào linkest list
### a) Thêm node vào đầu list
<p align = "center">
<img src = "https://github.com/user-attachments/assets/6515b7a4-8051-48aa-b43f-e90f9545d411" width = "500" height = "200">

+ Tạo node mới 

+ Kiểm tra linkest list có node nào không, nếu không thì gán địa chỉ của node mới cho địa chỉ dầu __head__ của linkest list

+ Nếu list đã có node rồi thì gán địa ban đầu có sẵn trong list cho địa chỉ next của node mới tạo ra

+ Cuối cùng ta cập nhật địa chỉ của node mới tạo thành địa chỉ ban đầu của list __(tương tự trường hợp nếu list không có node nào)__

```bash
void push_front(Node_t **head, int data)
{
    Node_t *new_node = createNode(data);
    if (*head != NULL)
    {
        new_node->next = *head;
    }
    *head = new_node;
}
```
### b) Thêm vào cuối list

<p align = "center">
<img src = "https://github.com/user-attachments/assets/2b469609-7f1e-40dd-a177-6ee5583a1bf4" width = "500" height = "200">

+ Tạo ra 1 node,kiểm tra trong list có hay không, nếu không thì gán node đầu tiên 
+ Nếu có node trong list thì dùng 1 con trỏ để lặp qua tất cả các node trong list
+ Nếu node hiện tại trỏ đến null, thì tiến hành liên kết với node đã tạo

```bash
void push_back(Node_t **head, int data)
{
    Node_t *new_node = createNode(data);
    Node_t *current_node = *head;
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        current_node->next = new_node;
        new_node->next = NULL;
    }
}

```
### c) Thêm 1 node vào vị trí bất kỳ trong list

<p align = "center">
<img src = "https://github.com/user-attachments/assets/48849f6a-3853-4c3f-9ba3-34790a0d789d" width = "500" height = "200">

+ Đầu tiên ta tạo ra 1 node 
+ Nếu vị trí thêm vào là 0 thì thay node ban đầu trong list là node mới tạo ra
+ Nếu vị trí thêm vào khác không thì lặp qua từng node đến khi gặp vị tri cần thêm thì liên kết địa chỉ của node tạo ra với 2 node trước và sau vị trí thêm vào
+ Trong trường hợp đã lắp qua hết các phần tử mà không tìm thấy vị trí cần thêm vào thì dừng việc xử lý

```bash
void insert(Node_t **head, int data, int position)
{
    Node_t *new_node = createNode(data);
    if (position == 0)
    {
        new_node->next = *head;
        *head = new_node;
    }
    else
    {
        Node_t *current_node = *head;
        int index = 0;
        while (current_node != NULL && index < position - 1)
        {
            current_node = current_node->next;
            index++;
        }
        if (current_node != NULL)
        {
            new_node->next = current_node->next;
            current_node->next = new_node;
        }
        else
        {
            printf("Error Position\n");
            free(new_node);
        }
    }
}
```
## 2.3 Xóa node khỏi linkest list
### a) Xóa node đầu của list

<p align = "center">
<img src ="https://github.com/user-attachments/assets/82ae9b33-f014-4e32-a6ef-567a19ba04d9" width = "500" height = "250">

__Bước 1:__ Đầu tiên ta kiểm tra có node nào không nếu có thì lưu địa chỉ của node đầu tiên

__Bước 2:__ Ta cập nhật địa chỉ node đầu là node tiếp theo

__Bước 3:__ Ta giải phóng node đầu đã lưu vào con trỏ tạm trước đó

```bash
void pop_front(Node_t **head)
{
    if (*head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    else
    {
        Node_t *tmep = *head;
        *head = (*head)->next;
        free(tmep);
    }
}
```
### b) Xóa node cuối cùng của list

<p align = "center">
<img src ="https://github.com/user-attachments/assets/b90e11bd-0fbc-40ad-9939-2715acea3e45" width = "500" height = "250">

__Bước 1:__ Ta kiểm tra có node nào trong list không thì dừng xử lý
+ Nếu chỉ có 1 node: gọi ra hàm xóa node đầu 
+ Nếu có nhiều node: lặp qua từng node đến node kế cuối

__Bước 2:__ lưu địa chỉ next (node tiếp theo) vào 1 con trỏ

__Bước 3:__ giải phóng con trỏ lưu node này (cũng là node cuối)

__Bước 4:__ cập nhật địa chỉ next là null 

```bash
void pop_back(Node_t **head)
{
    Node_t *current_node = *head;
    if (current_node == NULL)
    {
        printf("List is empty\n");
        return;
    }
    else if (current_node->next == NULL)
    {
        pop_front(head);
    }
    else
    {
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        Node_t *temp = current_node->next;
        current_node->next = NULL;
        free(temp);
    }
}
```
### c) Xóa toàn bộ node 

<p align = "center">
<img src ="https://github.com/user-attachments/assets/64692987-9ac3-4f94-939d-b8b8c556d66d" width = "550" height = "300">

__+ Bước 1:__ ta kiểm tra list có node nào không nếu có thì tiếp tục bước 2

__+ Buóc 2:__ ta lưu node tiếp theo sang 1 con trỏ khác

__+ Bước 3:__ ta giải phóng node hiện tại

__+ Bước 4:__ ta lấy lại node đã lưu trước đó 

__+ Bước 5:__ ta lặp lại bước 2 cho đến khi lặp qua hết tất cả các node

__+ Bước 6:__ ta gán con trỏ đến node đầu là NULL

```bash

void free_list(Node_t **heed)
{
    Node_t *current_node = *heed;
    Node_t *temp = NULL;
    while (current_node != NULL)
    {
        temp = current_node;
        current_node = current_node->next;
        free(temp);
    }
    *heed = NULL;
}
```

### d) Xóa node ở vị trí cho trước 

<p align = "center">
<img src = "https://github.com/user-attachments/assets/23cc5bb5-7ac0-4fdd-bc6d-a38dbf32e740" width = "600" height = "250">

+ Đầu tiên ta sẽ kiểm tra nếu vị trí xóa là 0 thì sẽ gọi ra hàm xóa node ở đầu list như đã đề cập bên trên
+ Lăp qua từng node cho đến khi đến vị trí cần xóa
+ Dùng 1 con trỏ __temp__ đế lưu địa chỉ node hiện tại
+ liên kết địa chỉ next của node trước đó với node sau vị trí cần xóa
+ tiến hành xóa __temp__

```bash
void delete_list(Node_t **heed, int position)
{
    Node_t *current_node = *heed;
    Node_t *temp = NULL;
    while (current_node != NULL && position > 0)
    {
        temp = current_node;
        current_node = current_node->next;
        position--;
    }
    if (current_node == NULL)
    {
        printf("Error Position\n");
        return;
    }
    if (temp == NULL)
    {
        *heed = current_node->next;
    }
    else
    {
        temp->next = current_node->next;
    }
    free(current_node);
    current_node = NULL;
    temp = NULL;            
}
```

## 2.4 Đọc giá trị các node

### a) Lấy ra node đầu và cuối list

```bash

int front(Node_t *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return -1;
    }
    return head->data;
}

int back(Node_t *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return -1;
    }
    Node_t *current_node = head;
    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }
    return current_node->data;
}
```

### b) Đọc giá trị của node ở vị trí bất kỳ
+ Đầu tiên ta cũng kiểm tra list có rỗng không hay vị trí muốn lấy ra giá trị có hợp lệ hay không thì mới xử lý tiếp
+ Nếu thỏa điều kiện Ta sẽ lặp qua các node cho đến khi đến vị trí muốn đọc ra và trả về kết quả
```bash
int size(Node *head)
{
    if(empty(head)) 
        return 0;
    Node *current = head;
    int size = 1; //mặc định trong list có ít nhất 1 node
    while (current->next != NULL)
    {
        current = current->next;
        size++;
    }
    return size;
}
int get_postion(Node *head, int position)
{
    if (empty(head) || position == 0 || position > size(head))
        return 0;
    Node *current = head;
    int index = 0;
    while (index < position - 1)
    {
        current = current->next;
        index++;
    }
    int val = current->val;
    return val;
}
```

## 2.5 Sắp xếp linkest list

Để sắp xếp danh sách liên kết, ta có thể sử dụng thuật toán sắp xếp nổi bọt (Bubble Sort). Dưới đây là cách triển khai:

```c
void sort_list(Node_t **head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return; // Danh sách rỗng hoặc chỉ có một phần tử
    }

    Node_t *current, *next_node;
    int temp_data;
    int swapped;

    do
    {
        swapped = 0;
        current = *head;

        while (current->next != NULL)
        {
            next_node = current->next;

            if (current->data > next_node->data)
            {
                // Hoán đổi giá trị của hai node
                temp_data = current->data;
                current->data = next_node->data;
                next_node->data = temp_data;

                swapped = 1;
            }

            current = current->next;
        }
    } while (swapped);
}
```

### Giải thích:
1. **Kiểm tra danh sách rỗng hoặc chỉ có một phần tử**: Nếu đúng, không cần sắp xếp.
2. **Sử dụng vòng lặp do-while**: Tiếp tục lặp cho đến khi không còn hoán đổi nào xảy ra.
3. **So sánh và hoán đổi giá trị**: Nếu giá trị của node hiện tại lớn hơn giá trị của node tiếp theo, hoán đổi chúng.
4. **Kết thúc khi danh sách đã được sắp xếp**.

### Ví dụ sử dụng:
```c
int main()
{
    Node_t *head = NULL;

    push_back(&head, 5);
    push_back(&head, 3);
    push_back(&head, 8);
    push_back(&head, 1);

    printf("Danh sách trước khi sắp xếp:\n");
    print_list(head);

    sort_list(&head);

    printf("Danh sách sau khi sắp xếp:\n");
    print_list(head);

    free_list(&head);
    return 0;
}
```

### Kết quả:
```
Danh sách trước khi sắp xếp:
5 -> 3 -> 8 -> 1 -> NULL

Danh sách sau khi sắp xếp:
1 -> 3 -> 5 -> 8 -> NULL
```