#include "queue.h"
#include "stack.h"
#include "set.h"
#include "hash_table.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/mman.h>

#define commad_line "Enter the command\n"
#define data_line "Enter the data\n"
#define key_line "Enter tne key\n"
#define done_line "Done!\n"
#define _SIZE_ 15

// функция обработки запросов
void dostuff (int sock, int shm);//, HT* table, SET* my_set);

// функция обработки ошибок
void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}
// количество активных пользователей
int nclients = 0;
// печать количества активных пользователей
void printusers() 
{
    if (nclients) {
        printf("%d user on-line\n", nclients);
    }
    else {
        printf("No User on-line\n");
    }
}

int main(int argc, char *argv[]) {
    char buff[1024]; // Буфер для различных нужд
    int sockfd, newsockfd; // дескрипторы сокетов
    int portno; // номер порта
    int pid; // id номер потока
    socklen_t clilen; // размер адреса клиента типа socklen_t
    struct sockaddr_in serv_addr, cli_addr; // структура сокета сервера и клиента
    
    // ошибка в случае если мы не указали порт
    if (argc < 2) {
        fprintf(stderr, "ERROR: no port provided\n");
        exit(EXIT_FAILURE);
    }
    
    // создание сокета
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR: opening socket");
    
    // связывание сокета с локальным адресом
    bzero((char*) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // сервер принимает подключения на все IP-адреса
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR: on binding");
    }
    
    // ожидание подключений, размер очереди - 5
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    
    // создание общей ячейки памяти для хранения количества активных пользователей
    int shm = shm_open("/shm", O_CREAT | O_RDWR, 0660);
    if (shm == -1) 
    {
    	error("Shared memory open");
    }
    
    if (ftruncate(shm, sizeof(int)) == -1) 
    {
    	error("Shared memory truncate");
    }
    
    char* addr = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0);
    memcpy(addr, &nclients, sizeof(nclients));

    //HT* table = create_table(_SIZE_);
    //SET* my_set = create_set(_SIZE_);

    // извлекаем сообщение из очереди (цикл извлечения запросов на подключение)
    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) error("ERROR: on accept");
        memcpy(&nclients, addr, sizeof(nclients));
        nclients++;
        memcpy(addr, &nclients, sizeof(nclients));

        // вывод сведений о клиенте
        struct hostent *hst;
        hst = gethostbyaddr((char *)&cli_addr.sin_addr, 4, AF_INET);
        printf("+%s [%s] new connect!\n",
        (hst) ? hst->h_name : "Unknown host",
        (char*)inet_ntoa(cli_addr.sin_addr));
        printusers();

        pid = fork();
        if (pid < 0) error("ERROR: on fork");
        if (pid == 0) {
            close(sockfd);
            dostuff(newsockfd, shm);//, table, my_set);
            exit(EXIT_SUCCESS);
        }
        else close(newsockfd);
    }
    close(sockfd);
    exit(EXIT_SUCCESS);
}


void dostuff (int sock, int shm)//, HT* table, SET* my_set) 
{
    int bytes_recv; // размер принятого сообщения
    //int a,b; // переменные для myfunc
    //char message[1024];
    char buff[20 * 1024];
    char startBuff[10]; // Буфер для различных нужд
    char* addr = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0);

    while (1) {
        // ожидаем готовности клиента
        bytes_recv = read(sock, &startBuff[0], sizeof(startBuff));
        if (bytes_recv < 0) error("ERROR reading from socket");
        if (strcmp(startBuff, "start\n")) break;

        // отправляем клиенту сообщение
        write(sock, commad_line, sizeof(commad_line));
        
        // обработка первого параметра
        bytes_recv = read(sock, &buff[0], sizeof(buff));
        
        if (bytes_recv < 0) error("ERROR reading from socket");
        if (!strcmp(buff, "end\n")) break;

        if (strcmp(buff, "SADD\n") == 0)
        {
            /*printf("Enter the data: ");
            char data[100];
            scanf("%s", data);

            printf("\nYour data: %s\n", data); /

            // отправляем клиенту сообщение
            write(sock, data_line, sizeof(data_line));
        
            // обработка первого параметра
            bytes_recv = read(sock, &buff[0], sizeof(buff));
        
            if (bytes_recv < 0) error("ERROR reading from socket");
            //if (!strcmp(buff, "end\n")) break;

            set_insert(my_set, buff, "");*/


            write(sock, &buff[0], strlen(buff) + 1);
        }
        if (strcmp(buff, "SPUSH\n") == 0)
        {
            /*printf("Enter the data: ");
            char data[100];
            scanf("%s", data);

            printf("\nYour data: %s\n", data);*/

            // отправляем клиенту сообщение
            write(sock, data_line, sizeof(data_line));
        
            // обработка первого параметра
            bytes_recv = read(sock, &buff[0], sizeof(buff));
        
            if (bytes_recv < 0) error("ERROR reading from socket");
            //if (!strcmp(buff, "end\n")) break;

            push_stack(buff);

            // отправляем клиенту сообщение
            write(sock, done_line, sizeof(done_line));

        }
        /*else if (strcmp(buff, "QPUSH\n") == 0)
        {
            printf("Enter the data: ");
            char data[100];
            scanf("%s", data);

            printf("\nYour data: %s\n", data);

            push_queue(data);

        }
        /*else if (strcmp(buff, "HSET\n") == 0)
        {
            printf("Enter the data: ");
            char data[100];
            scanf("%s", data);

            printf("Enter the key: ");
            char key[100];
            scanf("%s", key);

            printf("\nYour key: %s data: %s\n", key, data);

            ht_insert(table, key, data);
        }
        //------------REMOVE------------

        else if (strcmp(buff, "SREM\n") == 0)
        {
            printf("Enter the data: ");
            char data[100];
            scanf("%s", data);

            printf("\nYour key: %s\n", data);

            set_delete(table, data);
        }*/
        printf("%s", buff);
        if (strcmp(buff, "SPOP\n") == 0)
        {

            //printf("%s\n", pop_stack());

            char* msg_res = pop_stack();
            // отправляем клиенту сообщение
            write(sock, msg_res, sizeof(msg_res));
        }
        /*else if (strcmp(buff, "QPOP\n") == 0)
        {
            printf("%s\n", pop_queue());
        }
        else if (strcmp(buff, "HDEL\n") == 0)
        {
            printf("Enter the key: ");
            char key[100];
            scanf("%s", key);

            printf("\nYour key: %s\n", key);

            ht_delete(table, key);
        }

        //------------READ------------
        else if (strcmp(buff, "SISMEMBER\n") == 0)
        {
            printf("Why?\n");
        }
        else if (strcmp(buff, "HGET\n") == 0)
        {
            printf("Enter the key: ");
            char key[100];
            scanf("%s", key);

            printf("\nYour key: %s\n", key);

            print_search(table, key);
        }*/
        else
        {
            char* msg_error = "ERROR: incorrect command\n";
            // отправляем клиенту сообщение
            write(sock, msg_error, sizeof(msg_error));
        }

        
        //a = atoi(buff); // преобразование первого параметра в int

        // отправляем клиенту сообщение
        /*write(sock, second_line, sizeof(second_line));

        // обработка второго параметра
        bytes_recv = read(sock, &buff[0], sizeof(buff));
        if (bytes_recv < 0) error("ERROR reading from socket");
        if (!strcmp(buff, "quit\n")) break;

        b = atoi(buff); // преобразование второго параметра в int

        // отправляем клиенту сообщение
        write(sock, third_line, sizeof(third_line));

        // обработка знака
        bytes_recv = read(sock, &buff[0], sizeof(buff));
        if (bytes_recv < 0) error("ERROR reading from socket");
        if (!strcmp(buff, "quit\n")) break;

        a = myfunc(a, b, buff[0]); // вызов пользовательской функции
        sprintf(buff, "%d", a); // преобразование результата в строку
        buff[strlen(buff)] = '\n'; // добавление к сообщению символа конца строки

        // отправляем клиенту результат
        //write(sock, &buff[0], sizeof(buff[0]));
        write(sock, &buff[0], strlen(buff) + 1);*/
    }
    memcpy(&nclients, addr, sizeof(nclients));
    nclients--; // уменьшаем счетчик активных клиентов
    memcpy(addr, &nclients, sizeof(nclients));
    close(sock);
    printf("-disconnect\n");
    printusers();
    return;
}
