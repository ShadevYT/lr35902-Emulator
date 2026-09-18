#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iomanip>

class LR35902 {
public:
    // Registros de 8 bits de la CPU
    uint8_t A = 0, F = 0;
    uint8_t B = 0, C = 0;
    uint8_t D = 0, E = 0;
    uint8_t H = 0, L = 0;

    // Registros de 16 bits (Program Counter y Stack Pointer)
    uint16_t PC = 0x0100; // El punto de entrada oficial de la Game Boy
    uint16_t SP = 0xFFFE;

    // Bus de memoria de 64 KB (65,536 bytes)
    uint8_t memory[65536] = {0};

    // Función para abrir la ROM y copiar sus bytes a la RAM del emulador
    bool loadROM(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "❌ Error: No se pudo abrir la ROM: " << filename << std::endl;
            return false;
        }

        // Leemos la ROM binaria directamente en nuestra memoria
        file.read(reinterpret_cast<char*>(memory), 65536);
        std::cout << "✅ ROM cargada con éxito en la memoria." << std::endl;
        return true;
    }

    // Ciclo básico Fetch-Decode (Lee la instrucción y avanza el PC)
    void step() {
        uint8_t opcode = memory[PC];

        // Imprime en consola la dirección actual (PC) y el Opcode en Hexadecimal
        std::cout << "PC: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << PC 
                  << " | Opcode: 0x" << std::setw(2) << (int)opcode << std::endl;

        PC++; // Avanzamos al siguiente byte en memoria
    }
};

int main() {
    std::cout << "=== shadev64 :: LR35902 CPU Core v0.1 ===" << std::endl;

    LR35902 cpu;

    // Intenta cargar una ROM de prueba (asegúrate de poner el nombre de tu ROM)
    if (cpu.loadROM("rom.gb")) {
        std::cout << "\nEjecutando primeros 10 ciclos de lectura:\n" << std::endl;
        for (int i = 0; i < 10; i++) {
            cpu.step();
        }
    }

    return 0;
}
