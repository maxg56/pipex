/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgendrot <mgendrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:31:03 by mgendrot          #+#    #+#             */
/*   Updated: 2024/11/29 16:37:03 by mgendrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	irst_child(int fd[2], int file1, char *cmd, char **envp)
{
	dup2(file1, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	exec_cmd(cmd, envp);
}

void	second_child(int fd[2], int file2, char *cmd, char **envp)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(cmd, envp);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**args;
	char 	*path;

	args = ft_split(cmd, ' ');
	path = find_path(args[0], envp);
	if (!path)
		error("Command not found");
	execve(path, args, envp);
	perror("Execve error");
	exit(EXIT_FAILURE);
}

char *find_path(char *cmd, char **envp) {
    int i = 0;
    char **paths;
    char *path;
    char *full_path;

    // Trouver la variable d'environnement PATH
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    if (!envp[i]) // Si PATH n'existe pas dans l'environnement
        return (NULL);

    // Diviser les chemins dans PATH
    paths = ft_split(envp[i] + 5, ':'); // On ignore "PATH=" avec `+ 5`
    if (!paths)
        return (NULL);

    // Vérifier chaque chemin pour trouver la commande
    for (i = 0; paths[i]; i++) {
        path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(path, cmd);
        free(path);
        if (access(full_path, X_OK) == 0) { // Vérifie si le fichier est exécutable
            free_tab(paths);
            return (full_path);
        }
        free(full_path);
    }
    free_tab(paths);
    return (NULL); // Commande non trouvée
}
