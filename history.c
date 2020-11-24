#include "shell.h"

/**
 * read_textfile - reads a text file and prints it to the POSIX standard output
 * @filename: the file to read from
 * @letters: the number of letters to read from file
 * Return: the actual number of letters or 0 if failed
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	char *buf = NULL;
	int fd;
	ssize_t bytes;

	if (!filename || !letters)
		return (0);

	buf = malloc(letters + 1);
	if (!buf)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (free(buf), 0);

	bytes = read(fd, buf, letters);
	if (bytes == -1)
		return (free(buf), 0);

	buf[letters] = '\0';
	bytes = write(STDOUT_FILENO, buf, bytes);
	if (bytes == -1)
		return (free(buf), 0);

	free(buf);
	close(fd);
	return (bytes);
}

/**
 * create_file - creates a file.
 * @filename: the name of the file to create
 * @text_content: a NULL terminated string to write to the file
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int bytes, fd;
	mode_t modes;

	modes = S_IRUSR | S_IWUSR;
	if (!filename)
		return (-1);

	fd = open(filename, O_RDWR | O_CREAT | O_APPEND, modes);
	if (fd == -1)
		return (-1);

	if (text_content)
	{
		bytes = write(fd, text_content, strlen(text_content));
		if (bytes == -1)
			return (-1);
	}

	close(fd);
	return (1);
}

/**
 * append_text_to_file - appends text at the end of a file.
 * @filename: the name of the file
 * @text_content: the NULL terminated string to add at the end of the file
 * Return: 1 on success and -1 on failure
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int bytes, fd;

	if (!filename)
		return (-1);

	fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (-1);

	if (text_content)
	{
		bytes = write(fd, text_content, strlen(text_content));
		if (bytes == -1)
			return (-1);
	}

	close(fd);
	return (1);
}
