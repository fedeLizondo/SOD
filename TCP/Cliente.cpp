#include <atomic>
#include <thread>
#include <iostream>
#include <string>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <ncurses.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

std::mutex m;

int client;
const int bufsize = 1024;
char buffer[bufsize];
char sender[bufsize];
        

void ReadCin(std::atomic<bool>& run)
{
    std::string mensaje = "";  
    while (run.load())
    {    m.lock();
        char a = getch();
        m.unlock();
        if( a == '\n'){
            if (mensaje == "Exit")
            {
                run.store(false);
            } else {
                sprintf(sender,"%s",mensaje.c_str());
                send(client,sender,bufsize,0);
                mensaje = "";
            }
        }
        else
        {
            mensaje += a;
        }
        
        m.lock();
        printf("%c[%d;%df",0x1B,22,0);
        printf("%s","\033[K");
        std::cout<<mensaje<<std::endl;
        m.unlock();
    }
}

int main()
{
    initscr();
	clear();
	noecho();
	cbreak();
    refresh();
    keypad( curscr,true );

    int portNum = 1500; // NOTE that the port number is same for both client and server
    bool isExit = false;
    const char * ip = "127.0.0.1";
    struct sockaddr_in server_addr;

    //Preparo la conexion
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) 
    {
        std::cout << "\nError establishing socket..." << std::endl;
        exit(1);
    }
    //Creo la estructura Necesaria
    server_addr.sin_family = AF_INET; //IPv4
    server_addr.sin_addr.s_addr = inet_addr( ip ); //Direccion del Servidor
    server_addr.sin_port = htons(portNum); //Puerto del servidor
    
    //Connecto
    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
    {
        
        std::atomic<bool> run(true);
        std::thread cinThread(ReadCin, std::ref(run));
        
        int i = 0;
        while (run.load())
        {   
            recv(client, buffer, bufsize, 0);
            printf("%s","\033[u");      
            printf("%c[%d;%df",0x1B,((i++)%21)+1,0);
            std:: cout<< buffer << std::endl;
            printf("%s"," \033[s");
            
        }

        run.store(false);
        cinThread.join();
    }

    clrtoeol();
	refresh();
	endwin();

    return 0;
}