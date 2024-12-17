/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:28:22 by mmariano          #+#    #+#             */
/*   Updated: 2024/12/17 12:47:58 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int	readbytes;
	char *cupbuffer;

	cupbuffer = ft_calloc(3 + 1, sizeof(char));
	if (!cupbuffer)
		return (NULL);
	readbytes = read(fd, cupbuffer, 3);
	return (cupbuffer);
	if (readbytes <= 0)
		return (NULL);
	return (cupbuffer);
}

#include "get_next_line.h" // Inclui o cabeçalho com as definições necessárias, como protótipos de funções e macros.

char	*read_file_with_malloc(int fd, char *store_until_n)
{
	char	*buffer;          // Ponteiro temporário para armazenar os bytes lidos do arquivo.
	char	*old_adress;      // Guarda o endereço anterior de store_until_n para liberar após realocação.
	int		store_read_bytes; // Variável para armazenar a quantidade de bytes lidos do arquivo.

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char)); // Aloca memória para o buffer com tamanho BUFFER_SIZE + 1.
	if (!buffer) // Verifica se a alocação de memória falhou.
		return (NULL);
	while (!ft_strchr(store_until_n, '\n')) // Continua lendo enquanto não encontrar um '\n' na string.
	{
		store_read_bytes = read(fd, buffer, BUFFER_SIZE); // Lê até BUFFER_SIZE bytes do arquivo.
		if (store_read_bytes == -1) // Verifica erro na leitura.
		{
			return (free(buffer), free(store_until_n), // Libera a memória alocada e retorna NULL.
				store_until_n = NULL, buffer = NULL, NULL);
		}
		buffer[store_read_bytes] = '\0'; // Adiciona o caractere nulo no final do buffer para formar uma string válida.
		old_adress = store_until_n; // Salva o endereço atual de store_until_n.
		store_until_n = ft_strjoin(store_until_n, buffer); // Concatena o conteúdo lido com o conteúdo já existente.
		free(old_adress); // Libera a memória antiga alocada.
		old_adress = NULL; // Evita ponteiro solto.
		if (store_read_bytes < BUFFER_SIZE) // Se a leitura foi menor que BUFFER_SIZE, significa fim do arquivo.
			break ;
	}
	return (free(buffer), buffer = NULL, store_until_n); // Libera o buffer e retorna a string final.
}

void	extract_after_n(char *store_until_n, char *remainder_line)
{
	int	i;

	i = 0;
	while (store_until_n[i] != '\n' && store_until_n[i] != '\0') // Percorre a string até encontrar '\n' ou o fim.
		i++;
	if (store_until_n[i] == '\n') // Se um '\n' foi encontrado.
	{
		ft_strlcpy(remainder_line, &store_until_n[i + 1], BUFFER_SIZE); // Copia o conteúdo após '\n' para remainder_line.
		store_until_n[i + 1] = '\0'; // Trunca a string original para finalizar no '\n'.
	}
}

char	*get_next_line(int fd)
{
	char		*store_until_n;             // String que acumula o conteúdo lido até encontrar um '\n'.
	static char	remainder_line[BUFFER_SIZE]; // Buffer estático para armazenar o restante da leitura entre chamadas.

	if (fd < 0 || BUFFER_SIZE <= 0) // Valida se o descritor do arquivo ou o tamanho do buffer são inválidos.
		return (NULL);
	store_until_n = ft_strdup(remainder_line); // Duplica o conteúdo de remainder_line para store_until_n.
	if (!store_until_n) // Verifica falha de alocação.
		return (NULL);
	remainder_line[0] = '\0'; // Limpa o conteúdo de remainder_line.

	store_until_n = read_file_with_malloc(fd, store_until_n); // Lê do arquivo até encontrar um '\n'.
	if (!store_until_n || store_until_n[0] == '\0') // Caso store_until_n seja NULL ou vazio após a leitura.
	{
		free(store_until_n); // Libera a memória alocada.
		store_until_n = NULL; // Evita ponteiro solto.
		return (NULL);
	}
	if (ft_strchr(store_until_n, '\n')) // Se um '\n' estiver presente, separa o restante da linha.
		extract_after_n(store_until_n, remainder_line); // Copia o restante após '\n' para remainder_line.
	return (store_until_n); // Retorna a linha lida.
}