#include <iostream>
#include <cstdint>

#include <array>
// Bai1 : Kiem tra kich thuoc va dia chi du lieu
void printf_size_and_address(const char *type_name, size_t size, const void *address)
{
    std::cout << "Type: " << type_name << ", Size: " << size << " bytes, Address: " << address << std::endl;
}
// Bai 2 : Truy cap mang qua pointer va offset
// Bai 3 : Pointer to struct and access field

struct Sensor
{
    /* data */
    uint8_t id;
    uint16_t raw;
    uint8_t status;
};
void print_sensor_info(const Sensor *sensor)
{
    std::cout << "Sensor ID: " << static_cast<int>(sensor->id)
              << ", Raw: " << sensor->raw
              << ", Status: " << static_cast<int>(sensor->status)
              << ", Address: " << (const void *)sensor
              << std::endl;
}
// Bai 4 : In ra gia tung byte cua bien (Memory Dump)
// Bai 5 : enum va typdef cho ma trang thai
enum class Status : uint8_t
{
    OK = 0,
    FAIL = 1,
    BUSY = 2
};
typedef Status SysTate;
const char *status_to_string(SysTate state)
{
    switch (state)
    {
    case Status::OK:
        return "OK";
    case Status::FAIL:
        return "FAIL";
    case Status::BUSY:
        return "BUSY";
    default:
        return "UNKNOWN";
    }
}
int main()
{
    // Kich thuoc cac kieu du lieu co ban
    std::cout << "=== Kich thuoc cac kieu du lieu co ban ===" << std::endl;
    uint8_t a = 1;
    uint16_t b = 2;
    uint32_t c = 3;
    float d = 4.0f;

    printf_size_and_address("uint8_t", sizeof(a), (const void *)&a);
    printf_size_and_address("uint16_t", sizeof(b), (const void *)&b);
    printf_size_and_address("uint32_t", sizeof(c), (const void *)&c);
    printf_size_and_address("float", sizeof(d), (const void *)&d);
    // Truy cap mang qua pointer va offset
    std::cout << "\n=== Truy cap mang qua pointer va offset ===" << std::endl;
    uint8_t arr[8] = {10, 11, 12, 13, 14, 15, 16, 17};
    uint8_t *ptr = arr; // Pointer tro den phan tu dau tien cua mang
    for (auto v : arr)
    {
        size_t offset = v - 10;          // Tinh offset duoc su dung de truy cap phan tu
        uint8_t value = *(ptr + offset); // Truy cap phan tu qua pointer va offset
        std::cout << "arr[" << offset << "] = " << static_cast<int>(value) << " @" << (void *)(ptr + offset) << std::endl;
    }
    // Pointer to struct and access field
    std::cout << "\n=== Pointer to struct and access field ===" << std::endl;
    Sensor s1 = {5, 0x1234, 1};
    Sensor *p = &s1; // Pointer tro den struct Sensor
    print_sensor_info(p);
    // In ra gia tung byte cua bien (Memory Dump)
    std::cout << "\n=== In ra gia tung byte cua bien (Memory Dump) ===" << std::endl;
    uint32_t val = 0x12345678;
    uint8_t *byte_ptr = reinterpret_cast<uint8_t *>(&val);
    std::cout << "Memory dump of val (0x12345678): ";
    for (size_t i = 0; i < sizeof(val); ++i)
    {
        std::cout << std::hex << static_cast<int>(*(byte_ptr + i)) << " ";
    }
    // Enum va typedef cho ma trang thai
    std::cout << "\n\n=== Enum va typedef cho ma trang thai ===" << std::endl;
    SysTate state = Status::BUSY;
    std::cout << "Current system state: " << status_to_string(state) << std::endl;
    return 0;
}