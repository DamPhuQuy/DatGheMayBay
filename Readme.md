# 📁 DatGheMayBay

[Vietnamese]

Mô tả chung về đề tài:

- Hãng hàng không ITF-Airway điều hành một chiếc máy bay với số chỗ ngồi MAX_SEATs.
- Hãng hàng không này cần xây dựng chương trình để xác định ghế nào còn trống để xếp chỗ cho khách hàng trên mỗi chuyến bay.
- Sơ đồ chỗ ngồi trên máy bay được mô tả trên một file.

[English]

General project description:

- ITF-Airway airline operates an aircraft with MAX_SEATs seats.
- The airline needs to develop a program to determine which seats are available for passenger allocation on each flight.
- The seating layout on the aircraft is described in a file.

---

## Distribution

### 1. 📂 `library/` – Chứa các file header `.h`

| File Name          | Mô tả                                |
| ------------------ | ------------------------------------ |
| `global.h`         | Biến toàn cục, định nghĩa dùng chung |
| `admin.h`          | Hàm liên quan đến quản trị           |
| `import_data.h`    | Hàm nhập dữ liệu                     |
| `log_check.h`      | Hàm kiểm tra và ghi log              |
| `print_menu.h`     | In menu giao diện                    |
| `selecting_seat.h` | Hàm chọn ghế                         |

---

### 2. 📂 `src/` – Chứa các file source code `.cpp`

| File Name            | Mô tả                                     |
| -------------------- | ----------------------------------------- |
| `main.cpp`           | Hàm `main()`, điểm khởi động chương trình |
| `admin.cpp`          | Cài đặt chức năng admin                   |
| `import_data.cpp`    | Đọc dữ liệu từ file                       |
| `log_check.cpp`      | Ghi và kiểm tra log                       |
| `print_menu.cpp`     | In menu lựa chọn                          |
| `selecting_seat.cpp` | Xử lý chọn ghế ngồi                       |

---

### 3. 📂 `data/` – Chứa dữ liệu các chuyến bay

#### 📂 `data/ITF2023/` – Chuyến bay ITF2023

| File Name                 | Mô tả                |
| ------------------------- | -------------------- |
| `BookedSeatingChart.txt`  | Danh sách ghế đã đặt |
| `FlightInformation.txt`   | Thông tin chuyến bay |
| `PersonalInformation.txt` | Dữ liệu hành khách   |
| `SeatingChart.txt`        | Sơ đồ ghế            |
| `TicketInformation.txt`   | Thông tin vé         |

#### 📂 `data/ITF2024/`, `data/ITF2025/`

> Các chuyến bay khác có cấu trúc dữ liệu tương tự.

---

### 4. 📄 Các file dữ liệu khác

| File Name      | Mô tả                       |
| -------------- | --------------------------- |
| `accounts.txt` | Tài khoản người dùng        |
| `flights.txt`  | Danh sách các chuyến bay    |
| `log.txt`      | Lưu thông tin log hoạt động |

---

### 5. 📂 `build/` – Chứa các file biên dịch đầu ra

> Thư mục này chứa file `.o` sau khi build chương trình.

---

## Environment Variables

To run this project, you will need to install and add the following environment variables to your computer.

[`Mingw64`](https://www.mingw-w64.org/) or [`Msys2`](https://www.msys2.org/)

## Run

### Method 1: Compile the entire program directly (quick and simple):

#### Step 1: Compile with one single line:

```bash
g++ -Ilibrary src/main.cpp src/admin.cpp src/global.cpp src/import_data.cpp src/log_check.cpp src/print_menu.cpp src/selecting_seat.cpp -o DatGheMayBay.exe
```

### Step 2: Run DatGheMayBay.exe:

```bash
.\DatGheMayBay.exe
```

---

### Method 2: Compile each `.cpp` file separately to speed up later builds:

#### Step 1: Create a `build` folder to store `.o` files

```bash
mkdir build
```

#### Step 2: Compile each `.cpp` file individually (only recompile the ones you modify)

```bash
g++ -Ilibrary -c src/main.cpp -o build/main.o
g++ -Ilibrary -c src/admin.cpp -o build/admin.o
g++ -Ilibrary -c src/global.cpp -o build/global.o
g++ -Ilibrary -c src/import_data.cpp -o build/import_data.o
g++ -Ilibrary -c src/log_check.cpp -o build/log_check.o
g++ -Ilibrary -c src/print_menu.cpp -o build/print_menu.o
g++ -Ilibrary -c src/selecting_seat.cpp -o build/selecting_seat.o
```

**Notice:** When you modify one or more than one `.cpp`, you only need to compile the files which you had modified before. There is no need to modify the whole files again.

**For example:** You modify `admin.cpp` file:

```bash
g++ -Ilibrary -c src/admin.cpp -o build/admin.o
```

#### Step 3: Link all `.o` files into the final program

```bash
g++ build/*.o -o DatGheMayBay.exe
```

#### Run the program:

```bash
.\DatGheMayBay.exe
```

**Advantage of Method 2**: Later, you only need to recompile the `.cpp` files you changed, without rebuilding the entire project → significantly faster build times.

## Contributor

| Name             | Class     |
| :--------------- | :-------- |
| `Dam Phu Quy`    | `24T_DT2` |
| `Dam Vinh Quang` | `24T_DT1` |

## Students of Danang university of Science and Technology

- [Dam Phu Quy](https://www.facebook.com/damphuquy/)
- [Dam Vinh Quang](https://www.facebook.com/vinh.quang.am.2024)
