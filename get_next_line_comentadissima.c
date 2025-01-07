#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

//desconsiderar, só pra BUFFER_SIZE existir por enquanto
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif


size_t ft_strlen(const char *s)//const char significa que o input nao vai ser modificado durante a excução, pq a função é só de leitura
{
    size_t index; //size_t é melhor do que int pq é unsigned, isso sigifica que sera grande o suficiente para armazenar o tamanho de qualquer objeto

    index = 0;
    if(!s)
        return (0);
    while(s[index] != '\0')
        index++;
    return (index);
}

char    *ft_strchr(char *s, int c)
{
    int index;//guarda o valor do index

    index = 0;
    if(!s)
        return (NULL); //verifica se s é valida
    if (c == '\0')
        return ((char *)&s[ft_strlen(s)]); // caso o char procurado for \0, retorna um ponteiro pro ultimo char de s
    while (s[index] != '\0')
    {
        if (s[index] == (char)c)//quando encontra o char, retorna um ponteiro pro endereço desse char
            return ((char *)&s[index]); //isso é importante pq vai ser usado na função read_and_store
        index++;
    }
    return (NULL); //caso não encontre o c, retorna nulo
}

size_t  ft_strlcpy(char *dest, const char *src, size_t size)
{
    size_t  index;
    size_t  len_src;

    index = 0;
    len_src = 0;
    while (src[len_src] != '\0') //enquanto não chegar no nullterm, aumenta o len_src
    {
        len_src++;
    }
    if (size > 0)
    {
        while (src[index] != '\0' && index < (size - 1))//o loop continua até o nullterm e index menor que size
        {
            dest[index] = src[index]; //copia src para dest
            index++;
        }
        dest[index] = '\0'; //nullterm dest quando o loop acabar
    }
    return(len_src);
}

char *ft_strjoin(char *str1, char *str2)
{
    char    *new_string;
    size_t  lenstr1;
    size_t  lenstr2;

    if (str1)//caso a str1 não for 0, calcular o tamanho
        lenstr1 = ft_strlen(str1);
    else //caso for 0, o len vai ser 0
        lenstr1 = 0; 
    lenstr2 = ft_strlen(str2);
    new_string = malloc(lenstr1 + lenstr2 + 1); //aloca memoria para a duas strings + nullterm
    if (!new_string)
        return (NULL); //checa se a alocação foi bem sucedida
    if (str1) //caso haja chars in str1
    {
        ft_strlcpy(new_string, str1, lenstr1 + 1); //copia str1 para new_str do tamaho lenstr1+nullterm
        free(str1); 
    }
    ft_strlcpy(new_string + lenstr1, str2, lenstr2 + 1); //copia str2 para new_str do tamaho lenstr1+nullterm
    return(new_string); //retorna a string concatenada
}

char    *read_and_store(int fd, char *buffer)
{
    char    *read_buffer; //guarda os caracteres lidos
    int     bytes_read; //guarda a quantidade de caracteres lidos

    //aloca memoria suficiente pra ler o fd do tamanho do buffer +1, correspondente ao \n ou \0
    read_buffer = malloc(BUFFER_SIZE + 1);
    if(!read_buffer)
        return (NULL);
    bytes_read = 1; //atribuição para que haja pelo menos uma volta no loop
    //o loop continua até que o \n seja encontrado, ou não exista mais bytes para serem lidos (EOF)
    while (!ft_strchr(buffer, '\n') && bytes_read !=0)
    {
        //a função read vai ler o fd em blocos do tamanho BUFFER_SIZE e armazenar em read_buffer
        bytes_read = read(fd, read_buffer, BUFFER_SIZE); //a qtdd de bytes lidos sera armazenada
        if (bytes_read == -1) //caso haja algum erro na leitura, libera memoria de tudo
        {
            free(read_buffer); //libera memoria dos caracteres lidos agora
            free(buffer); //libera memoria de tudo que ja esta armazenado no buffer
            return (NULL); 
        }
        read_buffer[bytes_read] = '\0'; //coloca o nullterminator na posiçao bytes_read, que a essa altura deve corresponder ao fim da linha.
        buffer = ft_strjoin(buffer, read_buffer); //concatena os chars recem lidos (read_buffer), aos ja armazenados (buffer)
    }
    free(read_buffer); //libera a memoria dos chars recem lidos
    return (buffer); //retorna a linha até o \n
}

char *extract_line(char *buffer)
{
    int     index;
    char    *line;

    index = 0;
    if(!buffer || !buffer[index]) //checa se buffer é valido
        return  (NULL);
    while (buffer[index] && buffer[index] != '\n')
        index++; //contador para o tamanho da memoria que precisa ser alocada até \n
    line = malloc(index + 2); //aloca memoria para a linha até n (armazenada em index) +nullterm +\n
    if(!line)
        return (NULL); //checa a alocação de memória para line
    index = 0; //reseta o index
    while (buffer[index] && buffer[index] != '\n')
    {
        line[index] = buffer[index]; //copia buffer para line
        index++;
    }
    if (buffer[index] == '\n')
    {
        line[index] = buffer[index]; // se o char for \n, copiar também
        index++;
    }
    line[index] = '\0'; //coloca o nullterm no fim da linha
    return (line); //retorna a linha completa (até \n)
}

char    *extract_remaining(char *buffer)
{
    int     i;
    int     j;
    char    *remaining_content;

    i = 0;
    while (buffer[i] && buffer[i] != '\n') //enquanto não chegar no \n, pula pro proximo char
        i++;
    if(!buffer[i]) //checa se buffer é valido
    {
        free(buffer);
        return (NULL);
    }
    remaining_content = malloc(ft_strlen(buffer) - i); //aloca memoria para o conteudo do buffer depois do \n
    if (!remaining_content) //checa se a alocação foi bem sucedida
        return (NULL);
    i++; //se chegou no \n, sai do loop
    j = 0;
    while(buffer[i])
        remaining_content[j++] = buffer[i++]; //copia o conteudo após o \n pro buffer
    remaining_content[j] = '\0'; //nullterm a string copiada
    return (remaining_content); //retorna o conteúdo copiado
}

char    *get_next_line(int fd)
{
    static char *buffer; //guarda o valor dos char lidos, precisa ser static pra manter o valor entre as diferentes funções
    char    *line; //guarda a linha inteira (até \n)

    if (fd < 0 || BUFFER_SIZE <= 0)//checa se fd e buffersize sáo validos
        return (NULL);
    //buffer vai ser o retorno da função read_and_store
    buffer = read_and_store(fd, buffer); //coloca o conteudo lido do tamanho do BUFFER_SIZE no buffer
    if (!buffer)//checa se buffer existe
        return (NULL); 
    line = extract_line(buffer); //coloca o conteúdo do buffer até /n na line
    if(!line)//checa se line existe
    {    
        free(buffer);
        buffer = NULL;
        return (NULL); 
    }
    buffer = extract_remaining(buffer); //coloca o conteudo após \n no buffer
    return(line); //retorna a linha completa
}

int main(void)
{
    int fd;
    char *line;

    // Open the file "text.txt" in read-only mode
    fd = open("text.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }

    // Read and print lines using get_next_line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line); // Print the line
        free(line);         // Free the memory allocated by get_next_line
    }

    // Close the file descriptor
    close(fd);

    return (0);
}