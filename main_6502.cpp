#include<stdio.h>
#include<stdlib.h>
using Byte = unsigned char;     // 8 bit
using Word = unsigned short;    //16 bit
using u32 = unsigned int;

struct Mem
{
    static constexpr u32 MAX_MEM = 1024*64;
    Byte Data[MAX_MEM];

    void Initialise()
    {
        for(u32 i = 0 ; i < MAX_MEM ; i++)
        {
            Data[i] = 0;
        }
    }
};

struct CPU
{
    Word PC;
    Word SP;    //stack pointer

    Byte A,X,Y; //registers

    // Status Flags/ Processor status

    Byte C : 1; //carry         1 = true
    Byte Z : 1; //zero          1 = result zero
    Byte I : 1; //IRQ Disable   1 = disable
    Byte D : 1; //Decimal Mode  1 = true
    Byte B : 1; //BRK command   1 = BRK
    Byte V : 1; //Overflow      1 = true
    Byte N : 1; //Negative      1 = Neg

    void Reset(Mem &memory)
    {
        PC = 0xFFFC;
        SP = 0x00FF;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;

        memory.Initialise();
    }


    Byte FetchByte(u32 &Cycles , Mem &memory)
    {
        Byte Data = memory[PC];
        PC++;
        Cycles--;
        return Data;

    }
    // The execution of an instruction we need to know the number of cycles
    // for which the code will get executed
    void Execute(u32 Cycles , Mem& memory)
    {
        while(Cycles > 0)
        {
            Byte Ins = FetchByte(Cycles,memory);
        }
    }
};

int main()
{
    Mem mem;
    CPU cpu;
    cpu.Reset(mem);
    cpu.Execute(2 , mem);
    return 0;
}
// Address Width 16 bits
// Data Width 8 bits