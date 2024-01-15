#include <bits/stdc++.h>
using namespace std;

void init();
int load();
int execute();
int mos(int op_add);
int allocate();
int addressmap(int va);

struct PCB
{
    int job_id;
    int TTL;
    int TLL;
    int TTC ;
    int TLC ;
};
struct PCB P;

char IR[4];
char R[4];
int IC,SI;
bool toggle;
char M[300][4];
int ptr;
bool visited[30];
int PI;
int TI;
int EM;
fstream input;
fstream output;

int main(){
    input.open("input2.txt",ios::in);
    output.open("output2.txt",ios::out);
    load();
    return 0;
}

void init(){
    for (int i = 0; i < 300; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = ' ';
        }
    }
    for (int i = 0; i < 4; i++)
    {
        IR[i] = ' ';
        R[i] = ' ';
    }
    IC = 0;
    toggle = false;
    ptr = 0;
}

int allocate(){
    return (rand() % 30);
}

int addressmap(int va){
    int pte = ptr*10 + va/10;
    int add;
    add = (M[pte][2]-48)*10 + (M[pte][3]-48);
    return add*10;
}

int mos(int op_add){
    if (SI == 1)
    {
        string buffer;
        getline(input,buffer);
        if (buffer[0]=='$' && buffer[1]=='E' && buffer[2]=='N' && buffer[3]=='D')
        {
            return 1;
        }
        int frameno = allocate();
        while (visited[frameno] != false)
        {
            frameno = allocate();
        }
        visited[frameno] = true;
        int add = ptr*10 + op_add/10;
        M[add][0] = ' ';
        M[add][1] = ' ';
        M[add][2] = frameno / 10 + 48;
        M[add][3] = frameno % 10 + 48;
        int j = frameno*10;
        int k = 0;
        for (int i = 0; i < 40 && i < buffer.length(); i++)
        {
            M[j][k++] = buffer[i];
            if (k == 4)
            {
                k = 0;
                j++;
            }
        }
    }
    else if (SI == 2)
    {
        string out;
        int pte = ptr*10 + op_add/10;
        if (M[pte][0] == '*')
        {
            PI = 3;
            return 6;
        }
        int frameno = (M[pte][2]-48)*10 + (M[pte][3]-48);
        int add = frameno*10;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                out += M[add][j];
            }
            add++;
        }
        output<<out<<'\n';
        P.TLC++;
    }
    else if (SI == 3)
    {
        output<<"\n\n";
        if (P.TTC > P.TTL)
        {
            TI = 2;
        }
        else 
        {
            return 0;
        }
    }
    if (TI = 2)
    {
        return 3;
    }
}

int execute(){
    int RA = addressmap(0);
    int count = 0;
    while (true)
    {
        if (P.TLC > P.TLL)
        {
            return 2;
        }
        if (P.TTC > P.TTL)
        {
            TI = 2;
            int flag = mos(0);
            return flag;
        }
        for (int i = 0; i < 4; i++)
        {
            IR[i] = M[RA][i];
        }
        RA++;count++;
        if (count == 11)
        {
            int pte = ptr*10 + 1;
            int frameno = (M[pte][2]-48)*10 + (M[pte][3]-48);
            RA = frameno*10;
        }
        if(IR[0]!='H')
        {
            if (isdigit(IR[2]) == 0 || isdigit(IR[3]) == 0)
            {
                PI = 2;
                return 5;
            }
        }
        if (IR[0] == 'L' && IR[1] == 'R')
        {    
            int op_add, offset;
            op_add = (IR[2]-48)*10;
            offset = IR[3]-48;
            int pte = ptr*10 + op_add/10;
            if (M[pte][0] == '*')
            {
                PI = 3;
                return 6;
            }
            int add = (M[pte][2]-48)*10 + (M[pte][3]-48);
            for (int i = 0; i < 4; i++)
            {
                R[i] = M[add*10+offset][i];
            }
            P.TTC++;
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            int op_add, offset;
            op_add = (IR[2]-48)*10;
            offset = IR[3]-48;
            int pte = ptr*10 + op_add/10;
            int add = (M[pte][2]-48)*10 + (M[pte][3]-48);
            for (int i = 0; i < 4; i++)
            {
                M[add*10+offset][i] = R[i];
            }
            P.TTC = P.TTC + 2;
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            int op_add, offset;
            op_add = (IR[2]-48)*10;
            offset = IR[3]-48;
            int pte = ptr*10 + op_add/10;
            if (M[pte][0] == '*')
            {
                PI = 3;
                return 6;
            }
            int add = (M[pte][2]-48)*10 + (M[pte][3]-48);
            int flag = 0;
            for (int i = 0; i < 4; i++)
            {
                if (R[i] != M[add*10+offset][i])
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
            P.TTC++;  
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            int op_add, offset, inst_no;
            op_add = (IR[2]-48)*10;
            offset = IR[3]-48;
            if (toggle == true)
            {
                int pte = ptr*10 + 1;
                RA = ((M[pte][2]-48)*10 + (M[pte][3]-48))*10 + offset;cout<<"UPDATED RA:"<<RA<<endl;
                count = 0;
            }
            P.TTC++;
        }
        else if (IR[0] == 'G' && IR[1] == 'D')
        {
            int op_add = (IR[2]-48)*10 + (IR[3]-48);
            SI = 1;
            int flag = mos(op_add);
            if (flag == 1)
            {
                return 1;
            }
            P.TTC = P.TTC + 2;
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            int op_add = (IR[2]-48)*10 + (IR[3]-48);
            SI = 2;
            int flag = mos(op_add);
            if (flag == 6)
            {
                PI = 3;
                return 6;
            }
            P.TTC++;
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            P.TTC++;
            int flag = mos(0);
            if (flag != 0)
            {
                return flag;
            }
            else 
            {
                return 0;
            }
        }
        else
        {
            PI = 1;
            return 4;
        }
    }
}

int load(){
    string buffer;
    string line = "";
    int flag;
    while (getline(input,buffer,'\n'))
    {
        for (int i = 0; i < 4; i++)
        {
            line += buffer[i];
        }
        if (line == "$AMJ")
        {
            init();
            buffer.clear();
            line.clear();
            ptr = allocate();
            for (int i = ptr*10; i < ptr*10 + 10; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    M[i][j] = '*';
                }
            }
            visited[ptr] = true;
            string jobid_str = "";
            string TTL_str = "";
            string TLL_str = "";
            for (int i = 0; i < 4; i++)
            {
                jobid_str += buffer[i + 4];
                TTL_str += buffer[i + 8];
                TLL_str += buffer[i + 12];
            }
            P.job_id = stoi(jobid_str);
            P.TTL = stoi(TTL_str);
            P.TLL = stoi(TLL_str);
            P.TLC = 0;
            P.TTC = 0;
        }
        else if (line == "$DTA")
        {
            buffer.clear();
            line.clear();
            flag = execute();
        }
        else if (line == "$END")
        {
            line.clear();
            buffer.clear();
            if (flag == 0)
            {
                cout<<"Memory Print:"<<endl;
                for (int i = 0; i < 150; i++)
                {
                cout<<"M["<<i<<"]:";
                for (int j = 0; j < 4; j++)
                {
                    cout<<M[i][j];
                }
                cout<<"\t\t";
                cout<<"M["<<i+150<<"]:";
                for (int j = 0; j < 4; j++)
                {
                    cout<<M[i+150][j];
                }
                cout<<endl;
                }
                cout<<"********HALT********"<<endl;
            }
            else if (flag == 1)
            {
                cout<<"Error Code:1 Out of Data."<<endl;
                output<<"Program Terminated Abnormally."<<endl;
                output<<"Error Code:1 Out of Data."<<endl;
            }
            else if (flag == 2)
            {
                cout<<"Error Code:2 Line Limit Exceeded."<<endl;
                output<<"Program Terminated Abnormally."<<endl;
                output<<"Error Code:2 Line Limit Exceeded."<<endl;
            }
            else if (flag == 3)
            {
                cout<<"Error Code:3 Time Limit Exceeded."<<endl;
                output<<"Program Terminated Abnormally."<<endl;
                output<<"Error Code:3 Time Limit Exceeded."<<endl;
            }
            else if (flag == 4)
            {
                cout<<"Error code:4 Operation Code Error."<<endl;
                output<<"Program Terminated Abnormally."<<endl;
                output<<"Error Code:4 Operation Code Error."<<endl;
            }
            else if (flag == 5)
            {
                cout<<"Error Code:5 Operand Error."<<endl;
                output<<"Program Terminated Abnormally."<<endl;
                output<<"Error Code:5 Operand Error."<<endl;
            }
            else if (flag == 6)
            {
                cout<<"Error Code:6 Invalid Page Fault."<<endl;
                output<<"Program Terminated Abnormally."<<endl;
                output<<"Error Code:6 Invalid Page Fault."<<endl;
            }
            cout<<"Toggle:"<<toggle<<"\t"<<"TTL:"<<P.TTL<<"\t"<<"TTC:"<<P.TTC<<"\t"<<"TLC:"<<P.TLC<<"\t"<<"TLL:"<<P.TLL<<endl;
            output<<"Toggle:"<<toggle<<"\t"<<"TTL:"<<P.TTL<<"\t"<<"TTC:"<<P.TTC<<"\t"<<"TLC:"<<P.TLC<<"\t"<<"TLL:"<<P.TLL<<endl;
        }
        else
        {
            int frameno = allocate();
            while (visited[frameno] != false)
            {
                frameno = allocate();
            }
            visited[frameno] = true;
            int add = ptr*10;
            while (M[add][0] != '*')
            {
                add++;
            }
            M[add][0] = ' ';
            M[add][1] = ' ';
            M[add][2] = frameno / 10 + 48;
            M[add][3] = frameno % 10 + 48;
            int k = 0;
            for (int i = frameno*10; i < frameno*10 + 10 && k < buffer.length(); i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (buffer[k] == 'H')
                    {
                        M[i][j] = buffer[k++];
                        break;
                    }
                    else
                    {
                        M[i][j] = buffer[k++];
                    }
                }
            }
            buffer.clear();
            line.clear();
        }
    }
}