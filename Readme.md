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

### 1. 📂 `library/` – Contains header files `.h`

| File Name          | Description                         |
| ------------------ | ----------------------------------- |
| `global.h`         | Global variables and shared defines |
| `admin.h`          | Admin-related function declarations |
| `import_data.h`    | Data importing functions            |
| `log_check.h`      | Logging and checking utilities      |
| `print_menu.h`     | Functions for displaying menus      |
| `selecting_seat.h` | Seat selection functions            |

---

### 2. 📂 `src/` – Contains source code files `.cpp`

| File Name            | Description                        |
| -------------------- | ---------------------------------- |
| `main.cpp`           | Entry point with `main()` function |
| `admin.cpp`          | Admin functionalities              |
| `global.cpp`         | Supportive functions               |
| `import_data.cpp`    | Load data from files               |
| `log_check.cpp`      | Log writing and checking           |
| `print_menu.cpp`     | Print UI menus                     |
| `selecting_seat.cpp` | Handle seat selection logic        |

---

### 3. 📂 `data/` – Contains flight data (text files)

#### 📂 `data/ITF2023/` – Flight: ITF2023

| File Name                 | Description          |
| ------------------------- | -------------------- |
| `BookedSeatingChart.txt`  | List of booked seats |
| `FlightInformation.txt`   | Flight details       |
| `PersonalInformation.txt` | Passenger data       |
| `SeatingChart.txt`        | Full seating chart   |
| `TicketInformation.txt`   | Ticket details       |

#### 📂 `data/ITF2024/`, `data/ITF2025/`

> Other flights with the same data structure.

---

### 4. 📄 Other data files

| File Name      | Description               |
| -------------- | ------------------------- |
| `accounts.txt` | User account information  |
| `flights.txt`  | List of available flights |
| `log.txt`      | Log of system activities  |

---

### 5. 📂 `build/` – Compiled output directory

> This folder contains the compiled output `.o` after building the program.

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
