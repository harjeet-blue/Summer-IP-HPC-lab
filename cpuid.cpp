// Code to get cache information using CPUID
// Works on Intel CPUs

#include<bits/stdc++.h>
#include "cpuid.h"
#include <stdio.h>

using namespace std;
string cpu_instruction;



int get_number(char c){

    if( c >= '0' && c <= '9')return c - '0';

    if( c >= 'A' && c <= 'F')return 10 + (c - 'A');

    if( c >= 'a' && c <= 'f')return 10 + (c - 'a');

    cout<<" Invalid Hexadecimal number !\n Please enter valid Hexadecimal value \n";
    exit(0);
    return 0;
}



int read_instruction(){

    cout<< "Enter the CPU INSTRUCTION :-  ";
    cin>>cpu_instruction;

    int leaf = 0;
    int a = get_number( cpu_instruction[6]);
    int b = get_number( cpu_instruction[7]);

    leaf += b;
    leaf += a*16;

    return leaf;

}



int read_required_bits(int leaf){
    

    int left = 0;
    int i = 0;

    while( cpu_instruction[i] !='[')i++;
    i++;

    while(cpu_instruction[i] != ':' && cpu_instruction[i] != ']')
    {
        left = left*10 + ( cpu_instruction[i] - '0');
        i++;

    }
    

    int right = 0;

    if( cpu_instruction[i] == ':'){

        i++;
        while (cpu_instruction[i] != ']')
        {
            right = right*10 + (cpu_instruction[i] - '0');
            i++;
        }

    }else{
        right = left;
    }

    if(left > 64){
        cout<<"left bit cannot exceed 64 bit\n";
        exit(0);
    }

    
    int num = 0;

    for( int i = 0 ; right <= left ; right++, i++){

        if( (leaf & (1<<right )) != 1){
            num |= ( 1<<i);
        }

    }
    
    
    return num;
}


int main() {


    unsigned int eax = 0, ebx = 0, ecx = 0, edx = 0;

    int leaf = read_instruction();

    int ret = __get_cpuid(leaf, &eax, &ebx, &ecx, &edx);

	printf("%x, %x, %x, %x, %d\n", eax, ebx, ecx, edx, ret);

    int req_bits = read_required_bits(leaf);
    printf("Required bits :- %d\n", req_bits);


    // The output is stored in variables: eax, ebx, ecx, edx
    // Use it get the information you need about L2 cache
    
}
