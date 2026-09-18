#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iomanip>

class LR35902 {
public:
    uint8_t A = 0, F = 0;
    uint8_t B = 0, C = 0;
    uint8_t D = 0, E = 0;
    uint8_t H = 0, L = 0;

    uint16_t PC = 0x0100;
    uint16_t SP = 0xFFFE;

    uint8_t memory[65536] = {0};

    bool loadROM(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "❌ Error: No se pudo abrir la ROM: " << filename << std::endl;
            return false;
        }

        file.read(reinterpret_cast<char*>(memory), 65536);
        std::cout << "✅ ROM cargada con exito en la memoria." << std::endl;
        return true;
    }

    void step() {
        uint16_t currentPC = PC; // Guardamos la dirección actual para el log
        uint8_t opcode = memory[PC++]; // Leemos el byte y avanzamos el PC

        std::cout << "PC: 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << currentPC 
                  << " | Opcode: 0x" << std::setw(2) << (int)opcode << " -> ";

        // Decodificador de Instrucciones (Decode & Execute)
        switch (opcode) {
            case 0x00: // NOP (No Operation)
                std::cout << "NOP" << std::endl;
                break;

            case 0xC3: { // JP a16 (Jump a dirección de 16 bits)
                // La Game Boy guarda los enteros en Little-Endian (Byte Bajo primero, luego Byte Alto)
                uint16_t low = memory[PC++];
                uint16_t high = memory[PC++];
                uint16_t targetAddress = (high << 8) | low;

                std::cout << "JP 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << targetAddress 
                          << " (SALTANDO...)" << std::endl;

                PC = targetAddress; // La CPU salta a la nueva dirección
                break;
            }

            default:
                std::cout << "Opcode no implementado aun!" << std::endl;
                break;
        }
    }
};

int main() {
    std::cout << "=== shadev64 :: LR35902 CPU Core v0.1.1 ===" << std::endl;

    LR35902 cpu;

    if (cpu.loadROM("rom.gb")) {
        std::cout << "\nEjecutando primeros 20 ciclos de instrucción:\n" << std::endl;
        for (int i = 0; i < 20; i++) {
            cpu.step();
        }
    }

    std::cout << "\nPresiona ENTER para salir...";
    std::cin.get();

    return 0;
}
