#include<bits/stdc++.h>
using namespace std;

void init();
void Load();
void ExecuteUserProgram();
void MOS();

char IR[4];
char R[4];
int IC,SI;
bool toggle;
char memory[100][4];
fstream input;
fstream output;

int main(){
    input.open("input.txt",ios::in);
    output.open("output.txt",ios::out);
    Load();
    return 0;
}

void init(){
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            memory[i][j] = ' ';
        }
    }
    for (int i = 0; i < 4; i++)
    {
        IR[i] = ' ';
        R[i] = ' ';
    }
}

void MOS(){
    if (SI == 1)
    {
        string buffer;
        getline(input,buffer);
        int k = 0;
        int add = (IR[2] - 48) * 10 + (IR[3] - 48);
        for (int i = 0; i < buffer.length() && i < 40; i++)
        {
            memory[add][k++] = buffer[i];
            if (k == 4)
            {
                k = 0;
                add++;
            }
        }
    }
    else if (SI == 2)
    {
        int add = (IR[2] - 48) * 10 + (IR[3] - 48);
        string out;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                out += memory[add][j];
            }
            add++;
        }
        output<<out<<'\n';
    }
    else if (SI == 3)
    {
        output<<'\n';
    }
}

void ExecuteUserProgram(){
    int I = 0;
    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            IR[i] = memory[I][i];
        }
        I++;
        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            MOS();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            MOS();
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            int add = (IR[2] - 48) * 10 + (IR[3] - 48);
            for (int i = 0; i < 4; i++)
            {
                R[i] = memory[add][i];
            }
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            int add = (IR[2] - 48) * 10 + (IR[3] - 48);
            for (int i = 0; i < 4; i++)
            {
                memory[add][i] = R[i];
            }
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            int flag = 0;
            int add = (IR[2] - 48) * 10 + (IR[3] - 48);
            for (int i = 0; i < 4; i++)
            {
                if (R[i] != memory[add][i])
                    flag = 1;
            }
            if (flag == 1)
            {
                toggle = false;
            }   
            else
            {
                toggle = true;
            }    
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            int add = (IR[2] - 48) * 10 + (IR[3] - 48);
            if (toggle == true)
            {
                I = add;
            }
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            MOS();
            break;
        }
    } 
}

void Load(){
    string buffer;
    string line;
    int block = 0;
    while (getline(input,buffer,'\n'))
    {
        for (int i = 0; i < 4; i++)
        {
            line = line + buffer[i];
        }
        if (line == "$AMJ")
        {
            block = 0;
            buffer.clear();
            line.clear();
            init();
        }
        else if (line == "$DTA")
        {
            buffer.clear();
            line.clear();
            ExecuteUserProgram();
        }
        else if (line == "$END")
        {
            buffer.clear();
            line.clear();
        }
        else
        {
            if (block > 100)
            {
                cout<<"Out of memory.";
            }
            else 
            {
                int k = 0;
                for (int i = block; i < block+10 && k < buffer.length(); i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if(buffer[k] == 'H')
                        {
                            memory[i][j] = buffer[k++];
                            break;
                        }
                        else
                        {
                            memory[i][j] = buffer[k++];
                        }
                    }   
                }   
                block += 10;
                line.clear();
            }
        }
    }
}